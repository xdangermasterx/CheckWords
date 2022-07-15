#include "draglabel.h"

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

DragLabel::DragLabel(const QString &text, QWidget *parent)
    :CustomLabel (text,parent)
{

}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void DragLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
            return;

    if ((event->pos() - dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
        return;


   auto drag = new QDrag(this);
   auto mimeData = new QMimeData;

   mimeData->setText(text());

   drag->setMimeData(mimeData);

   drag->exec();
}
