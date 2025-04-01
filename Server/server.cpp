#include "server.h"
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QTextStream>
#include <iostream>

#define PORT 27000

Server::Server(QObject *parent) : QTcpServer(parent) {
    if (this->listen(QHostAddress::Any, PORT)) {
        std::cout << "Server started. Listening on port " << PORT << std::endl;
    } else {
        std::cerr << "Server failed to start!" << std::endl;
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    Session *session = new Session();
    sessions[socket] = session;

    connect(socket, &QTcpSocket::readyRead, this, &Server::handleClient);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectClient);

    std::cout << "New client connected." << std::endl;
}

void Server::handleClient() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket || !sessions.contains(socket)) return;

    Session *session = sessions[socket];
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data).trimmed();

    if (message.startsWith("AUTH")) {
        QStringList parts = message.split(',');
        if (parts.size() >= 4) {
            QString username = parts[2];
            session->username = username;
            session->state = IN_PROGRESS;

            // Load correct answers from CSV file
            QString csvFilePath = "pdf_mcq_generator/output/mcq_output.csv";
            QFile file(csvFilePath);
            if (file.open(QIODevice::ReadOnly)) {
                QTextStream in(&file);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList cols = line.split(',');
                    if (cols.size() >= 2) {
                        session->correctAnswers.append(cols[1].trimmed());
                    }
                }
                file.close();
            }

            socket->write("Authentication successful");
        } else {
            socket->write("Invalid authentication packet.");
        }

    } else if (session->state == IN_PROGRESS && message.startsWith("ANSWER")) {
        QStringList parts = message.split(',');
        if (parts.size() < 2) {
            socket->write("Invalid answer format.");
            return;
        }

        QString userAnswer = parts[1].trimmed().toUpper();
        int qIndex = session->currentQuestionIndex;

        if (qIndex < session->correctAnswers.size()) {
            QString correct = session->correctAnswers[qIndex].toUpper();
            if (userAnswer == correct) {
                session->score++;
                socket->write("Correct!\n");
            } else {
                socket->write(QString("Wrong! Correct answer was: %1\n").arg(correct).toUtf8());
            }
            session->currentQuestionIndex++;
        }

        if (session->currentQuestionIndex >= session->correctAnswers.size()) {
            session->state = FINISHED;
            QString result = QString("Quiz finished. Your score: %1/%2\n")
                                 .arg(session->score)
                                 .arg(session->correctAnswers.size());
            socket->write(result.toUtf8());
        } else {
            socket->write("Next question...\n");
        }
    } else {
        socket->write("Invalid or unexpected input.\n");
    }
}

void Server::receiveFile() {
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

void Server::disconnectClient() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    std::cout << "Client disconnected.\n";
    if (sessions.contains(socket)) {
        delete sessions[socket];
        sessions.remove(socket);
    }

    socket->deleteLater();
}
