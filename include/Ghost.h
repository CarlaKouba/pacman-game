#pragma once
#include "MovingObj.h"

class Ghost :public MovingObj{
public:
    Ghost(int x, int y);
    int getX() const;
    int getY() const;

private:
    int x_;
    int y_;
};