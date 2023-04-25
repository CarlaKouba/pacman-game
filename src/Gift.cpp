#pragma once
#include "Gift.h"

Gift::Gift(int x, int y)
    : x_(x), y_(y),Is_LivePlusGift(false),Is_StopGhostGift(false),Is_SupPacGift(false),Is_TimePlusGift(false)
{}

int Gift::getX() const {
    return x_;
}

int Gift::getY() const {
    return y_;
}

void Gift::setTexture() {

    if (!m_texture.loadFromFile("Gift.png")) {
        std::cerr << "Failed to load gift texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}


sf::Sprite Gift::getSprite() {

    return m_sprite;
}

void Gift::setPosition(int x, int y)
{
   
    m_sprite.setPosition(x, y);
}

void Gift::checkGift(Board& board,Vertex& vertex) {
    sf::Vector2f pos = m_sprite.getPosition();
    if (!Is_LivePlusGift) {
        vertex.set_Lives_Plus();
        Is_LivePlusGift = true;
    }
}