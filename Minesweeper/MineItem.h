#ifndef MINEITEM_H
#define MINEITEM_H

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>

class MineItem : public QLabel
{
    Q_OBJECT
public:
    explicit MineItem(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit MineItem(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());


    void setBoomNum(int nBoomNum);
    int GetBoomNum();
protected:


    void mousePressEvent(QMouseEvent*);
//    void mouseReleaseEvent(QMouseEvent*);
//    void mouseDownEvent(QMouseEvent*);
//    void mouseUpEvent(QMouseEvent*);
//    void mouseDoubleClickEvent(QMouseEvent*);

//    void SingleClick();

signals:
    void clicked(void);

private:
    //QTimer *timerJudgeSingleOrDoubleClick;
    //bool m_bIsBoom;

    // 99表示本身是雷，0-8表示周围的雷数
    int m_nBoomCnt;
};

#endif // MINEITEM_H
