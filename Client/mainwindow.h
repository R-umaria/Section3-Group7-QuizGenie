#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "homepage.h"
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

private slots:
    void on_loginButton_clicked();  // Function to handle login

private:
    Ui::MainWindow *ui;
    Client *client;

};
#endif // MAINWINDOW_H
