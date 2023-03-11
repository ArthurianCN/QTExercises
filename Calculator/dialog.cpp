#include "dialog.h"
#include <QStringList>
#include <QGridLayout>

QStringList strListOpt = {"+", "-", "*", "/", "="};
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* pGridLayout = new QGridLayout(this);
    m_pLineEdit = new QLineEdit(this);
    pGridLayout->addWidget(m_pLineEdit, 0, 0, 1, 4);
    for(int i = 0; i < 11; ++i)
    {
        if(10 == i)
        {
            m_pArrBtnNum[10] = new QPushButton(".", this);
        }
        else if(9 == i)
        {
            m_pArrBtnNum[i] = new QPushButton("0", this);
        }
        else
        {
            m_pArrBtnNum[i] = new QPushButton(QString::number(i + 1), this);
        }

        connect(m_pArrBtnNum[i], &QPushButton::clicked, this, &Dialog::onPushbuttonNumClicked);

        pGridLayout->addWidget(m_pArrBtnNum[i], i / 3 + 1, i % 3, 1, 1);
    }

    calcflag = 0;
    ans = 0;

    for(int i = 0; i < 5; ++i)
    {
        m_pArrBtnOpt[i] = new QPushButton(strListOpt[i], this);
        connect(m_pArrBtnOpt[i], &QPushButton::clicked, this, &Dialog::onPushbuttonOperatorClicked);
        if(4 == i)
        {
            pGridLayout->addWidget(m_pArrBtnOpt[i], 4, 2, 1, 1);
        }
        else
        {
            pGridLayout->addWidget(m_pArrBtnOpt[i], 1 + i, 3, 1, 1);
        }
    }
}

Dialog::~Dialog()
{

}


void Dialog::onPushbuttonNumClicked()
{
    //通过信号发送者获取按钮对象
    QPushButton *button = (QPushButton*)sender();
    QString str = button->text();

    if(0 == calcflag)
    {
        if(0 != ans)
        {
            m_qstrNum1.clear();
            m_qstrNum2.clear();
        }
        ans = 0;
        m_qstrNum1 += str;
        m_pLineEdit->setText(m_qstrNum1);
    }
    else
    {
        m_qstrNum2 += str;
        m_pLineEdit->setText(m_qstrNum2);
    }
}

void Dialog::onPushbuttonOperatorClicked()
{
    QPushButton *button = (QPushButton*)sender();
    QString str = button->text();

    ans = 0.0;
    if(0 == str.compare("+"))
    {
        calcflag = 1;
        m_qstrNum2 = "";
    }
    else if(0 == str.compare("-"))
    {
        calcflag = 2;
        m_qstrNum2 = "";
    }
    else if(0 == str.compare("*"))
    {
        calcflag = 3;
        m_qstrNum2 = "";
    }
    else if(0 == str.compare("/"))
    {
        calcflag = 4;
        m_qstrNum2 = "";
    }
    else if(0 == str.compare("="))
    {
        switch (calcflag)
        {
        case 1:
            ans = m_qstrNum1.toDouble() + m_qstrNum2.toDouble();
            break;
        case 2:
            ans = m_qstrNum1.toDouble() - m_qstrNum2.toDouble();
            break;
        case 3:
            ans = m_qstrNum1.toDouble() * m_qstrNum2.toDouble();
            break;
        case 4:
            ans = m_qstrNum1.toDouble() / m_qstrNum2.toDouble();
            break;
        default:
            break;
        }

        m_pLineEdit->setText(QString::number(ans));
        calcflag = 0;
        m_qstrNum1 = QString::number(ans);
    }
    qDebug("[%s %d %s] num1: %s, num2: %s",
           __FILE__, __LINE__, __FUNCTION__,
           m_qstrNum1.toStdString().c_str(), m_qstrNum2.toStdString().c_str());
}
