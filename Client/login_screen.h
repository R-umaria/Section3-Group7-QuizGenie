#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QMainWindow>
#include <QMessageBox>
#include "home_screen.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client *client, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_loginButton_clicked();  // Function to handle login

private:
    Ui::MainWindow *ui;
    Client *client;
};

#endif // LOGIN_SCREEN_H
