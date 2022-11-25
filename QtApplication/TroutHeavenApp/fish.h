#ifndef FISH_H
#define FISH_H

#include <string>

class Fish {
private:
    std::string name;

    double value;

    double score;

public:
    Fish(const std::string& name, double value, double score);

    Fish();

    std::string getName();

    double getValue();

    double getScore();

};

#endif // FISH_H
