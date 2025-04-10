#include "home_screen.h"
#include "ui_home_screen.h"
#include "quiz_screen.h"
#include <QDir>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>

HomePage::HomePage(Client* client, QWidget* parent, QString userName) :
    QWidget(parent),
    ui(new Ui::HomePage),
    // csvCheckTimer(new QTimer(this)),
    userName(userName),
    client(client)
{
    ui->setupUi(this);

    // Set user's name from login
    ui->labelUserName->setText("Welcome, " + userName + "!");

    // Apply Drop Shadow Effect to the Frames (body_container only)
    QGraphicsDropShadowEffect* shadowEffect1 = new QGraphicsDropShadowEffect(this);
    shadowEffect1->setBlurRadius(30);
    shadowEffect1->setXOffset(0);
    shadowEffect1->setYOffset(0);
    shadowEffect1->setColor(QColor(120, 101, 200, 200));

    // Apply Drop Shadow Effect to the Frames (body_container only)
    QGraphicsDropShadowEffect* shadowEffect2 = new QGraphicsDropShadowEffect(this);
    shadowEffect2->setBlurRadius(30);
    shadowEffect2->setXOffset(0);
    shadowEffect2->setYOffset(0);
    shadowEffect2->setColor(QColor(120, 101, 200, 200));

    QGraphicsDropShadowEffect* shadowEffect3 = new QGraphicsDropShadowEffect(this);
    shadowEffect3->setBlurRadius(30);
    shadowEffect3->setXOffset(0);
    shadowEffect3->setYOffset(0);
    shadowEffect3->setColor(QColor(120, 101, 200, 200));

    ui->btnGenerateQuiz->setGraphicsEffect(shadowEffect1);  // Apply shadow effect
    ui->btnGenerateQuiz->setStyleSheet("QPushButton {"
        "background-color: #211726;"
        "color: #FAF6F0;"
        "}"
        "QPushButton:hover {"
        "background-color: #7865c8;"
        "}");

    // Load and set the SVG icon
    QSvgRenderer svgRenderer(QStringLiteral(":/assets/gemini-icon.svg"));
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer.render(&painter);
    ui->btnGenerateQuiz->setIcon(QIcon(pixmap));
    ui->btnGenerateQuiz->setIconSize(QSize(20, 20));

    ui->btnStartQuiz->setGraphicsEffect(shadowEffect2);
    ui->btnStartQuiz->setStyleSheet("QPushButton {"
        "background-color: #8d7cd0;"
        "color: #FAF6F0;"
        "}"
        "QPushButton:hover {"
        "background-color: #7865c8;"
        "}");
    ui->top_menubar->setGraphicsEffect(shadowEffect3);

    // Disable start button initially
    ui->btnStartQuiz->setEnabled(false);

    // // Setup CSV file check timer
    // connect(csvCheckTimer, &QTimer::timeout, this, &HomePage::checkForCSVFile);
}

HomePage::~HomePage()
{
    delete ui;
    //delete csvCheckTimer;
}

void HomePage::on_btnUploadPDF_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select PDF File", "", "PDF Files (*.pdf)");

    if (filePath.isEmpty()) {
        return;  // User canceled file selection
    }

    QString destinationFolder = QDir::currentPath() + "/UploadedPDFs/";
    QDir().mkpath(destinationFolder); // Ensure the directory exists

    // Define the new file path
    QString newFilePath = destinationFolder + QFileInfo(filePath).fileName();

    // Ensure the file is not already copied
    if (QFile::exists(newFilePath)) {
        QFile::remove(newFilePath);  // Remove existing file before copying
    }

    if (QFile::copy(filePath, newFilePath)) {
        ui->labelPDFStatus->setText("File Uploaded: " + QFileInfo(newFilePath).fileName());
        pdfFilePath = newFilePath; // Store the PDF path
    }
    else {
        showCustomMessageBox("Upload Failed", "Could not save the file!", QMessageBox::Warning);
    }
}

void HomePage::on_btnGenerateQuiz_clicked()
{
    if (pdfFilePath.isEmpty()) {
        showCustomMessageBox("No PDF Selected", "Please upload a PDF before generating the quiz.", QMessageBox::Warning);
        return;
    }

    // Disable buttons while processing
    ui->btnUploadPDF->setEnabled(false);
    ui->btnGenerateQuiz->setEnabled(false);
    ui->btnStartQuiz->setEnabled(false);

    // Simulate sending PDF to server (Backend handles this)
    showCustomMessageBox("Quiz Generation", "The quiz is being generated. Please wait...", QMessageBox::Information);

    // Send the pdf to the server
    client->sendPDF(pdfFilePath);
    qDebug() << "packet sent to server";

    // Receive CSV response from server
    client->receiveCSV();
    qDebug() << "Received csv from server";

    // Enable Start Quiz button once CSV is received
    ui->btnStartQuiz->setEnabled(true);
    showCustomMessageBox("Quiz Ready", "Quiz generated successfully! You can now start.", QMessageBox::Information);

}

// void HomePage::checkForCSVFile()
// {
//     QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
//     QDir dir(csvFolder);
//     QStringList csvFiles = dir.entryList(QStringList() << "*.csv", QDir::Files);

//     if (!csvFiles.isEmpty()) {
//         // CSV found, stop timer
//         csvCheckTimer->stop();

//         // Enable Start button
//         ui->btnStartQuiz->setEnabled(true);
//         showCustomMessageBox("Quiz Ready", "Quiz generated successfully! You can now start.", QMessageBox::Information);
//     }
// }

void HomePage::on_btnStartQuiz_clicked()
{
    qDebug() << "Starting QuizScreen";

    // Avoid creating multiple instances
    static QuizScreen* quizScreen = nullptr;

    if (quizScreen == nullptr) {
        quizScreen = new QuizScreen(client, nullptr, userName);
        quizScreen->loadQuestionsFromCSV(QDir::currentPath() + "/UploadedPDFs/mcq_output.csv");
        quizScreen->show();
    }
    else {
        quizScreen->raise();
        quizScreen->activateWindow();
    }

    this->close(); // Hide the home screen if necessary
}

void HomePage::showCustomMessageBox(const QString& title, const QString& text, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setIcon(icon);

    msgBox.setMinimumSize(350, 250);

    msgBox.setStyleSheet("QMessageBox {"
        "background-color: #beb4e4;"
        "color: #7865c8;"
        "font-size: 16px;"
        "}"
        "QMessageBox QLabel {"
        "color: #FAF6F0;"
        "}"
        "QMessageBox QPushButton {"
        "background-color: #ada1dd;"
        "border-radius: 5px;"
        "color: #FAF6F0;"
        "padding: 5px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "background-color: #7865c8;"
        "}");

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(&msgBox);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    msgBox.setGraphicsEffect(shadowEffect);

    msgBox.setAttribute(Qt::WA_StyledBackground);

    msgBox.exec();
}
