#include "widget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDrag>
#include <QMimeData>
#include <QKeyEvent>

#include "draglabel.h"
#include "droplabel.h"
#include "wordwidget.h"
#include "resultdialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setWindowState(Qt::WindowMaximized);

    auto mainLay=new QVBoxLayout(this);
    auto btnLay=new QHBoxLayout(this);

    m_loadFileBtn=new QPushButton(tr("Загрузить словарь"),this);
    m_nextBtn=new QPushButton(tr("Следующее слово"),this);
    m_closeBtn=new QPushButton(tr("Завершить"),this);

    m_wordWidget=new WordWidget(this);


    m_nextBtn->setEnabled(false);
    m_closeBtn->setEnabled(false);


    btnLay->addWidget(m_loadFileBtn);

    mainLay->addLayout(btnLay);
    mainLay->addWidget(m_wordWidget);
    mainLay->addWidget(m_nextBtn);
    mainLay->addWidget(m_closeBtn);

    connect(m_closeBtn,&QPushButton::clicked,[this]{
        ResultDialog d(this);

        d.setData(m_relustList);

        d.exec();
    });

    connect(m_nextBtn,&QPushButton::clicked,[this]{
        handleAnswer();
    });

    connect(m_loadFileBtn,&QPushButton::clicked,[this]{

        const auto fileName=QFileDialog::getOpenFileName(this,tr("Выбрать словарь"),qApp->applicationDirPath(),"*.json");

        if(fileName.isEmpty())
            return;

        QFile file(fileName);

        file.open(QFile::ReadOnly);

        auto content=file.readAll();

        QJsonDocument doc(QJsonDocument::fromJson(content));

        readJson(doc.object());

        m_wordWidget->setData(m_words);

        m_nextBtn->setEnabled(!m_words.isEmpty());
        m_closeBtn->setEnabled(!m_words.isEmpty());


    });

}

Widget::~Widget()
{

}

void Widget::handleAnswer()
{
    checkWord(m_wordWidget->word(),m_wordWidget->info());

    m_wordWidget->updateWidget();
}

void Widget::readJson(const QJsonObject &json)
{
    m_words.clear();
    if(json.contains("list")&&json["list"].isArray()){
        auto list=json["list"].toArray();
        for(int indexList=0;indexList<list.size();indexList++){
            WordInfo wi;
            auto infoObj=list[indexList].toObject();

            if(infoObj.contains("word")&&infoObj["word"].isString())
                wi.word=infoObj["word"].toString();

            if(infoObj.contains("accent")&&infoObj["accent"].isDouble())
                wi.accentIndex=infoObj["accent"].toInt();

            if(infoObj.contains("letters")&&infoObj["letters"].isArray()){
                auto lettersArr=infoObj["letters"].toArray();

                QSet<QChar> tmpLettersList;
                for(int indexLetter=0;indexLetter<lettersArr.size();indexLetter++){
                    tmpLettersList.insert(lettersArr[indexLetter].toString().at(0));
                }

                wi.lettersList=tmpLettersList;

            }

            if(infoObj.contains("right")&&infoObj["right"].isArray()){

                auto rightArr=infoObj["right"].toArray();

                QMap<int,QChar>m_tmpRightList;

                for(int indexRight=0;indexRight<rightArr.size();indexRight++){
                    auto rightObj=rightArr[indexRight].toObject();

                    int tmpIndex=0;
                    QChar tmpLetter=0;

                    if(rightObj.contains("letter")&&rightObj["letter"].isString()){

                        tmpLetter=rightObj["letter"].toString().at(0);

                    }

                    if(rightObj.contains("index")&&rightObj["index"].isDouble()){
                        tmpIndex=rightObj["index"].toInt();
                    }

                    m_tmpRightList.insert(tmpIndex,tmpLetter);
                }
                wi.rightLetters=m_tmpRightList;
            }
            m_words.append(wi);
        }
    }
}

void Widget::checkWord(const QString &word,const WordInfo &info)
{

    ResultInfo ri;

    auto rightWord=info.word;

    const auto spaceChar='_';

    while(rightWord.count(spaceChar)){

        const auto spacePos=rightWord.indexOf(spaceChar);

        rightWord.replace(spacePos,1,info.rightLetters.value(spacePos+1));


    }

    ri.word=word;
    ri.rightWord=rightWord;
    ri.isCorrect=!(word.compare(rightWord));

    m_relustList.append(ri);

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()!=Qt::Key_Enter && event->key()!=Qt::Key_Return)
        return;

    handleAnswer();

}

