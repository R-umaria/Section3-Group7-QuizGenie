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
    void initTestCase() {
        // Use a temporary directory
        QVERIFY(m_tempDir.isValid());
        QDir::setCurrent(m_tempDir.path());
    }

    void cleanupTestCase() {
        QFile::remove("log.txt");
    }

    // Test saveToFile
    void testSaveToFile() {
        Client client;
        bool saved = client.saveToFile("Test log message.\n");
        QVERIFY(saved);

        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString content = file.readAll();
        file.close();
        QVERIFY(content.contains("Test log message."));
        remove("log.txt");
    }

    // Test connection failure
    void testConnectToServerFailure() {
        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(!connected);

        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Couldn't connect to Server."));
        remove("log.txt");
    }

    // Test connection success
    void testConnectToServerSuccess() {
        // Dummy server
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;

        // Timer to allow server to connect
        QTimer::singleShot(50, [&]() {
        });
        bool connected = client.connectToServer();
        QVERIFY(connected);

        // Verify that the server received a connection
        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);
        serverSocket->disconnectFromHost();
        server.close();
    }

    // Test authentication failure
    void testAuthenticationFailure() {
        // Dummy server
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        // Connect the client.
        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(connected);

        // Wait for the authentication packet from the client
        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);

        // Instead of disconnecting, send invalid
        serverSocket->write("Authentication failed");
        serverSocket->flush();

        // Disconnect the server
        serverSocket->disconnectFromHost();
        server.close();

        bool authResult = client.authenticate("user", "wrongpassword");
        QVERIFY(!authResult);

        // Verify correct log entry was created
        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Invalid login received from Server."));
        remove("log.txt");
    }

    // Test sendScore functionality
    void testSendScoreSuccess() {
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;
        QTimer::singleShot(50, [](){});
        bool connected = client.connectToServer();
        QVERIFY(connected);

        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);
        server.close();

        client.sendScore("10");

        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("Score sent to server."));
        remove("log.txt");
    }

    // Test receiveCSV functionality
    void testReceiveCSV() {
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(connected);

        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);

        // Send dummy CSV data.
        QString dummyCSV = "Question,OptionA,OptionB,OptionC,OptionD,Answer\nWhat is 2+2?,3,4,5,6,4\n";
        serverSocket->write(dummyCSV.toUtf8());
        serverSocket->flush();
        serverSocket->disconnectFromHost();
        server.close();

        client.receiveCSV();

        // Check that the CSV file exists and contains the expected content.
        QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
        QString csvFilePath = csvFolder + "mcq_output.csv";
        QFile csvFile(csvFilePath);
        QVERIFY(csvFile.exists());
        QVERIFY(csvFile.open(QIODevice::ReadOnly | QIODevice::Text));
        QString csvContent = csvFile.readAll();
        csvFile.close();
        QVERIFY(csvContent.contains("Question,OptionA,OptionB,OptionC,OptionD,Answer"));
        remove("mcq_output.csv");
    }

    // Test receiveImage
    void testReceiveImage() {
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(connected);

        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);

        // Simulate sending image data.
        // For simplicity, use dummy image data.
        QByteArray imageData = "dummyimagedata";
        int fileSize = imageData.size();
        QByteArray fileSizeBytes(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
        serverSocket->write(fileSizeBytes);
        serverSocket->write(imageData);
        serverSocket->flush();
        serverSocket->disconnectFromHost();
        server.close();

        QString imagePath = client.receiveImage();
        QFile imageFile(imagePath);
        QVERIFY(imageFile.exists());
        // Optionally, verify that the file size matches the dummy image data.
        QVERIFY(imageFile.open(QIODevice::ReadOnly));
        QByteArray readData = imageFile.readAll();
        imageFile.close();
        QCOMPARE(readData.size(), imageData.size());
        remove("log.txt");
    }

    // Test failure to receiveCSV functionality
    void testReceiveCSVFailure() {
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress(SERVER_IP), SERVER_PORT));

        TestClient client;
        bool connected = client.connectToServer();
        QVERIFY(connected);

        QTcpSocket *serverSocket = server.nextPendingConnection();
        QVERIFY(serverSocket != nullptr);

        client.receiveCSV();

        serverSocket->flush();
        serverSocket->disconnectFromHost();
        server.close();

        // Verify correct log entry was created
        QFile file("log.txt");
        QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
        QString logContent = file.readAll();
        file.close();
        QVERIFY(logContent.contains("No CSV received from Server."));
        remove("log.txt");
    }

    // Additional tests for methods like sendPDF, receiveCSV, or receiveImage
    // would require further refactoring (or dummy server responses) to simulate the network behavior.

private:
    QTemporaryDir m_tempDir;
};

QTEST_MAIN(ClientTest)
#include "tst_clienttests.moc"
