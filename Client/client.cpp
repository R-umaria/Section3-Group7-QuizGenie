#include "client.h"
#include <QFile>
#include <QMessageBox>

const QString SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 27000;

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)), authenticated(false) {

}

Client::~Client()
{
    // Ensure that the socket is properly cleaned up
    if (socket) {
        socket->disconnectFromHost();
        delete socket;  // Delete the socket
    }
}

void Client::connectToServer() {
    socket->connectToHost(SERVER_IP, SERVER_PORT);
    if (!socket->waitForConnected(3000)) {
        QMessageBox::critical(nullptr, "Connection Failed", "Unable to connect to the server!");
        exit(1);
    }
}

bool Client::authenticate(const QString &username, const QString &password)
{
    //////for auth
    QByteArray packet;

    QByteArray packetType = "AUTH";
        //maybe change depending on server parsing
    QByteArray data = username.toUtf8() + "," + password.toUtf8();
    qint64 dataSize = static_cast<qint64>(data.size());
    QByteArray dataSizeStr = QByteArray::number(dataSize);
    packet.append(packetType);
    packet.append(",");
    packet.append(dataSizeStr);
    packet.append(",");
    packet.append(data);

    socket->write(packet);
    //////

    //socket->write(username.toUtf8() + "\n" + password.toUtf8());

    if (!socket->waitForBytesWritten()) {
        QMessageBox::critical(nullptr, "Send Error", "Error sending authentication data!");
        return false;
    }

    socket->waitForReadyRead();
    QByteArray authResponse = socket->readAll();
    if (authResponse == "Authentication successful") {
        authenticated = true;
    } else {
        authenticated = false;
    }
    return true;
}

void Client::sendPDF(const QString &filePath)
{
    if (!authenticated) {
        QMessageBox::warning(nullptr, "Not Authenticated", "You must authenticate first!");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "File Error", "Unable to open the PDF file!");
        return;
    }

    QByteArray fileData = file.readAll();
    QByteArray dataSizeStr = QByteArray::number(fileData.size());
    socket->connectToHost("127.0.0.1", 27000);  // Reconnect for file transfer

    socket->write(fileData);

    if (!socket->waitForBytesWritten()) {
        QMessageBox::critical(nullptr, "Send Error", "Error sending file to the server!");
    }

    socket->disconnectFromHost();
}

bool Client::isAuthenticated() const
{
    return authenticated;
}
