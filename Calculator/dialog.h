#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void input_data(QString str);

private slots:
    void onPushbuttonNumClicked();
    void onPushbuttonOperatorClicked();

private:
    Ui::Dialog *ui;

    QString m_qstrNum1;        //记录输入第一个数值
    QString m_qstrNum2;       //记录输入第一个数值
    int calcflag;               //1-add， 2-sub, 3-mul, 4-div
    double ans;
};
#endif // DIALOG_H
