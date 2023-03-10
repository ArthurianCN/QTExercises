#ifndef TELNET_H
#define TELNET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class Telnet : public QWidget
{
    Q_OBJECT

public:
    Telnet(QWidget *parent = nullptr);
    ~Telnet();

private:
    QTcpSocket *client;
    QLineEdit *lineEditDstHost, *lineEditPort;
    QPushButton *btnConnect, *btnDisconnect, *btnSend;
    QTextEdit* textEditLog, *textEditInput;
};
#endif // TELNET_H
