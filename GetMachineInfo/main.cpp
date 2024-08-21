#include <QCoreApplication>
#include "HostInfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CHostInfo objHostInfo;
    objHostInfo.GetCpuName();
    objHostInfo.GetHostName();
    objHostInfo.GetIpMac();

    objHostInfo.PrintInfo();


    return a.exec();
}
