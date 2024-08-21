#ifndef CHOSTINFO_H
#define CHOSTINFO_H

#include <QString>
#include <QMap>


class CHostInfo
{
public:
    CHostInfo();
    void GetHostName();
    void GetCpuName();
    void GetIpMac();
    void PrintInfo();

private:
    QString m_qstrHostName;
    QString m_qstrCpuName;
    QMap<QString, QString> m_mapIpMac;
};

#endif // CHOSTINFO_H
