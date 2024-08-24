#ifndef HASHTOOL_H
#define HASHTOOL_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>


class HashTool : public QMainWindow
{
    Q_OBJECT

public:
    HashTool(QWidget *parent = nullptr);
    ~HashTool();
private:
    // 输入：label、输入框
    QLabel *m_lbSrc = nullptr;
    QTextEdit * m_teSrc = nullptr;

    // 输出：label、输出框
    QLabel* m_lbDst = nullptr;
    QTextEdit* m_teDst = nullptr;

};
#endif // HASHTOOL_H
