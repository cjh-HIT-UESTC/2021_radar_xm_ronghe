#include "udpget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    udpget w;
    w.show();
    return a.exec();
}
