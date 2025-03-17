#include <iostream>
#include <fstream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include <QDir>

#define PORT 12345

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr) : QTcpServer(parent) {
        if (this->listen(QHostAddress::Any, PORT)) {
            std::cout << "Server started. Listening on port " << PORT << std::endl;
        } else {
            std::cerr << "Server failed to start!" << std::endl;
        }
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, &QTcpSocket::readyRead, this, &Server::receiveFile);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }

private slots:
    void receiveFile() {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        if (!socket) return;

        QByteArray data = socket->readAll();
        QString inputDir = "pdf_mcq_generator/input/";
        QDir().mkpath(inputDir);
        QString filePath = inputDir + "received.pdf";

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.close();
            std::cout << "PDF file received and saved: " << filePath.toStdString() << std::endl;
        } else {
            std::cerr << "Failed to save PDF file!" << std::endl;
            return;
        }

        // Run Python script to process the file
        QProcess process;
        process.start("python3", QStringList() << "pdf_mcq_generator/main.py" << filePath);
        process.waitForFinished();

        // Path to the generated CSV
        QString csvFilePath = "pdf_mcq_generator/output/mcq_output.csv";
        QFile csvFile(csvFilePath);
        if (csvFile.open(QIODevice::ReadOnly)) {
            QByteArray csvData = csvFile.readAll();
            csvFile.close();
            socket->write(csvData);
            socket->flush();
            socket->waitForBytesWritten();
            std::cout << "CSV file sent to client: " << csvFilePath.toStdString() << std::endl;
        } else {
            std::cerr << "Failed to read CSV file!" << std::endl;
        }

        socket->close();
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    Server server;
    return app.exec();
}
