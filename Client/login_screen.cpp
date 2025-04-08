#include "login_screen.h"
#include "ui_login_screen.h"
#include "QPixmap"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QMessageBox>

MainWindow::MainWindow(Client *client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), client(client)
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

    // Apply styling to Login button
    ui->Login_Btn->setStyleSheet("QPushButton {"
                                 "background-color: #211726;"
                                 "border-radius: 8px;"
                                 "color: #FAF6F0;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #7865c8;"
                                 "}");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->User_name_txtfield->text();
    QString password = ui->Password_txtfield->text();

    if(client->authenticate(username, password)) {
        showCustomMessageBox("Login", "Login successful!", QMessageBox::Information);

        // Open HomePage and pass the user's name
        HomePage *homePage = new HomePage(client, nullptr, username);
        homePage->show();
        this->close();  // Close login window
    } else {
        showCustomMessageBox("Login", "Invalid username or password!", QMessageBox::Warning);
    }
}

void MainWindow::showCustomMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setIcon(icon);

    // Set a larger minimum size for the message box
    msgBox.setMinimumSize(350, 250);

    // Apply custom stylesheet
    msgBox.setStyleSheet("QMessageBox {"
                         "background-color: #beb4e4;"
                         "color: #7865c8;"
                         "font-size: 16px;"
                         "}"
                         "QMessageBox QLabel {"
                         "color: #FAF6F0;"
                         "}"
                         "QMessageBox QPushButton {"
                         "background-color: #8d7cd0;"
                         "border-radius: 5px;"
                         "color: #FAF6F0;"
                         "padding: 5px;"
                         "}"
                         "QMessageBox QPushButton:hover {"
                         "background-color: #7865c8;"
                         "}");

    // Apply drop shadow effect
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(&msgBox);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    msgBox.setGraphicsEffect(shadowEffect);

    // Ensure the background is fully transparent around the rounded corners
    msgBox.setAttribute(Qt::WA_StyledBackground);

    msgBox.exec();
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
