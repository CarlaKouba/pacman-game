#pragma once
#include "Cake.h"

Cake::Cake(int x, int y) 
    : x_(x), y_(y) {}

int Cake::getX() const {
    return x_; 
}

int Cake::getY() const {
    return y_; 
}

void Cake::setTexture() {
   
    if (!m_texture.loadFromFile("Cake.png")) {
        std::cerr << "Failed to load cake texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}

sf::Sprite Cake::getSprite() {

    return m_sprite;
}

void Cake::setPosition(int x, int y)
{
    
    m_sprite.setPosition(x, y);
}

