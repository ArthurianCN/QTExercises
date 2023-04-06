#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>



//定义常量
#define BLOCK_LENGTH 21
#define BLOCK_HEIGH 21
#define ELENUM_LENGHT (BLOCK_LENGTH - 1)
#define EXPRESSION_LENGHT (BLOCK_LENGTH + 3)
#define EXPRESSION_HEIGH (BLOCK_HEIGH + 3)
#define TTILE_BEGIN 0
#define TITILE_HEIGH  (TTILE_BEGIN+40)
#define MAP_ITEM_WIDTH 1000
#define MAP_ITEM_HEIGHT 1000

class MineMap : public QWidget
{
    Q_OBJECT
    
public:
    explicit MineMap(int nRow, int nCol, int nMineNum, QWidget *parent = 0);

    ~MineMap();
    //绘制时间红旗数与标题
    void painttitle(QPainter *painter);
    void paintboom(QPainter * painter);
    void showblock(int x,int y);
    bool iswin();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:
    void on_secondadd();

private:
    int **m_pMapNum;
    QTimer * runtime;
    int m_nRow = 0;
    int m_nCol = 0;
    int m_nMineNum = 0;

    int m_nTimeNum = 0;
    int m_nRedFlagNum;


    int paint_flag = 0;
    bool showimage = true;

    int click_x = 0, click_y = 0;
    bool end = false;
public:
    int getcol() const{
        return this->m_nCol;
    }

    int getrow() const{
        return this->m_nRow;
    }

    int getboomNum()const {
        return this->m_nMineNum;
    }
    int gettimeNum() const
    {
        return this->m_nTimeNum;
    }
    int getredFlagNum() const
    {
        return this->m_nRedFlagNum;
    }
    void minusredFlagNum()
    {
        --this->m_nRedFlagNum;
    }
    void addtimeNum()
    {
        ++this->m_nTimeNum;
    }
    void addredFlagNum()
    {
        ++this->m_nRedFlagNum;
    }
};

#endif // MAINWINDOW_H
