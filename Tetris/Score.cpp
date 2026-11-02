#include "Score.h"

Score::Score() {
    current = 0;
    best = 0;
}

void Score::addLines(int lines) {
    if (lines == 1) {
        current = current + 100;
    }
    else if (lines == 2) {
        current = current + 300;
    }
    else if (lines == 3) {
        current = current + 500;
    }
    else if (lines >= 4) {
        current = current + 800;
    }
}

void Score::addCleanerPoints(int cells) {
    current = current + cells * 10;
}

bool Score::isVictory() const {
    return current >= 10000;
}

void Score::reset() {
    current = 0;
}

void Score::setBest(int value) {
    best = value;
}

int Score::getCurrent() const {
    return current;
}

int Score::getBest() const {
    return best;
}

void Score::setCurrent(int value) {
    current = value;
}