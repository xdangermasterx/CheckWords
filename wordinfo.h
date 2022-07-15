#ifndef WORDINFO_H
#define WORDINFO_H

#include <QString>
#include <QSet>
#include <QMap>

struct WordInfo{
    QString word;
    QSet<QChar> lettersList;
    QMap<int,QChar>rightLetters;
    int accentIndex{0};
};

#endif // WORDINFO_H
