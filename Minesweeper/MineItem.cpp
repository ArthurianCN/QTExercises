#include "MineItem.h"
#include <QDebug>

MineItem::MineItem(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
//    timerJudgeSingleOrDoubleClick = new QTimer(this);
//    connect(timerJudgeSingleOrDoubleClick, &QTimer::timeout, [=]()
//    {
//        timerJudgeSingleOrDoubleClick->stop();
    //    });
}

MineItem::MineItem(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
    , m_nBoomCnt(0)
{

}

void MineItem::setBoomNum(int nBoomNum)
{
    this->m_nBoomCnt = nBoomNum;
}

int MineItem::GetBoomNum()
{
    return this->m_nBoomCnt;
}


#include <QMouseEvent>
void MineItem::mousePressEvent(QMouseEvent *)
{
    qDebug() << __FUNCTION__;
    emit clicked();

}

//void MineItem::mouseReleaseEvent(QMouseEvent *)
//{
//    qDebug() << __FUNCTION__;
//}
//void MineItem::mouseDownEvent(QMouseEvent *)
//{
//    qDebug() << __FUNCTION__;
//}

//void MineItem::mouseUpEvent(QMouseEvent *)
//{
//    qDebug() << __FUNCTION__;
//}

//void MineItem::mouseDoubleClickEvent(QMouseEvent *)
//{
//    qDebug() << __FUNCTION__;
//}

//void MineItem::SingleClick()
//{
//    // 这里处理单击消息
//    ;
//}
