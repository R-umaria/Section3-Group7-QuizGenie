#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "homepage.h"
MainWindow::MainWindow(Client *client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    client(client)
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

    //pass the entered username and password to the client
    if (client->authenticate(username, password)) {
        QMessageBox::information(this, "Login", "Login successful!");

        // Open HomePage and pass the user's name
        HomePage *homePage = new HomePage(client, nullptr, "Admin User");
        homePage->show();
        this->close();  // Close login window
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password!");
    }
}
