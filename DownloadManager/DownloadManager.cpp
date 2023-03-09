#include "DownloadManager.h"
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>

DownloadManager::DownloadManager(QWidget *parent)
    : QWidget(parent)
    ,m_pLineEditUrl(new QLineEdit(this))
    ,m_pLineEditLocalFilePath(new QLineEdit(this))
    ,m_pLineEditLocalFileName(new QLineEdit("index.html", this))
{
    this->resize(600, 100);

    m_pLineEditLocalFilePath->setPlaceholderText(("请输入完整的目标文件路径"));
    QString downloadDirectory = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    if (downloadDirectory.isEmpty() || !QFileInfo(downloadDirectory).isDir())
        downloadDirectory = QDir::currentPath();

    m_pLineEditLocalFilePath->setText(downloadDirectory);

    m_pProgressBar = new QProgressBar(this);

    m_pBtnStartDownload = new QPushButton("Start", this);
    pHBoxLayoutBtn = new QHBoxLayout();
    pHBoxLayoutBtn->addStretch(1);
    pHBoxLayoutBtn->addWidget(m_pBtnStartDownload);
    pHBoxLayoutBtn->addStretch(1);

    formLayout = new QFormLayout(this);
    formLayout->addRow("URL:", m_pLineEditUrl);
    formLayout->addRow("Download Directory:", m_pLineEditLocalFilePath);
    formLayout->addRow("Default File:", m_pLineEditLocalFileName);
    formLayout->addRow("Progress:", m_pProgressBar);
    formLayout->addRow(pHBoxLayoutBtn);

    connect(m_pBtnStartDownload, &QPushButton::clicked, [=]()
    {
        networkManager = new QNetworkAccessManager(this);
        QUrl url = m_pLineEditUrl->text();

        fileDownload = new QFile(m_pLineEditLocalFilePath->text());

        if(!fileDownload->open(QIODevice::WriteOnly))
        {
            return;
        }

        QNetworkReply* reply = networkManager->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::readyRead, [=](){
            fileDownload->write(reply->readAll());
        });
        connect(reply, &QNetworkReply::finished, [=](){
            fileDownload->flush();
            fileDownload->close();
            qDebug() << "finished" << fileDownload->size() << fileDownload->fileName();
        });

        connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesRead, qint64 bytesTotal){
            m_pProgressBar->setValue(bytesRead);
            m_pProgressBar->setMaximum(bytesTotal);
        });
    });
}

DownloadManager::~DownloadManager()
{
}


