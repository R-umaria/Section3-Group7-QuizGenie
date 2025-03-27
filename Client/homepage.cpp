#include "homepage.h"
#include "ui_homepage.h"
#include <QDir>

HomePage::HomePage(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::HomePage),
    loadingMovie(nullptr),
    csvCheckTimer(new QTimer(this))
{
    ui->setupUi(this);
    QPixmap pix(":/assets/logo_horizontal.png");
    int w = ui->logo_horizontal->width ();
    int h = ui->logo_horizontal->height ();
    ui->logo_horizontal->setPixmap (pix.scaled(w,h,Qt::KeepAspectRatio));

    // Set user's name from login
    ui->labelUserName->setText("Welcome, " + userName);

    // Connect button signals
    connect(ui->btnUploadPDF, &QPushButton::clicked, this, &HomePage::on_btnUploadPDF_clicked);
    connect(ui->btnGenerateQuiz, &QPushButton::clicked, this, &HomePage::on_btnGenerateQuiz_clicked);
    connect(ui->btnStartQuiz, &QPushButton::clicked, this, &HomePage::on_btnStartQuiz_clicked);

    // Disable start button initially
    ui->btnStartQuiz->setEnabled(false);

    // Create a loading spinner
    loadingMovie = new QMovie(":/assets/loading.gif"); // Ensure you have a loading GIF
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
        return;  // No file selected
    }

    // Define the destination folder
    QString destinationFolder = QDir::currentPath() + "/UploadedPDFs/";
    QDir().mkpath(destinationFolder); // Ensure the directory exists

    // Define the new file path
    QString newFilePath = destinationFolder + QFileInfo(filePath).fileName();

    // Copy the file to the destination folder
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

    // Show loading spinner
    ui->labelLoading->setVisible(true);
    loadingMovie->start();

    // Disable buttons while processing
    ui->btnUploadPDF->setEnabled(false);
    ui->btnGenerateQuiz->setEnabled(false);
    ui->btnStartQuiz->setEnabled(false);

    // Simulate sending PDF to server (Backend handles this)
    QMessageBox::information(this, "Quiz Generation", "The quiz is being generated. Please wait...");

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
    QMessageBox::information(this, "Start Quiz", "The quiz will start now!");

    // Here, transition to the quiz page
}
