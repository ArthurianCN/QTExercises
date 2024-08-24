#include "systemhunter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	SystemHunter w;
    w.show();
    return a.exec();
}
