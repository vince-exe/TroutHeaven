#ifndef FISH_H
#define FISH_H

#include <QString>

class Fish {
private:
    double value;

public:
    Fish();

    Fish(double n);

    void setValue(double n);

    double getValue();

};

#endif // FISH_H
