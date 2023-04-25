#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StaticObj.h"
using std::string;
using namespace std;

class Cake: public StaticObj {
public:
    Cake(int x, int y);
    int getX() const;
    int getY() const;
    void setTexture();
    sf::Sprite getSprite();

    void setPosition(int x, int y);
private:
    int x_;
    int y_;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};