#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "MineMap.h"

#include <QMainWindow>


class Minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    Minesweeper(QMainWindow *parent = nullptr);
    ~Minesweeper();

    void MenuBarInit();

    void Restart();

private:
    int m_nLevel = 1;
    MineMap* widget = NULL;
};
#endif // MINESWEEPER_H
