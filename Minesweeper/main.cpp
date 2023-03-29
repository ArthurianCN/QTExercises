#include "Minesweeper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minesweeper w;
    w.show();
    return a.exec();
}
