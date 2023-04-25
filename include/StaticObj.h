#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Object.h"

class StaticObj: public Object
{
public:
	StaticObj();
	//void DrawToWindow(std::vector<std::unique_ptr<StaticObj>>& m_moving, sf::RenderWindow& window);
	virtual void setTexture() {};

	virtual sf::Sprite getSprite() = 0;
	virtual void setPosition(int x, int y) =0;

	virtual int getX() const= 0;
	virtual int getY() const= 0;


private:

};