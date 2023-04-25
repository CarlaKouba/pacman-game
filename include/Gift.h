#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StaticObj.h"
#include "Board.h"
#include "SuperPacMan.h"
#include "Vertex.h"
using std::string;
using namespace std;

class Gift :public StaticObj {
public:
    Gift(int x, int y);
    int getX() const;
    int getY() const;
    void setTexture();
    sf::Sprite getSprite();
    void setPosition(int x, int y);
    void checkGift(Board& board, Vertex& vertex);
private:
    int x_;
    int y_;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    bool Is_SupPacGift;
    bool Is_TimePlusGift;
    bool Is_LivePlusGift;
    bool Is_StopGhostGift;
};