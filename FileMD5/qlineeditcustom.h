#ifndef QLINEEDITCUSTOM_H
#define QLINEEDITCUSTOM_H

#include <QWidget>
#include <QLineEdit>
#include <QDropEvent>
#include <QMimeData>
#include <QDragEnterEvent>

class QLineEditCustom : public QLineEdit
{
    Q_OBJECT


public:
    QLineEditCustom(QWidget* parent = nullptr);
    QLineEditCustom(const QString &contents, QWidget *parent = nullptr);
    ~QLineEditCustom();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // QLINEEDITCUSTOM_H
