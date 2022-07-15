#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include "customlabel.h"

class DragLabel : public CustomLabel
{
    Q_OBJECT
public:
   explicit DragLabel(const QString &text, QWidget *parent =nullptr);

private:

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;


    QPoint dragStartPosition;
};

#endif // DRAGLABEL_H
