#include <QApplication>
#include "login_screen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    return a.exec();
}
