#include <QApplication>
#include "login_screen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client *client = new Client();
    client->connectToServer();

    MainWindow w(client);
    //MainWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    int result = a.exec();

    //Safely deletes the client before exiting
    delete client;

    return result;
}
