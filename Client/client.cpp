#include "client.h"
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>

const QString SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 27000;

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)), authenticated(false) {}

Client::~Client()
{
    // Ensure that the socket is properly cleaned up
    if (socket) {
        socket->disconnectFromHost();
        delete socket;  // Delete the socket
    }
}

bool Client::connectToServer() {
    socket->connectToHost(SERVER_IP, SERVER_PORT);
    if (!socket->waitForConnected(3000)) {
        showCustomMessageBox("Connection Failed", "Unable to connect to the server.", QMessageBox::Critical);
        return false;
    }
    else {
        showCustomMessageBox("Connection Successful", "Connected to server.", QMessageBox::Information);
        return true;
    }
}

bool Client::authenticate(const QString &username, const QString &password)
{
    //////for auth
    QByteArray packet;

    //Set up packet
    QByteArray packetType = "AUTH";
        //maybe change depending on server parsing
    QByteArray data = username.toUtf8() + "," + password.toUtf8();
    qint64 dataSize = static_cast<qint64>(data.size());
    QByteArray dataSizeStr = QByteArray::number(dataSize);

    //Create packet
    packet.append(packetType);
    packet.append("|");
    packet.append(dataSizeStr);
    packet.append("|");
    packet.append(data);

    //Send packet
    socket->write(packet);
    //////

    //socket->write(username.toUtf8() + "\n" + password.toUtf8());

    if (!socket->waitForBytesWritten()) {
        showCustomMessageBox("Send Error", "Error sending authentication data.", QMessageBox::Critical);
        return false;
    }

    socket->waitForReadyRead();
    QByteArray authResponse = socket->readAll();
    if (authResponse == "Authentication successful") {
        authenticated = true;
    } else {
        authenticated = false;
    }
    return authenticated;
}

void Client::sendPDF(const QString &pdfFilePath)
{
    if (!isAuthenticated()) {
        showCustomMessageBox("Not Authenticated", "You must authenticate first.", QMessageBox::Critical);
        return;
    }

    QFile file(pdfFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        showCustomMessageBox("File Error", "Unable to open the PDF file.", QMessageBox::Critical);
        return;
    }

    //Read file into memory
    QByteArray fileData = file.readAll();
    qint64 dataSize = static_cast<qint64>(fileData.size());
    QByteArray dataSizeStr = QByteArray::number(dataSize);

    //Create packet header
    QByteArray packet;
    QByteArray packetType = "PDF";
    packet.append(packetType);
    packet.append("|");
    packet.append(dataSizeStr);
    packet.append("|");
    //packet.append(fileData);

    //Send packet header
    socket->write(packet);
    if (!socket->waitForBytesWritten()) {
        showCustomMessageBox("Send Error", "Error sending file to the server.", QMessageBox::Critical);
    }

    //send file in chunks
    const int CHUNK_SIZE = 1024;
    qint64 totalSent = 0;
    while(totalSent < dataSize) {
        QByteArray chunk = fileData.mid(totalSent, CHUNK_SIZE);
        int bytesSent = socket->write(chunk);
        if(bytesSent==-1) {
            showCustomMessageBox("Send Error", "Error sending file chunk to the server.", QMessageBox::Critical);
            return;
        }
        totalSent +=bytesSent;

        if (!socket->waitForBytesWritten()) {
            showCustomMessageBox("Send Error", "Error during chunk transmission.", QMessageBox::Critical);
        }
    }

    if (totalSent != dataSize) {
        showCustomMessageBox("Send Error", "Failed to send complete file.", QMessageBox::Critical);
    }
}

void Client::receiveCSV()
{
    //Wait for response
    qDebug() << "attempting to wait for ready read";
    if (!socket->waitForReadyRead()) {
        showCustomMessageBox("Read Error", "Couldn't receive CSV file.", QMessageBox::Critical);
        qDebug() <<"NO CSV";
        return;
    }

    qDebug() <<"Attempting to read file from server";
    //Read file data from server
    QByteArray fileData;
    while(socket->bytesAvailable() > 0) {
        QByteArray chunk = socket->readAll();
        fileData.append(chunk);
    }

    if(fileData.isEmpty()) {
        showCustomMessageBox("No Data", "No CSV file received from the server.", QMessageBox::Critical);
        return;
    }

    //Create directory for file
        //Folder
    QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
    QDir().mkpath(csvFolder);

        //File name
    QString fileName = "mcq_output.csv";
    QString newFilePath = csvFolder + fileName;

    //Remove file if already exists
    if(QFile::exists(newFilePath)) {
        QFile::remove(newFilePath);
    }

    //Save data into the file
    QFile file(newFilePath);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(fileData);
        file.close();
        qDebug() <<"CSV file saved successfully";
    } else {
        showCustomMessageBox("File Error", "Failed to save CSV file.", QMessageBox::Critical);
    }

    //check to make sure csv received correctly
    //   ->can delete after debugging
    QFile printFile(newFilePath);
    if (printFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&printFile);
        qDebug() << "=== CSV File Contents ===";
        while (!in.atEnd()) {
            QString line = in.readLine();
            qDebug().noquote() << line;
        }
        qDebug() << "==========================";
        printFile.close();
    } else {
        qDebug() << "Failed to open CSV file for reading.";
    }
}

bool Client::isAuthenticated() const
{
    return authenticated;
}

void Client::showCustomMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setIcon(icon);

    msgBox.setMinimumSize(350, 250);

    msgBox.setStyleSheet("QMessageBox {"
                         "background-color: #beb4e4;"
                         "color: #7865c8;"
                         "font-size: 16px;"
                         "}"
                         "QMessageBox QLabel {"
                         "color: #FAF6F0;"
                         "}"
                         "QMessageBox QPushButton {"
                         "background-color: #8d7cd0;"
                         "border-radius: 5px;"
                         "color: #FAF6F0;"
                         "padding: 5px;"
                         "}"
                         "QMessageBox QPushButton:hover {"
                         "background-color: #7865c8;"
                         "}");

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(&msgBox);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    msgBox.setGraphicsEffect(shadowEffect);

    msgBox.setAttribute(Qt::WA_StyledBackground);

    msgBox.exec();
}
