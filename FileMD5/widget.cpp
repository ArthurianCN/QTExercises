#include "widget.h"
#include <QMessageBox>

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
    ,m_pLayoutMain(new QGridLayout(this))
    ,m_lableResult(new QLabel(this))
{
    this->resize( QSize( 400, 100 ));
    m_lableHash1 = new QLabel( this);
    m_pLayoutMain->addWidget(m_lableHash1, 0, 0, 1, 5);
    m_LineEditCustomFilePath1 = new QLineEditCustom(this);
    m_pLayoutMain->addWidget(m_LineEditCustomFilePath1, 1, 0, 1, 5);

    m_lableHash2 = new QLabel(this);
    m_pLayoutMain->addWidget(m_lableHash2, 2, 0, 1, 5);
    m_LineEditCustomFilePath2 = new QLineEditCustom(this);
    m_pLayoutMain->addWidget(m_LineEditCustomFilePath2, 3, 0, 1, 5);

    m_pBtnVerify = new QPushButton("Verify", this);
    m_pLayoutMain->addWidget(m_lableResult, 4, 0, 1, 1);
    m_pLayoutMain->addWidget(m_pBtnVerify, 4, 2, 1, 1);

    connect(m_LineEditCustomFilePath1, &QLineEdit::textChanged, [=](){
        m_lableHash1->setText(GetFileMd5(m_LineEditCustomFilePath1->text().toUtf8().data()));
    }
    );
    connect(m_LineEditCustomFilePath2, &QLineEdit::textChanged, [=](){
        m_lableHash2->setText(GetFileMd5(m_LineEditCustomFilePath2->text().toUtf8().data()));
    }
    );
    connect(m_pBtnVerify, &QPushButton::clicked, this, &Widget::onBtnVerify);
}

Widget::~Widget()
{
}

void Widget::onBtnVerify()
{
    if(0 == m_lableHash1->text().compare(m_lableHash2->text()))
    {
        QPalette palette;
        palette.setColor(QPalette::Background, QColor(0, 255, 0));
        m_lableResult->setAutoFillBackground(true);  //一定要这句，否则不行
        m_lableResult->setGeometry(m_lableResult->x(), m_lableResult->y(), m_pBtnVerify->size().width(), m_pBtnVerify->size().height());
        m_lableResult->setPalette(palette);
    }
    else
    {
        QPalette palette;
        palette.setColor(QPalette::Background, QColor(255, 0, 0));
        m_lableResult->setAutoFillBackground(true);  //一定要这句，否则不行
        m_lableResult->setGeometry(m_lableResult->x(), m_lableResult->y(), m_pBtnVerify->size().width(), m_pBtnVerify->size().height());
        m_lableResult->setPalette(palette);
    }
}

