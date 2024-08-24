#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSoundEffect>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSoundEffect *soundEffect = new QSoundEffect();
    // 设置声音源文件的路径
    soundEffect->setSource(QUrl::fromLocalFile("://audio/sample-15s.wav"));
    // 音频循环的次数
    soundEffect->setLoopCount(1);
    // 音量
    soundEffect->setVolume(1);
    soundEffect->play();

    // 连接信号，当播放完毕时，自动销毁对象。
    connect(soundEffect, &QSoundEffect::playingChanged, [soundEffect] () {
        if (soundEffect->isPlaying()) {
            soundEffect->deleteLater();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

