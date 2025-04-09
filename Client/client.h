#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QMessageBox>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    bool connectToServer();
    bool authenticate(const QString &username, const QString &password);
    void sendPDF(const QString &pdfFilePath);
    void receiveCSV();
    QString receiveImage();
    bool isAuthenticated() const;
    void showImageInMessageBox(const QString &imagePath, const QString &title, const QString &text);
    void sendScore(QString score);
    bool saveToFile(const QString &content);

private:
    QTcpSocket *socket;
    bool authenticated;
    void showCustomMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon);
};

#endif // CLIENT_H
