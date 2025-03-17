#include <QApplication>
#include <QMainWindow>
#include <QTcpSocket>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

class Client : public QMainWindow {
    Q_OBJECT
public:
    Client(QWidget *parent = nullptr) : QMainWindow(parent) {
        socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
        connect(socket, &QTcpSocket::readyRead, this, &Client::receiveCSV);
    }

    void sendPDF() {
        QString filePath = QFileDialog::getOpenFileName(this, "Select PDF", "", "PDF Files (*.pdf)");
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Failed to open PDF file!");
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();

        socket->connectToHost(SERVER_IP, SERVER_PORT);
        if (!socket->waitForConnected(3000)) {
            QMessageBox::warning(this, "Error", "Failed to connect to server!");
            return;
        }

        socket->write(fileData);
        socket->flush();
    }

private slots:
    void onConnected() {
        std::cout << "Connected to server!" << std::endl;
    }

    void receiveCSV() {
        QByteArray csvData = socket->readAll();
        QString outputDir = "received_csv/";
        QDir().mkpath(outputDir);
        QString filePath = outputDir + "generated.csv";
        
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(csvData);
            file.close();
            QMessageBox::information(this, "Success", "CSV received successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to save CSV file!");
        }

        displayQuestions(filePath);
    }

    void displayQuestions(const QString &filePath) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Error", "Could not open CSV file.");
            return;
        }

        QTextStream in(&file);
        QStringList questions;
        while (!in.atEnd() && questions.size() < 10) {
            questions.append(in.readLine());
        }
        file.close();

        QString output = "Mock Questions:\n";
        for (const QString &q : questions) {
            output += q + "\n";
        }

        QMessageBox::information(this, "QuizGenie - Mock Questions", output);
    }

private:
    QTcpSocket *socket;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Client client;
    client.show();
    return app.exec();
}
