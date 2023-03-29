#include "Minesweeper.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QGridLayout>
#include "MineMap.h"
#include "MineItem.h"
#include <QApplication>

Minesweeper::Minesweeper(QMainWindow *parent)
    : QMainWindow(parent)
    , m_nLevel(1)
{
    MenuBarInit();

    if(1 == m_nLevel)
    {
        widget = new MineMap(8, 8, 10);
    }

    this->setCentralWidget(widget);
}

Minesweeper::~Minesweeper()
{
    ;
}

void Minesweeper::MenuBarInit()
{
    QMenuBar* pMenuBar = menuBar();

    QMenu* menuGame = new QMenu("游戏(G)");
    QAction* pActionStart = new QAction("开局（N）");
    menuGame->addAction(pActionStart);
    menuGame->addSeparator();
    QAction* pActionExit = new QAction("退出（X）");
    connect(pActionExit, &QAction::triggered, [](){
        qDebug("点击了退出按钮");
        QApplication::quit();
    });

    menuGame->addAction(pActionExit);

    QMenu* menuFunction = new QMenu("功能（F）");
    QAction* pGamePause = new QAction("暂停游戏（P） F1");
    QAction* pGameRestart = new QAction("重新开始（R）");

    menuFunction->addAction(pGamePause);
    menuFunction->addAction(pGameRestart);
    QMenu* menuHelp = new QMenu("帮助（H）");
    QAction* pActionAbout = new QAction("关于（A）");
    menuHelp->addAction(pActionAbout);
    pMenuBar->addMenu(menuGame);

    pMenuBar->addMenu(menuFunction);
    pMenuBar->addMenu(menuHelp);
}

