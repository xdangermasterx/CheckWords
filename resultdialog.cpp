#include "resultdialog.h"

#include <QLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QApplication>

ResultDialog::ResultDialog(QWidget *parent)
    :QDialog (parent)
{
    setWindowTitle("Результат");

    auto mainLay=new QGridLayout(this);

    auto closeBtn=new QPushButton("Закрыть",this);

    m_resultTable=new QTableWidget(0,3,this);

    m_countRight=0;
    m_countWrong=0;

     connect(closeBtn,&QPushButton::clicked,[this]{
         qApp->closeAllWindows();
    });


    mainLay->addWidget(m_resultTable);
    mainLay->addWidget(closeBtn);
}

void ResultDialog::setData(const QList<ResultInfo> &data)
{
    m_resultTable->clear();
    m_resultTable->setHorizontalHeaderLabels(QStringList()<<"Твое слово"<<"Правильный ответ"<<"Проверка ответа");

    m_resultTable->setEditTriggers(QTableWidget::NoEditTriggers);
    m_resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_resultTable->setRowCount(data.size());


    for(int index=0;index<data.size();index++){
            const auto ex=data.at(index);
            m_resultTable->setItem(index,0,new QTableWidgetItem(ex.word));
            m_resultTable->setItem(index,1,new QTableWidgetItem(ex.rightWord));

            auto tmpItem=new QTableWidgetItem();
            if(ex.isCorrect){
                tmpItem->setText("Верно");
                tmpItem->setBackground(QColor(127,255,0));
                m_countRight++;
            }else{
                tmpItem->setText("Не верно");
                tmpItem->setBackground(QColor(252,40,71));
                m_countWrong++;
            }

            m_resultTable->setItem(index,2,tmpItem);
        }


}
