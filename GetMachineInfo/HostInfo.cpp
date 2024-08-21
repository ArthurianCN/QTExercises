#include "HostInfo.h"

#include <QHostInfo>
#include <QSettings>
#include <QNetworkInterface>

CHostInfo::CHostInfo()
{

}

void CHostInfo::GetHostName()
{
    m_qstrHostName = QHostInfo::localHostName();
}

void CHostInfo::GetCpuName()
{
    // 获取CPU注册表地址
    QSettings cpu("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", QSettings::NativeFormat);

    // 提取CPU信息
    m_qstrCpuName = cpu.value("ProcessorNameString").toString();
}



// 获取MAC地址
void CHostInfo::GetIpMac()
{
    // 获取所有网络接口列表
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    for(auto iter : nets)
    {
        if(!iter.flags().testFlag(QNetworkInterface::IsUp) ||
           !iter.flags().testFlag(QNetworkInterface::IsRunning) ||
           iter.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            continue;
        }

        //qDebug() << "接口名称：" << iter.name()<< " MAC 地址：" << iter.hardwareAddress();
        for(int j = 0; j < iter.addressEntries().size(); j++)
        {
            if(iter.addressEntries().at(j).ip().isLoopback() ||
                    iter.addressEntries().at(j).ip().protocol() != QAbstractSocket::IPv4Protocol)
            {
                continue;
            }

            m_mapIpMac[iter.hardwareAddress()] = iter.addressEntries().at(j).ip().toString();
        }
    }

    return;
}

void CHostInfo::PrintInfo()
{
    // Hostname
    qDebug() << "******************** 系统信息 ********************";
    qDebug() << "HostName：" << this->m_qstrHostName;

    // CPU
    qDebug() << "******************** CPU ********************";
    qDebug() << "CPU：" << this->m_qstrCpuName;

    qDebug() << "******************** 网卡信息 ********************";
    // IP-MAC
    for(auto iter : m_mapIpMac.toStdMap())
    {
        qDebug() << "ip:" << iter.second << " mac:" << iter.first;
    }
}
