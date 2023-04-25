#pragma once
#include "Ghost.h"

Ghost::Ghost(int x, int y)
    : x_(x), y_(y) {}

int Ghost::getX() const {
    return x_;
}

int Ghost::getY() const {
    return y_;
}