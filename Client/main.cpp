#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client *client = new Client();
    client->connectToServer();

    MainWindow w(client);
    w.show();
    int result = a.exec();

    //Safely deletes the client before exiting
    delete client;

    return result;
}
