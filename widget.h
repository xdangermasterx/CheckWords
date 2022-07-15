#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "wordinfo.h"
#include "resultinfo.h"

class WordWidget;
class QPushButton;
class CustomLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    virtual ~Widget() override;


private slots:

    void handleAnswer();

private :



    void readJson(const QJsonObject &json);

    void checkWord(const QString &word, const WordInfo &info);

    virtual void keyPressEvent(QKeyEvent *event) override;

    QPushButton *m_loadFileBtn;
    QPushButton *m_nextBtn;
    QPushButton *m_closeBtn;
    WordWidget *m_wordWidget;


    QList<WordInfo>m_words;
    QList<ResultInfo>m_relustList;

};
#endif // WIDGET_H
