#include "homepage.h"
#include "ui_homepage.h"
#include <QDir>
//#include <QDebug>

HomePage::HomePage(Client *client, QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::HomePage),
    loadingMovie(nullptr),
    csvCheckTimer(new QTimer(this)),
    userName(userName),
    client(client)
{
    ui->setupUi(this);

    QPixmap pix(":/assets/logo_horizontal.png");
    ui->logo_horizontal->setPixmap(pix.scaled(ui->logo_horizontal->width(), ui->logo_horizontal->height(), Qt::KeepAspectRatio));

    // Set user's name from login
    ui->labelUserName->setText("Welcome, " + userName);

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
    QuizScreen *quizScreen = new QuizScreen(this, userName);
    quizScreen->show();
    this->close();
}


