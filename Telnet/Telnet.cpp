#include "Telnet.h"

#include <QGridLayout>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <QFormLayout>

Telnet::Telnet(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    client = new QTcpSocket(this);
    lineEditDstHost = new QLineEdit("www.baidu.com",this);
    lineEditPort = new QLineEdit("80", this);
    btnConnect = new QPushButton("connect", this);
    btnSend = new QPushButton("send", this);
    btnDisconnect = new QPushButton("disconnect", this);

    textEditLog = new QTextEdit(this);
    textEditInput = new QTextEdit(this);
    btnSend->setEnabled(false);
    btnDisconnect->setEnabled(false);

    textEditLog->setReadOnly(true);

    textEditInput->setPlaceholderText("请输入要发送给到服务器的内容");

    QRect rectScr = QGuiApplication::primaryScreen()->availableGeometry();
    resize(rectScr.width() / 2, rectScr.height() / 2);

    QGridLayout* pGridLayout = new QGridLayout(this);
    QGridLayout* pGridLayoutChild = new QGridLayout();

    int nRow = 0, nCol = 0, nRowSpan = 2, nColSpan = 5;
    QFormLayout* formLayoutLoginInfo = new QFormLayout();
    formLayoutLoginInfo->addRow("目标主机：", lineEditDstHost);
    formLayoutLoginInfo->addRow("目标端口：", lineEditPort);
    pGridLayoutChild->addLayout(formLayoutLoginInfo, 0, 0, 2, 5);

    nCol += nColSpan;
    nRowSpan = 1, nColSpan = 1;
    pGridLayoutChild->addWidget(btnConnect, nRow, nCol, nRowSpan, nColSpan);
    pGridLayoutChild->addWidget(btnDisconnect, nRow + 1, nCol, nRowSpan, nColSpan);

    nCol += nColSpan;
    nRowSpan = 1, nColSpan = 1;

    pGridLayout->addLayout(pGridLayoutChild, 0, 0, 2, nCol + 1);
    pGridLayout->addWidget(textEditLog, 2, 0, 2, nCol + nColSpan);
    pGridLayout->addWidget(new QLabel("Send:"), 4, 0, 1, 1);
    pGridLayout->addWidget(textEditInput, 5, 0, 2, nCol + nColSpan);
    pGridLayout->addWidget(btnSend, 7, nCol + nColSpan - 1, 1, 1);


    connect(btnConnect, &QPushButton::clicked, [=]() {
        client->connectToHost(lineEditDstHost->text(), lineEditPort->text().toInt());
    });

    connect(client, &QTcpSocket::connected, [=]() {
        btnSend->setEnabled(true);
        btnDisconnect->setEnabled(true);
        btnConnect->setEnabled(false);
        textEditLog->append("连接已建立");
    });

    connect(client, &QTcpSocket::stateChanged, [=](QAbstractSocket::SocketState socketState){
        switch (socketState)
        {
        case QAbstractSocket::UnconnectedState:
        {
            this->setWindowTitle("未连接");
            break;
        }
        case QAbstractSocket::ConnectingState:
        {
            this->setWindowTitle("连接中...");
            break;
        }
        case QAbstractSocket::ConnectedState:
        {
            this->setWindowTitle("已连接");
            break;
        }
        case QAbstractSocket::ClosingState:
        {
            this->setWindowTitle("连接即将关闭");
            break;
        }
        default:
        {
            break;
        }
        }
    });

    connect(btnSend, &QPushButton::clicked, [=]() {
        QString data = textEditInput->toPlainText();
        if(0 < data.length())
        {
            client->write(data.toUtf8());
            textEditLog->append("send:" + data);
        }
    });

    connect(client, &QTcpSocket::readyRead,this, [=]() {
        textEditLog->append("recv:" + client->readAll());
    });

    /* 断开连接 */
    connect(btnDisconnect,&QPushButton::clicked, [=]() {
        client->disconnectFromHost();
    });

    connect(client, &QTcpSocket::disconnected, [=]() {
        textEditLog->append("连接已断开");
        btnSend->setEnabled(false);
        btnDisconnect->setEnabled(false);
        btnConnect->setEnabled(true);
    });

}

Telnet::~Telnet()
{

}
