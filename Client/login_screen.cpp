#include "login_screen.h"
#include "ui_login_screen.h"
#include "QPixmap"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Make the main window background transparent to allow gradient to be seen
    this->setAttribute(Qt::WA_TranslucentBackground);

    // Load the logo
    QPixmap pix(":/assets/Logo.png");
    int w = ui->Logo->width();
    int h = ui->Logo->height();

    // Apply smooth scaling
    QPixmap scaledPixmap = pix.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a rounded pixmap with radius 20px
    QPixmap roundedPixmap(w, h);
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(0, 0, w, h, 20, 20);  // Rounded corners with 20px radius
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, scaledPixmap);
    painter.end();

    // Set the modified pixmap to the QLabel
    ui->Logo->setPixmap(roundedPixmap);

    // Apply Drop Shadow Effect to the Frames (body_container only)
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(30);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(120, 101, 200, 40));

    ui->body_container->setGraphicsEffect(shadowEffect);  // Apply shadow to the Login Form

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
        HomePage *homePage = new HomePage(nullptr, "Admin");
        homePage->show();
        this->close();  // Close login window
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password!");
    }
}

// Paint Event for the Central Widget (not the QMainWindow)
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Create a radial gradient to simulate a conic gradient
    QRadialGradient gradient(width() / 2, height() / 2, qMax(width(), height()));
    gradient.setColorAt(0.0, QColor("#e8dfec"));
    gradient.setColorAt(0.5, QColor("#7865c8"));
    gradient.setColorAt(1.0, QColor("#7865c8"));

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRect(this->rect());
}
