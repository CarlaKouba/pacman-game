#pragma once
#include "Ghost.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

class FollowPacGhost : public Ghost {
public:

	FollowPacGhost(int x, int y);
	void move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c);
	bool checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c);
	void setTexture();
	sf::Sprite& getSprite();
	void setPosition(int x, int y);
	
	bool pacManGhost(Board& board);
	bool IsSupPac(Board& board);
	bool IsStopGhost(Board& board);
	void change_pac_sup(Board& board, sf::Vector2f& pos) {}
	void moving(sf::Vector2f speed, sf::Vector2f ops_speed, Board& board, 
		Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, sf::Vector2f& pos, char& c);

	void KeepChar(Board& board, sf::Vector2f& pos2, sf::Vector2f& pos, bool& CharFound);

private:
	bool stopGhost;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};