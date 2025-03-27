#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QMovie>
#include <QTimer>
#include "quizscreen.h"
#include "client.h"


namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(Client *client, QWidget *parent = nullptr, QString userName = "");
    ~HomePage();

private slots:
    void on_btnUploadPDF_clicked();
    void on_btnGenerateQuiz_clicked();
    void on_btnStartQuiz_clicked();
    void checkForCSVFile(); // Checks if CSV exists

private:
    Ui::HomePage *ui;
    QString pdfFilePath;
    QMovie *loadingMovie;
    QTimer *csvCheckTimer;
    QString userName;
    Client *client;
};

#endif // HOMEPAGE_H
