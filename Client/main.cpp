#include <QApplication>
#include "login_screen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int result = 0;

    Client *client = new Client();
    if(client->connectToServer()) {
        MainWindow w(client);
        //MainWindow w;
        w.setAttribute(Qt::WA_TranslucentBackground);
        w.show();
        result = a.exec();
    }

    //Safely deletes the client before exiting
    delete client;

    return result;
}
