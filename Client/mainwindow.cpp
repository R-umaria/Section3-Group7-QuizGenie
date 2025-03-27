#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/assets/Logo.png");
    int w = ui->Logo->width ();
    int h = ui->Logo->height ();
    ui->Logo->setPixmap (pix.scaled(w,h,Qt::KeepAspectRatio)); //to display Logo

    // Connect login button to slot
    connect(ui->Login_Btn, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->User_name_txtfield->text();
    QString password = ui->Password_txtfield->text();

    if (username == "admin" && password == "1234") {
        QMessageBox::information(this, "Login", "Login successful!");

        // Open HomePage and pass the user's name
        HomePage *homePage = new HomePage(nullptr, "Admin User");
        homePage->show();
        this->close();  // Close login window
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password!");
    }
}
