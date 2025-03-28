#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    void connectToServer();
    bool authenticate(const QString &username, const QString &password);
    void sendPDF(const QString &pdfFilePath);
    void receiveCSV();
    bool isAuthenticated() const;

private:
    QTcpSocket *socket;
    bool authenticated;
};

#endif // CLIENT_H
