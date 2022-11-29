#include "fish.h"

Fish::Fish() {}

Fish::Fish(double n) {
    this->value = n;
}

void Fish::setValue(double n) {
    this->value = n;
}

double Fish::getValue() {
    return this->value;
};
