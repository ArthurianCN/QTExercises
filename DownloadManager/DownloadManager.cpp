#include "DownloadManager.h"
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QDebug>

DownloadManager::DownloadManager(QWidget *parent)
    : QWidget(parent)
{
    this->resize(600, 100);
    QLabel* m_pLblURL = new QLabel("URL:", this);
    QLineEdit* m_pLineEditUrl = new QLineEdit(this);
    QHBoxLayout* pHBoxLayoutUrl = new QHBoxLayout();
    pHBoxLayoutUrl->addWidget(m_pLblURL);
    pHBoxLayoutUrl->addWidget(m_pLineEditUrl);


    QLabel* m_pLblLocalFilePath = new QLabel("Path:", this);
    QLineEdit* m_pLineEditLocalFilePath = new QLineEdit(this);
    QHBoxLayout* pHBoxLayoutLocalFilePath = new QHBoxLayout();
    pHBoxLayoutLocalFilePath->addWidget(m_pLblLocalFilePath);
    pHBoxLayoutLocalFilePath->addWidget(m_pLineEditLocalFilePath);

    QPushButton* m_pBtnStartDownload = new QPushButton("Start", this);
    QHBoxLayout* pHBoxLayoutBtn = new QHBoxLayout();
    pHBoxLayoutBtn->addStretch(1);
    pHBoxLayoutBtn->addWidget(m_pBtnStartDownload);
    pHBoxLayoutBtn->addStretch(1);

    QVBoxLayout* pVBoxLayout = new QVBoxLayout(this);
    pVBoxLayout->addLayout(pHBoxLayoutUrl);
    pVBoxLayout->addLayout(pHBoxLayoutLocalFilePath);
    pVBoxLayout->addLayout(pHBoxLayoutBtn);

    connect(m_pBtnStartDownload, &QPushButton::clicked, [=]()
    {
        QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
        QUrl url = m_pLineEditUrl->text();

        QFile* fileDownload = new QFile(m_pLineEditLocalFilePath->text());

        if(!fileDownload->open(QIODevice::WriteOnly))
        {
            return;
        }

        QNetworkReply* reply = networkManager->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::readyRead, [=](){
            fileDownload->write(reply->readAll());
            qDebug() << "write";
        });
        connect(reply, &QNetworkReply::finished, [=](){
            fileDownload->flush();
            fileDownload->close();
            qDebug() << "finished" << fileDownload->size() << fileDownload->fileName();
        });
    });
}

DownloadManager::~DownloadManager()
{
}

void DownloadManager::readyRead()
{

}

