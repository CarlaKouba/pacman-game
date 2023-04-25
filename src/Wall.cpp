#pragma once
#include "Wall.h"

Wall::Wall(int x, int y)
    : x_(x), y_(y) {}

int Wall::getX()const {
    return x_;
}

int Wall::getY() const{
    return y_;
}
void Wall::setTexture() {

    if (!m_texture.loadFromFile("Wall.png")) {
        std::cerr << "Failed to load wall texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}


sf::Sprite Wall::getSprite() {

    return m_sprite;
}

void Wall::setPosition(int x, int y)
{
   
    m_sprite.setPosition(x, y);
}
