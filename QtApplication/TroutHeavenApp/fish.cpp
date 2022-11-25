#include "fish.h"

Fish::Fish(const QString name, double value, double score) {
    this->name = name;
    this->value = value;
    this->score = score;
}

Fish::Fish() {}

QString Fish::getName() {
    return this->name;
}

double Fish::getValue() {
    return this->value;
}

double Fish::getScore() {
    return this->score;
};
