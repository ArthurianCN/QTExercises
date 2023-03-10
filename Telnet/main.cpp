#include "Telnet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Telnet w;
    w.show();
    return a.exec();
}
