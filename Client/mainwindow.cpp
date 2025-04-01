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

void MainWindow::on_loginButton_clicked() {
    QString username = ui->User_name_txtfield->text();
    QString password = ui->Password_txtfield->text();

    // Test bypass for admin
    if (username == "admin" && password == "1234") {
        QMessageBox::information(this, "Login", "Login successful (test bypass)");

        // 🔐 Do real authentication too (send username to server)
        client->authenticate(username, password);

        // Use local variable instead of class-level homePage
        HomePage *homePage = new HomePage(client, nullptr, "Admin User");
        homePage->show();
        this->close();
        return;
    }

    // Optional: for other users if needed
    QMessageBox::warning(this, "Login", "Invalid username or password!");
}
