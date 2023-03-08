#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QWidget>

class DownloadManager : public QWidget
{
    Q_OBJECT

public:
    DownloadManager(QWidget *parent = nullptr);
    ~DownloadManager();

    void readyRead();
private:

};
#endif // DOWNLOADMANAGER_H
