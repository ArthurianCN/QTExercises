#include "qlineeditcustom.h"

QLineEditCustom::QLineEditCustom(QWidget *parent) : QLineEdit(parent)
{

}

QLineEditCustom::QLineEditCustom(const QString &contents, QWidget *parent): QLineEdit(contents, parent)
{

}

QLineEditCustom::~QLineEditCustom()
{

}

void QLineEditCustom::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }

}

void QLineEditCustom::dragMoveEvent(QDragMoveEvent *event)
{


}

void QLineEditCustom::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();
        QString fileName = urls.at(0).toLocalFile();
        setText(fileName);
        setCursorPosition(0);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
