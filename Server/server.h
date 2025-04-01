#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

enum SessionState {
    WAITING_FOR_LOGIN,
    IN_PROGRESS,
    FINISHED
};

struct Session {
    QString username;
    int currentQuestionIndex = 0;
    int score = 0;
    SessionState state = WAITING_FOR_LOGIN;
    QStringList correctAnswers;
};

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void handleClient();
    void receiveFile();
    void disconnectClient();

private:
    QMap<QTcpSocket*, Session*> sessions;
};

#endif // SERVER_H
