#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>

#include "resultinfo.h"

class QTableWidget;

class ResultDialog : public QDialog
{
    Q_OBJECT
public:
    ResultDialog(QWidget *parent);

    void setData(const QList<ResultInfo>&data);

private:

    QTableWidget *m_resultTable;

    int m_countRight;
    int m_countWrong;
};

#endif // RESULTDIALOG_H
