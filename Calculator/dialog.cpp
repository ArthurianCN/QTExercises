#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    calcflag = 0;
    ans = 0;
    connect(ui->pushButton_plus, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonOperatorClicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonOperatorClicked()));
    connect(ui->pushButton_multi, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonOperatorClicked()));
    connect(ui->pushButton_divide, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonOperatorClicked()));
    connect(ui->pushButton_equal, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonOperatorClicked()));

    connect(ui->pushButton_zero, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_dot, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_one, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_two, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_three, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_four, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_five, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_six, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_seven, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_eight, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
    connect(ui->pushButton_nine, SIGNAL(clicked(bool)), this, SLOT(onPushbuttonNumClicked()));
}

Dialog::~Dialog()
{
    delete ui;
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
        ui->lineEdit->setText(m_qstrNum1);
    }
    else
    {
        m_qstrNum2 += str;
        ui->lineEdit->setText(m_qstrNum2);
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

        ui->lineEdit->setText(QString::number(ans));
        calcflag = 0;
        m_qstrNum1 = QString::number(ans);
    }
    qDebug("[%s %d %s] num1: %s, num2: %s",
           __FILE__, __LINE__, __FUNCTION__,
           m_qstrNum1.toStdString().c_str(), m_qstrNum2.toStdString().c_str());
}
