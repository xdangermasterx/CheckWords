#include "droplabel.h"

#include <QDragEnterEvent>
#include <QMimeData>

DropLabel::DropLabel(const QString &text, QWidget *parent)
    :CustomLabel (text,parent)
{
    setAcceptDrops(true);

    m_isProtectedDrop=true;
}

void DropLabel::setProtectedDrop(bool isProtectedDrop)
{
    m_isProtectedDrop=isProtectedDrop;
}

bool DropLabel::isProtectedDrop() const
{
    return m_isProtectedDrop;
}

void DropLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void DropLabel::dropEvent(QDropEvent *e)
{
    if(!m_isProtectedDrop)
        setText(e->mimeData()->text());
}
