#pragma once
#include "Key.h"

Key::Key(int x, int y)
    : x_(x), y_(y) {}

int Key::getX() const {
    return x_;
}

int Key::getY() const {
    return y_;
}
void Key::setTexture() {

    if (!m_texture.loadFromFile("Key.png")) {
        std::cerr << "Failed to load key texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}


sf::Sprite Key::getSprite() {

    return m_sprite;
}

void Key::setPosition(int x, int y)
{
   
    m_sprite.setPosition(x, y);
}
