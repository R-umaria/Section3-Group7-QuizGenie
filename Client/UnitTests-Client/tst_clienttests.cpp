// tst_clienttests.cpp

#include <QtTest>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTemporaryDir>
#include <QTimer>

// Include your client header (adjust the path as needed)
#include "client.h"

// If your client.cpp defines SERVER_IP and SERVER_PORT only there,
// you may optionally define them here as well for testing purposes:
#ifndef SERVER_IP
#define SERVER_IP "127.0.0.1"
#endif
#ifndef SERVER_PORT
#define SERVER_PORT 27000
#endif

// Subclass Client for testing so that UI dialogs are not shown.
class TestClient : public Client {
    Q_OBJECT
public:
    TestClient(QObject *parent = nullptr)
        : Client(parent)
    {
    }

    // Override the UI functions so that no dialogs appear during tests.
    void showCustomMessageBox(const QString &title,
                                      const QString &text,
                                      QMessageBox::Icon icon)
    {
        m_lastMsgTitle = title;
        m_lastMsgText = text;
        m_lastMsgIcon = icon;
    }

    void showImageInMessageBox(const QString & /*imagePath*/,
                                       const QString &title,
                                       const QString &message)
    {
        m_lastMsgTitle = title;
        m_lastMsgText = message;
    }

    // Members to record what message would have been shown.
    QString m_lastMsgTitle;
    QString m_lastMsgText;
    QMessageBox::Icon m_lastMsgIcon;
};

class ClientTest : public QObject {
    Q_OBJECT

private slots:
    // This function is called once before all tests run.
    void initTestCase() {
        // Use a temporary directory as the working directory so your log.txt
        // and other output files do not clash with your project files.
        QVERIFY(m_tempDir.isValid());
        QDir::setCurrent(m_tempDir.path());
    }

    // This function is called once after all tests run.
    void cleanupTestCase() {
        QFile::remove("log.txt");
    }

    // Test the saveToFile function.
    void testSaveToFile() {
        Client client;
        bool saved = client.saveToFile("Test log message.\n");
        QVERIFY(saved);

        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString content = file.readAll();
        file.close();
        QVERIFY(content.contains("Test log message."));
    }

    // Test connection failure when no server is running.
    void testConnectToServerFailure() {
        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(!connected);
        // Optionally, verify that an error message was logged.
        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Couldn't connect to Server."));
    }

    // Test connection success using a dummy server.
    void testConnectToServerSuccess() {
        QTcpServer server;
        // Listen on the same IP and port used in the client.
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;
        // Start connection attempt; QTimer::singleShot can allow the server time to process.
        QTimer::singleShot(50, [&]() {
            // No additional work needed here; simply allow the client to connect.
        });
        bool connected = client.connectToServer();
        QVERIFY(connected);

        // Verify that the server received a connection.
        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);
        serverSocket->disconnectFromHost();
        server.close();
    }

    // Test authentication failure when no proper server response is provided.
    void testAuthenticationFailure() {
        TestClient client;
        // Without a valid server connection, authentication should fail.
        bool connected = client.connectToServer();
        QVERIFY(!connected);
        bool authResult = client.authenticate("user", "wrongpassword");
        QVERIFY(!authResult);

        // Verify that a log entry for invalid login is created.
        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Invalid login received from Server."));
    }

    // Test sendScore functionality without a valid connection.
    void testSendScoreFailure() {
        TestClient client;
        client.sendScore("10");

        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Couldn't send score to Server."));
    }

    // Additional tests for methods like sendPDF, receiveCSV, or receiveImage
    // would require further refactoring (or dummy server responses) to simulate the network behavior.

private:
    QTemporaryDir m_tempDir;
};

QTEST_MAIN(ClientTest)
#include "tst_clienttests.moc"
