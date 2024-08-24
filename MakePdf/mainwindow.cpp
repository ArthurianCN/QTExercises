#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPdfWriter>
#include <QDebug>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    generatePdf();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generatePdf()
{
    QString fileName = "output.pdf";
    QPdfWriter writer(fileName);

    // 设置纸张大小
    writer.setPageSize(QPageSize(QPageSize::A4));
    // 设置页边距
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&writer);
    painter.setFont(QFont("Arial", 12));

    int nX = 0, nY = 0;

    nX += 100;
    nY += 500;
    // 绘制文本
    painter.drawText(nX, nY, "Hello, PDF World!");

    nY += 20;
    // 绘制矩形
    painter.drawRect(nX, nY, 200, 100);
    // 完成绘制
    painter.end();
}

