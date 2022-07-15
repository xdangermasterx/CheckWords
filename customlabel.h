#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(const QString &text, QWidget *parent =nullptr);
};

#endif // CUSTOMLABEL_H
