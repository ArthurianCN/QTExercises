#include "Minesweeper.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QGridLayout>
#include "MineMap.h"
#include <QApplication>
#include <QMessageBox>


Minesweeper::Minesweeper(QMainWindow *parent)
    : QMainWindow(parent)
    , m_nLevel(1)
{
    setWindowTitle("扫雷");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);  // 可以达到要求
    MenuBarInit();

    Restart();
}

Minesweeper::~Minesweeper()
{

}


void Minesweeper::MenuBarInit()
{
    QMenuBar* pMenuBar = menuBar();

    QMenu* menuGame = new QMenu("游戏");
    QAction* pActionStart = new QAction("开局");
    connect(pActionStart, &QAction::triggered, [=](){
        qDebug() << "点击了" << pActionStart->text() << "按钮";
    });

    menuGame->addAction(pActionStart);
    menuGame->addSeparator();
    QAction* pActionExit = new QAction("退出");
    connect(pActionExit, &QAction::triggered, [=](){
        qDebug() << "点击了" << pActionExit->text() << "按钮";
        QApplication::quit();
    });

    menuGame->addAction(pActionExit);

    QMenu* menuFunction = new QMenu("功能");
    QAction* pGamePause = new QAction("暂停游戏");
    connect(pGamePause, &QAction::triggered, [=](){
        qDebug() << "点击了" << pGamePause->text() << "按钮";
    });

    QAction* pGameRestart = new QAction("重新开始");
    connect(pGameRestart, &QAction::triggered, [=](){
        qDebug() << "点击了" << pGameRestart->text() << "按钮";
        Restart();
    });

    menuFunction->addAction(pGamePause);
    menuFunction->addAction(pGameRestart);
    QMenu* menuHelp = new QMenu("帮助");
    QAction* pActionAbout = new QAction("关于");
    connect(pActionAbout, &QAction::triggered, [=](){
        qDebug() << "点击了" << pActionAbout->text() << "按钮";
        QMessageBox::information(this, "关于扫雷", "这是扫雷的1.0版本", QMessageBox::Close);
    });
    menuHelp->addAction(pActionAbout);
    pMenuBar->addMenu(menuGame);

    pMenuBar->addMenu(menuFunction);
    pMenuBar->addMenu(menuHelp);
}

void Minesweeper::Restart()
{
    if(1 == m_nLevel)
    {
        widget = new MineMap(8, 8, 10);
    }

    this->setCentralWidget(widget);
    this->setFixedSize(widget->width(), widget->height() + this->menuBar()->height() - 5);
}


