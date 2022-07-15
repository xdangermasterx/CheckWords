#ifndef DROPLABEL_H
#define DROPLABEL_H

#include "customlabel.h"

class DropLabel : public CustomLabel
{
    Q_OBJECT
public:

    explicit DropLabel(const QString &text, QWidget *parent =nullptr);

    void setProtectedDrop(bool isProtectedDrop);
    bool isProtectedDrop()const;

private:

   virtual void dragEnterEvent(QDragEnterEvent *event) override;
   virtual void dropEvent(QDropEvent *e) override;


    bool m_isProtectedDrop;
};

#endif // DROPLABEL_H
