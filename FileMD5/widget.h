#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QCryptographicHash>
#include <QLabel>
#include "qlineeditcustom.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QGridLayout *m_pLayoutMain;
    QLabel* m_lableHash1;
    QLineEditCustom* m_LineEditCustomFilePath1;
    QLabel* m_lableHash2;
    QLineEditCustom* m_LineEditCustomFilePath2;
    QLabel* m_lableResult;
    QPushButton* m_pBtnVerify;

public slots:
    void onBtnVerify();

};
#endif // WIDGET_H
