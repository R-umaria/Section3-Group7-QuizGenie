#include "home_screen.h"
#include "ui_home_screen.h"
#include "quiz_screen.h"
#include <QDir>
//#include <QDebug>
#include <QGraphicsDropShadowEffect>

HomePage::HomePage(Client *client, QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::HomePage),
    loadingMovie(nullptr),
    csvCheckTimer(new QTimer(this)),
    userName(userName),
    client(client)
{
    ui->setupUi(this);

    // Set user's name from login
    ui->labelUserName->setText("Welcome, " + userName + "!");

    // Apply Drop Shadow Effect to the Frames (body_container only)
    QGraphicsDropShadowEffect *shadowEffect1 = new QGraphicsDropShadowEffect(this);
    shadowEffect1->setBlurRadius(30);
    shadowEffect1->setXOffset(0);
    shadowEffect1->setYOffset(0);
    shadowEffect1->setColor(QColor(120, 101, 200, 200));

    // Apply Drop Shadow Effect to the Frames (body_container only)
    QGraphicsDropShadowEffect *shadowEffect2 = new QGraphicsDropShadowEffect(this);
    shadowEffect2->setBlurRadius(30);
    shadowEffect2->setXOffset(0);
    shadowEffect2->setYOffset(0);
    shadowEffect2->setColor(QColor(120, 101, 200, 200));

    QGraphicsDropShadowEffect *shadowEffect3 = new QGraphicsDropShadowEffect(this);
    shadowEffect3->setBlurRadius(30);
    shadowEffect3->setXOffset(0);
    shadowEffect3->setYOffset(0);
    shadowEffect3->setColor(QColor(120, 101, 200, 200));

    ui->btnGenerateQuiz->setGraphicsEffect(shadowEffect1);  // Apply shadow efect
    ui->btnStartQuiz->setGraphicsEffect(shadowEffect2);
    ui->top_menubar->setGraphicsEffect(shadowEffect3);

    // Connect button signals
        //don't need to be connected, QT does it automatically
    //connect(ui->btnUploadPDF, &QPushButton::clicked, this, &HomePage::on_btnUploadPDF_clicked);
    //connect(ui->btnGenerateQuiz, &QPushButton::clicked, this, &HomePage::on_btnGenerateQuiz_clicked);
    //connect(ui->btnStartQuiz, &QPushButton::clicked, this, &HomePage::on_btnStartQuiz_clicked);

    // Disable start button initially
    ui->btnStartQuiz->setEnabled(false);

    // Create a loading spinner
    loadingMovie = new QMovie(":/assets/loading.gif");
    ui->labelLoading->setMovie(loadingMovie);
    ui->labelLoading->setVisible(false);

    // Setup CSV file check timer
    connect(csvCheckTimer, &QTimer::timeout, this, &HomePage::checkForCSVFile);
}

HomePage::~HomePage()
{
    delete ui;
    delete loadingMovie;
    delete csvCheckTimer;
}

void HomePage::on_btnUploadPDF_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select PDF File", "", "PDF Files (*.pdf)");

    if (filePath.isEmpty()) {
        return;  // User canceled file selection
    }

    // Define the destination folder
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
    } else {
        QMessageBox::warning(this, "Upload Failed", "Could not save the file!");
    }
}

void HomePage::on_btnGenerateQuiz_clicked()
{
    if (pdfFilePath.isEmpty()) {
        QMessageBox::warning(this, "No PDF Selected", "Please upload a PDF before generating the quiz.");
        return;
    }

    //Send the pdf to the server
    client->sendPDF(pdfFilePath);

    // Show loading spinner
    ui->labelLoading->setVisible(true);
    loadingMovie->start();

    // Disable buttons while processing
    ui->btnUploadPDF->setEnabled(false);
    ui->btnGenerateQuiz->setEnabled(false);
    ui->btnStartQuiz->setEnabled(false);

    // Simulate sending PDF to server (Backend handles this)
    QMessageBox::information(this, "Quiz Generation", "The quiz is being generated. Please wait...");

    //Receive CSV response from server
    client->receiveCSV();

    // Start checking for CSV every 3 seconds
    csvCheckTimer->start(3000);
}

void HomePage::checkForCSVFile()
{
    QString csvFolder = QDir::currentPath() + "/UploadedPDFs/";
    QDir dir(csvFolder);
    QStringList csvFiles = dir.entryList(QStringList() << "*.csv", QDir::Files);

    if (!csvFiles.isEmpty()) {
        // CSV found, stop timer
        csvCheckTimer->stop();

        // Hide loading spinner
        loadingMovie->stop();
        ui->labelLoading->setVisible(false);

        // Enable Start button
        ui->btnStartQuiz->setEnabled(true);
        QMessageBox::information(this, "Quiz Ready", "Quiz generated successfully! You can now start.");
    }
}

void HomePage::on_btnStartQuiz_clicked()
{
    qDebug() << "Starting QuizScreen";

    // Avoid creating multiple instances
    static QuizScreen *quizScreen = nullptr;

    if (quizScreen == nullptr) {
        quizScreen = new QuizScreen(nullptr, "Admin");
        quizScreen->loadQuestionsFromCSV(QDir::currentPath() + "/UploadedPDFs/mcq_output.csv");
        quizScreen->show();
    } else {
        quizScreen->raise();
        quizScreen->activateWindow();
    }

    this->close(); // Hide the home screen if necessary
}
