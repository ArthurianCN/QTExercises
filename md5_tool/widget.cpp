#include "widget.h"
#include <QGridLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>
#include <QPushButton>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QDebug>


bool GetFileMD5(QString path, QString &fileMD5)
{
    /* 打开文件 */
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件打开错误";
        return false;
    }

    QCryptographicHash md5_hash(QCryptographicHash::Md5);
    md5_hash.reset();

    /* 文本读取 */
    while(!file.atEnd())
    {
        md5_hash.addData(file.readLine());
    }

   fileMD5 = QString(md5_hash.result().toHex());

   return true;
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,m_tabWidget(new QTabWidget(this))
{
    QWidget* m_widget1 = new QWidget(this);
    QGridLayout* pLayout1 = new QGridLayout(m_widget1);
    QTextEdit* pStringSrc = new QTextEdit(m_widget1);
    pStringSrc->setPlaceholderText("输入文字或将txt格式的文本文件拖拽到这里");

    pLayout1->addWidget(pStringSrc, 0, 0, 3, 6);
    QLineEdit* pStringMd5 = new QLineEdit(m_widget1);
    pLayout1->addWidget(pStringMd5, 3, 0, 1, 5);
    QCheckBox* pUpper1 = new QCheckBox("大写", m_widget1);
    pLayout1->addWidget(pUpper1, 3, 5, 1, 1);

    QWidget* m_widget2 = new QWidget(this);
    QGridLayout* pLayout2 = new QGridLayout(m_widget2);
    QTableWidget* pTable = new QTableWidget(m_widget2);
    // 没有这行，表头不显示
    pTable->setColumnCount(3);
    pTable->setHorizontalHeaderLabels(QStringList() << "文件名" << "MD5" << "对比结果");
    pLayout2->addWidget(pTable,0, 0, 3, 6);
    QPushButton* pBtnAdd = new QPushButton("添加", m_widget2);
    QPushButton* pBtnRemove = new QPushButton("移除", m_widget2);
    QPushButton* pBtnEmpty = new QPushButton("清空", m_widget2);
    QCheckBox* pUpper2 = new QCheckBox("大写", m_widget2);
    pLayout2->addWidget(pBtnAdd, 3, 0, 1, 1);
    pLayout2->addWidget(pBtnRemove, 3, 1, 1, 1);
    pLayout2->addWidget(pBtnEmpty, 3, 2, 1, 1);
    pLayout2->addWidget(pUpper2, 3, 5, 1, 1);

    m_tabWidget->addTab(m_widget1, "MD5生成器");
    m_tabWidget->addTab(m_widget2, "MD5对比");
    QGridLayout* pLayoutMain = new QGridLayout(this);
    pLayoutMain->addWidget(m_tabWidget);

    this->setFixedSize(500, 300);

    connect(pStringSrc, &QTextEdit::textChanged, [=](){
        if(0 == pStringSrc->toPlainText().size())
        {
            pStringMd5->clear();
        }
        else
        {
            QByteArray value;
            value = QCryptographicHash::hash(pStringSrc->toPlainText().toLocal8Bit(), QCryptographicHash::Md5);
            pStringMd5->setText(value.toHex().data());
        }
    });

    connect(pBtnAdd, &QPushButton::clicked, [=](){
        QFileDialog fileChooseDlg;
        fileChooseDlg.setWindowTitle("添加文件");
        fileChooseDlg.setDirectory("./");
        fileChooseDlg.setFileMode(QFileDialog::ExistingFiles);

        QStringList strFilePaths;
        QString strFileMD5;
        if(fileChooseDlg.exec())
        {
            strFilePaths = fileChooseDlg.selectedFiles();
        }

        foreach(QString strFileName, strFilePaths)
        {
            int rowIndex = pTable->rowCount();
            pTable->insertRow(rowIndex);
            pTable->setItem(rowIndex, 0, new QTableWidgetItem(strFileName));

            GetFileMD5(strFileName, strFileMD5);
            pTable->setItem(rowIndex, 1, new QTableWidgetItem(strFileMD5));
        }
    });
}

Widget::~Widget()
{
}

