#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Object.h"

class Board;
class Vertex;

class MovingObj: public Object
{
public:
	MovingObj();
	virtual void setTexture() = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual void setPosition(int x, int y) =0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual bool checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos, char& c) = 0;
	virtual void move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c) = 0;
	virtual bool pacManGhost(Board& board) = 0;
	virtual bool IsSupPac(Board &board) = 0; 
	virtual bool IsStopGhost(Board& board) = 0;
	virtual void change_pac_sup(Board& board, sf::Vector2f& pos) = 0;

private:
	bool Is_SupPacGift;
};