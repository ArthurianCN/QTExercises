#include "systemhunter.h"

// 刷新按钮
#include <QPushButton>

// 提示文字
#include <QLabel>

// 显示框
#include <QTextEdit>


#include <QGridLayout>

#include <QHostAddress>
#include <QHostInfo>
#include <QDateTime>
//qt获取所有的网卡信息（IP、MAC）
//qt获取主机名
//网络连接名、MAC地址、子网掩码、广播地址
SystemHunter::SystemHunter(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *m_pLayout = new QGridLayout(this);
//    QLabel *m_pMachineName = nullptr;
//    QLabel *m_pMacAddr = nullptr;
    QLabel *m_pHostName = nullptr;
    QLabel *m_pDateTime = nullptr;

//    m_pMachineName = new QLabel("IP");
//    m_pLayout->addWidget(m_pMachineName, 0, 0, 1, 1);

//    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//    m_pMachineName->setText(ipAddress);

//    m_pMacAddr = new QLabel("MAC");
//    m_pLayout->addWidget(m_pMacAddr);
    m_pHostName = new QLabel();
    QString qstrHostName  = "host: " + QHostInfo::localHostName();
    m_pHostName->setText(qstrHostName);
    m_pLayout->addWidget(m_pHostName);
    m_pDateTime = new QLabel();
    QString qstrDateTime = "time: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_pDateTime->setText(qstrDateTime);
    m_pLayout->addWidget(m_pDateTime);

}

SystemHunter::~SystemHunter()
{
}

