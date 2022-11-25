#ifndef FISH_H
#define FISH_H

#include <QString>

class Fish {
private:
    QString name;

    double value;

    double score;

public:
    Fish(const QString name, double value, double score);

    Fish();

    QString getName();

    double getValue();

    double getScore();

};

#endif // FISH_H
