#include "wordwidget.h"

#include <QHBoxLayout>
#include <QResizeEvent>
#include <QRandomGenerator64>
#include "draglabel.h"
#include "droplabel.h"

WordWidget::WordWidget(QWidget *parent)
    : QWidget{parent}
{

    auto mainLay=new QVBoxLayout(this);
    wordLay=new QHBoxLayout(this);
    letterLay=new QHBoxLayout(this);

    mainLay->addLayout(wordLay);
    mainLay->addLayout(letterLay);

    m_currentIndex=0;
    m_fontSize=0;

}

void WordWidget::setData(const QList<WordInfo> &list)
{
    m_words=list;
    updateWidget();
}

void WordWidget::updateWord()
{
    for(auto &lbl:m_wordLettersListLbl){
        lbl->deleteLater();
    }
    m_wordLettersListLbl.clear();

    for(const auto &simb:m_currentInfo.word){

        auto tmpLbl=new DropLabel(simb,this);

        tmpLbl->setProtectedDrop(simb!="_");

        tmpLbl->setAlignment(Qt::AlignCenter);

        updateFontSize(tmpLbl,m_fontSize);

        m_wordLettersListLbl.append(tmpLbl);

        wordLay->addWidget(tmpLbl);
    }
}

void WordWidget::updateLetters()
{
    for(auto &lbl:m_lettersListLbl){
        lbl->deleteLater();
    }
    m_lettersListLbl.clear();

    for(const auto &letter:m_currentInfo.lettersList){
        auto tmpLbl=new DragLabel(letter,this);

        tmpLbl->setAlignment(Qt::AlignCenter);

        updateFontSize(tmpLbl,m_fontSize);

        m_lettersListLbl.append(tmpLbl);

        letterLay->addWidget(tmpLbl);
    }
}

void WordWidget::updateWidget()
{
//    m_currentIndex=QRandomGenerator64::global()->bounded(m_words.size());
    m_currentIndex++;

    m_currentIndex%=m_words.size();

    m_currentInfo=m_words.at(m_currentIndex);

    updateWord();
    updateLetters();
}

QString WordWidget::word() const
{
    QString tmpWord;

    for(auto lbl:m_wordLettersListLbl)
        tmpWord.append(lbl->text().at(0));

    return tmpWord;
}

WordInfo WordWidget::info() const
{
    return m_currentInfo;
}

void WordWidget::updateFontSize(CustomLabel *lbl,int fontSize)
{
    auto tmpFont=lbl->font();

    tmpFont.setPixelSize(fontSize);

    lbl->setFont(tmpFont);
}

void WordWidget::resizeEvent(QResizeEvent *e)
{
    m_fontSize=e->size().height()/10;

    for(auto lbl:m_wordLettersListLbl){

        updateFontSize(lbl,m_fontSize);

    }

    for(auto lbl:m_lettersListLbl){

        updateFontSize(lbl,m_fontSize);

    }

    QWidget::resizeEvent(e);
}
