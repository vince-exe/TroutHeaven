#include "fish.h"

Fish::Fish(const std::string &name, double value, double score) {
    this->name = name;
    this->value = value;
    this->score = score;
}

Fish::Fish() {}

std::string Fish::getName() {
    return this->name;
}

double Fish::getValue() {
    return this->value;
}

double Fish::getScore() {
    return this->score;
};
