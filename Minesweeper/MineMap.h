#ifndef MINEMAP_H
#define MINEMAP_H
#include "MineItem.h"

#include <QWidget>

class MineMap: public QWidget
{
    Q_OBJECT
public:
    MineMap(int nCol, int nRow, int nBoomNum, QWidget *parent = nullptr);
    ~MineMap();
    MineItem** m_pMapInfo;
    qint8 m_nCol;
    qint8 m_nRow;
    qint8 m_nBoomNum;
    int timeNum,redFlagNum;
};

#endif // MINEMAP_H
