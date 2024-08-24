#include "HashTool.h"

#include <QApplication>





/* 输入一个字符串，可以以各种算法输出对应的hash值
 *
*/





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HashTool w;
    w.show();
    return a.exec();
}
