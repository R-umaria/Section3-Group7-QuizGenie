#include "client.h"
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QDateTime>
#include <QElapsedTimer>

const QString SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 27000;

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)), authenticated(false) {}

Client::~Client()
{
    // Ensure that the socket is properly cleaned up
    if (socket) {
        //Logs disconnection from server
        saveToFile("Disconnected from Server.\n");
        socket->disconnectFromHost();
        delete socket;  // Delete the socket
    }
}

bool Client::connectToServer() {
    socket->connectToHost(SERVER_IP, SERVER_PORT);
    if (!socket->waitForConnected(3000)) {
        saveToFile("Couldn't connect to Server.\n");
        showCustomMessageBox("Connection Failed", "Unable to connect to the server.", QMessageBox::Critical);
        return false;
    }
    else {
        if(saveToFile("Connected to Server.\n")) {
            qDebug() << "saved connection to file";
        }
        else {
            qDebug() << "connection not saved";
        }
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

    if (!socket->waitForBytesWritten()) {
        saveToFile("Couldn't write authentication to Server.\n");
        showCustomMessageBox("Send Error", "Error sending authentication data.", QMessageBox::Critical);
        return false;
    }
    saveToFile("Authentication sent to Server.\n");

    socket->waitForReadyRead();
    QByteArray authResponse = socket->readAll();
    if (authResponse == "Authentication successful") {
        saveToFile("Valid login received from Server.\n");
        authenticated = true;
    } else {
        saveToFile("Invalid login received from Server.\n");
        authenticated = false;
    }
    return authenticated;
}

void Client::sendScore(QString score) {

    qDebug() << "Score: " + score;
    QByteArray data = score.toUtf8();
    qint64 dataSize = static_cast<qint64>(data.size());
    QByteArray dataSizeStr = QByteArray::number(dataSize);

    //Create Packet
    QByteArray packet;
    QByteArray packetType = "SCORE";
    packet.append(packetType);
    packet.append("|");
    packet.append(dataSizeStr);
    packet.append("|");
    packet.append(data);

    //Send packet
    socket->write(packet);

    if (!socket->waitForBytesWritten()) {
        saveToFile("Couldn't send score to Server.\n");
        showCustomMessageBox("Send Error", "Error sending score.", QMessageBox::Critical);
        exit(1);
    }
    saveToFile("Score sent to server.\n");
}

void Client::sendPDF(const QString &pdfFilePath)
{
    if (!isAuthenticated()) {
        showCustomMessageBox("Not Authenticated", "You must authenticate first.", QMessageBox::Critical);
        return;
    }

    QFile file(pdfFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        saveToFile("Couldn't open file.\n");
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
        saveToFile("Couldn't send pdf header to Server.\n");
        showCustomMessageBox("Send Error", "Error sending file to the server.", QMessageBox::Critical);
    }
    saveToFile("PDF header sent to Server.\n");

    //send file in chunks
    const int CHUNK_SIZE = 1024;
    qint64 totalSent = 0;
    while(totalSent < dataSize) {
        QByteArray chunk = fileData.mid(totalSent, CHUNK_SIZE);
        int bytesSent = socket->write(chunk);
        if(bytesSent==-1) {
            saveToFile("Couldn't send PDF chunk to Server.\n");
            showCustomMessageBox("Send Error", "Error sending file chunk to the server.", QMessageBox::Critical);
            return;
        }
        totalSent +=bytesSent;

        if (!socket->waitForBytesWritten()) {
            showCustomMessageBox("Send Error", "Error during chunk transmission.", QMessageBox::Critical);
        }
    }
    saveToFile("PDF sent to Server.\n");

    if (totalSent != dataSize) {
        saveToFile("Couldn't send complete PDF to Server.\n");
        showCustomMessageBox("Send Error", "Failed to send complete file.", QMessageBox::Critical);
    }
}

// void Client::receiveCSV()
// {
//     //Wait for response
//     qDebug() << "attempting to wait for ready read";
//     if (!socket->waitForReadyRead()) {
//         saveToFile("Couldn't receive CSV from Server.\n");
//         showCustomMessageBox("Read Error", "Couldn't receive CSV file.", QMessageBox::Critical);
//         qDebug() <<"NO CSV";
//         return;
//     }

//     qDebug() <<"Attempting to read file from server";
//     //Read file data from server
//     QByteArray fileData;
//     while(socket->bytesAvailable() > 0) {
//         QByteArray chunk = socket->readAll();
//         fileData.append(chunk);
//     }

//     if(fileData.isEmpty()) {
//         saveToFile("No CSV received from Server.\n");
//         showCustomMessageBox("No Data", "No CSV file received from the server.", QMessageBox::Critical);
//         return;
//     }
//     saveToFile("CSV received from Server.\n");

//     //Create directory for file
//         //Folder
//     QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
//     QDir().mkpath(csvFolder);

//         //File name
//     QString fileName = "mcq_output.csv";
//     QString newFilePath = csvFolder + fileName;

//     //Remove file if already exists
//     if(QFile::exists(newFilePath)) {
//         QFile::remove(newFilePath);
//     }

//     //Save data into the file
//     QFile file(newFilePath);
//     if(file.open(QIODevice::WriteOnly)) {
//         file.write(fileData);
//         file.close();
//         saveToFile("CSV saved.\n");
//         qDebug() <<"CSV file saved successfully";
//     } else {
//         saveToFile("Couldn't save CSV file.\n");
//         showCustomMessageBox("File Error", "Failed to save CSV file.", QMessageBox::Critical);
//     }

//     //check to make sure csv received correctly
//     //   ->can delete after debugging
//     QFile printFile(newFilePath);
//     if (printFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QTextStream in(&printFile);
//         qDebug() << "=== CSV File Contents ===";
//         while (!in.atEnd()) {
//             QString line = in.readLine();
//             qDebug().noquote() << line;
//         }
//         qDebug() << "==========================";
//         printFile.close();
//     } else {
//         qDebug() << "Failed to open CSV file for reading.";
//     }
// }

void Client::receiveCSV()
{
    qDebug() << "Waiting for CSV data from server...";

    QByteArray fileData;
    QElapsedTimer timer;
    timer.start();

    // Timeout after 1 minute if nothing is received
    while (timer.elapsed() < 60000) {
        if (socket->waitForReadyRead(1000)) {
            QByteArray chunk = socket->readAll();
            if (!chunk.isEmpty()) {
                fileData.append(chunk);
                qDebug() << "Received chunk of size: " << chunk.size();
            }
        } else {
            // If we’ve already received some data and no more is coming
            if (!fileData.isEmpty()) {
                break;
            }
        }
    }

    if (fileData.isEmpty()) {
        saveToFile("No CSV received from Server.\n");
        showCustomMessageBox("No Data", "No CSV file received from the server.", QMessageBox::Critical);
        return;
    }

    saveToFile("CSV received from Server.\n");

    // Create directory for file
    QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
    QDir().mkpath(csvFolder);

    QString fileName = "mcq_output.csv";
    QString newFilePath = csvFolder + fileName;

    // Remove file if already exists
    if (QFile::exists(newFilePath)) {
        QFile::remove(newFilePath);
    }

    // Save data into the file
    QFile file(newFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(fileData);
        file.close();
        saveToFile("CSV saved.\n");
        qDebug() << "CSV file saved successfully.";
    } else {
        saveToFile("Couldn't save CSV file.\n");
        showCustomMessageBox("File Error", "Failed to save CSV file.", QMessageBox::Critical);
        return;
    }

    // Debug output (optional)
    QFile debugFile(newFilePath);
    if (debugFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&debugFile);
        qDebug() << "=== CSV File Contents ===";
        while (!in.atEnd()) {
            QString line = in.readLine();
            qDebug().noquote() << line;
        }
        qDebug() << "==========================";
        debugFile.close();
    }
}


QString Client::receiveImage() {
    if (!socket->waitForReadyRead()) {
        saveToFile("Couldn't receive image from Server.\n");
        showCustomMessageBox("Read Error", "Couldn't receive image from server.", QMessageBox::Critical);
        exit(1);
    }

    // Read the file size (4 bytes)
    QByteArray sizeData = socket->read(4);
    if (sizeData.size() < 4) {
        saveToFile("Couldn't receive image size from Server.\n");
        showCustomMessageBox("Error", "Failed to receive the image size.", QMessageBox::Critical);
        exit(1);
    }
    saveToFile("Image size received from Server.\n");
    int fileSize = *reinterpret_cast<int*>(sizeData.data());
    qDebug() << "File size received: " << fileSize;

    QByteArray imageData;
    int bytesReceived = 0;

    // Read the image data in chunks
    while (bytesReceived < fileSize) {
        if (socket->bytesAvailable() > 0) {
            QByteArray chunk = socket->read(1024);  // Read in chunks of 1KB
            qDebug() << "Received " << chunk.size() << " bytes, Total received: " << bytesReceived;
            saveToFile("Received " + QString::number(chunk.size()) + " bytes from the Server.\n");
            imageData.append(chunk);
            bytesReceived += chunk.size();
        } else {
            qDebug() << "No data available yet, waiting...";
            socket->waitForReadyRead(100);  // Wait for more data
        }
    }

    if (imageData.isEmpty()) {
        saveToFile("No image received from Server.\n");
        showCustomMessageBox("No Data", "No image received from the server.", QMessageBox::Critical);
        exit(1);
    }
    saveToFile("Image received from Server.\n");

    // Create folder for image
    QString imageFolder = QDir::currentPath() + "/UploadedImages/";
    QDir().mkpath(imageFolder);

    // Create path for image
    QString imageName = "received_image.jpg";
    QString imagePath = imageFolder + imageName;

    // Remove image if already exists
    if (QFile::exists(imagePath)) {
        QFile::remove(imagePath);
    }

    // Save the received image
    QFile file(imagePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(imageData);
        file.close();
        saveToFile("Image saved.\n");
        return imagePath;
    } else {
        saveToFile("Couldn't save image.\n");
        showCustomMessageBox("File Error", "Failed to save image file.", QMessageBox::Critical);
        exit(1);
    }
}

bool Client::isAuthenticated() const
{
    return authenticated;
}

bool Client::saveToFile(const QString &content) {
    QString filePath = QDir::currentPath() + "/log.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QTextStream out(&file);
    out << "[" << timestamp << "] " << content;
    file.close();
    return true;
}

void Client::showImageInMessageBox(const QString &imagePath, const QString &title, const QString &message) {
    // Create a custom dialog
    QDialog msgBox;
    msgBox.setWindowTitle(title);

    // Log the image path to ensure it's correct
    qDebug() << "Image Path: " << imagePath;

    // Load the image
    QPixmap image(imagePath);

    // Check if the image was loaded successfully
    if (image.isNull()) {
        QMessageBox::critical(&msgBox, "Error", "Failed to load the image.");
        return;
    }

    // Log the original size of the image
    qDebug() << "Original Image Size: " << image.size();

    // Set a maximum size for the image to fit within the message box
    const int maxWidth = 600;
    const int maxHeight = 400;

    // Resize the image if it's too large
    if (image.width() > maxWidth || image.height() > maxHeight) {
        image = image.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        qDebug() << "Scaled Image Size: " << image.size();
    }

    // Create a QLabel to hold the image
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(image);
    imageLabel->setAlignment(Qt::AlignCenter);  // Center the image

    // Create another QLabel for the message text
    QLabel *textLabel = new QLabel(message);
    textLabel->setWordWrap(true);  // Allow text to wrap if it's too long
    textLabel->setAlignment(Qt::AlignCenter);  // Center the text at the bottom

    // Customize the layout of the message box
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);  // Add the image label
    layout->addWidget(textLabel);   // Add the text label

    // Set the layout to the dialog's layout
    msgBox.setLayout(layout);

    // Apply the custom stylesheet
    msgBox.setStyleSheet(
        "QDialog {"
        "background-color: #beb4e4;"
        "color: #7865c8;"
        "font-size: 16px;"
        "}"
        "QDialog QLabel {"
        "color: #8d7cd0;"
        "border-radius: 8px;"
        "padding: 8px 16px;"
        "font-size: 20px;"
        "font-weight: bold;"
        "}"
        "QDialog QPushButton {"
        "background-color: #8d7cd0;"
        "border-radius: 5px;"
        "color: #FAF6F0;"
        "padding: 5px;"
        "}"
        "QDialog QPushButton:hover {"
        "background-color: #7865c8;"
        "}");

    // Show the custom message dialog
    msgBox.exec();
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


