#include "widget.h"
#include "ui_widget.h"

const QString GetFileMd5(const QString &path)
{
    QFile sourceFile(path);
    qint64 fileSize = sourceFile.size();
    const qint64 bufferSize = 10240;

    if (sourceFile.open(QIODevice::ReadOnly)) {
        char buffer[bufferSize];
        int bytesRead;
        int readSize = qMin(fileSize, bufferSize);

        QCryptographicHash hash(QCryptographicHash::Md5);

        while (readSize > 0 && (bytesRead = sourceFile.read(buffer, readSize)) > 0) {
            fileSize -= bytesRead;
            hash.addData(buffer, bytesRead);
            readSize = qMin(fileSize, bufferSize);
        }

        sourceFile.close();
        return QString(hash.result().toHex());
    }

    return QString();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
//    , ui(new Ui::Widget)
{
    this->resize( QSize( 400, 100 ));
    m_pLayoutMain = new QVBoxLayout(this);
    m_lableHash1 = new QLabel("md51", this);
    m_pLayoutMain->addWidget(m_lableHash1);
    m_LineEditCustomFilePath1 = new QLineEditCustom(this);
    m_pLayoutMain->addWidget(m_LineEditCustomFilePath1);

    m_lableHash2 = new QLabel("md52", this);
    m_pLayoutMain->addWidget(m_lableHash2);
    m_LineEditCustomFilePath2 = new QLineEditCustom(this);
    m_pLayoutMain->addWidget(m_LineEditCustomFilePath2);

    m_pBtnVerify = new QPushButton("Verify", this);
    pHLayoutBtn = new QHBoxLayout(this);
    pHLayoutBtn->addStretch();
    pHLayoutBtn->addWidget(m_pBtnVerify);
    pHLayoutBtn->addStretch();
    m_pLayoutMain->addLayout(pHLayoutBtn);

    setLayout(m_pLayoutMain);
    connect(m_LineEditCustomFilePath1, &QLineEdit::textChanged, this, &Widget::onBtnVerify);
    connect(m_LineEditCustomFilePath2, &QLineEdit::textChanged, this, &Widget::onBtnVerify);
    //connect(m_pBtnVerify, &QPushButton::clicked, this, &Widget::onBtnVerify);
}

Widget::~Widget()
{
    //    delete ui;
}

void Widget::onBtnVerify()
{
    QLineEditCustom* lineEditFile = qobject_cast<QLineEditCustom*>(sender());
    if(lineEditFile == m_LineEditCustomFilePath1)
    {
         m_lableHash1->setText(GetFileMd5(m_LineEditCustomFilePath1->text().toUtf8().data()));
    }
    else
    {
        m_lableHash2->setText(GetFileMd5(m_LineEditCustomFilePath2->text().toUtf8().data()));
    }
}

