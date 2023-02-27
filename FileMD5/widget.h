#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCryptographicHash>
#include <QLabel>
#include "qlineeditcustom.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QVBoxLayout *m_pLayoutMain;
    QLabel* m_lableHash1;
    QLineEditCustom* m_LineEditCustomFilePath1;
    QLabel* m_lableHash2;
    QLineEditCustom* m_LineEditCustomFilePath2;
    QPushButton* m_pBtnVerify;

    QHBoxLayout *pHLayoutBtn;

public slots:
    void onLineEditChanged();
    void onBtnVerify();

};
#endif // WIDGET_H
