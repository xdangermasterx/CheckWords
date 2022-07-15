#ifndef WORDWIDGET_H
#define WORDWIDGET_H

#include <QWidget>
#include <QList>

#include "wordinfo.h"

class QHBoxLayout;
class CustomLabel;
class CustomLabel;

class WordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WordWidget(QWidget *parent = nullptr);

    void setData(const QList<WordInfo> &list);

    void updateWidget();

    QString word()const;
    WordInfo info()const;

signals:


private:

    void updateFontSize(CustomLabel *lbl, int fontSize);
    void updateWord();
    void updateLetters();

    virtual void resizeEvent(QResizeEvent *e) override;



    QHBoxLayout *wordLay;
    QHBoxLayout *letterLay;

    QList<CustomLabel*>m_wordLettersListLbl;
    QList<CustomLabel*>m_lettersListLbl;

    QList<WordInfo>m_words;

    int m_currentIndex;
    int m_fontSize;

    WordInfo m_currentInfo;

};

#endif // WORDWIDGET_H
