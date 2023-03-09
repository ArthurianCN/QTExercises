#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>

#include <QProgressBar>
#include <QFormLayout>

class DownloadManager : public QWidget
{
    Q_OBJECT

public:
    DownloadManager(QWidget *parent = nullptr);
    ~DownloadManager();

private:
    QNetworkAccessManager* networkManager;
    QLineEdit* m_pLineEditUrl;
    QLineEdit* m_pLineEditLocalFilePath;
    QProgressBar* m_pProgressBar;

    QPushButton* m_pBtnStartDownload;
    QHBoxLayout* pHBoxLayoutBtn;

    QFormLayout* formLayout;

    QFile* fileDownload;
};
#endif // DOWNLOADMANAGER_H
