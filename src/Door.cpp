#pragma once
#include "Door.h"

Door::Door(int x, int y)
    : x_(x), y_(y) {}

int Door::getX() const {
    return x_;
}

int Door::getY() const {
    return y_;
}

void Door::setTexture() {

    if (!m_texture.loadFromFile("Door.png")) {
        std::cerr << "Failed to load door texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}


sf::Sprite Door::getSprite() {

    return m_sprite;
}

void Door::setPosition(int x, int y)
{
    m_sprite.setPosition(x, y);
}