
#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <thread>
#include <string>
#include <memory>
#include "Cake.h"
#include "Door.h"
#include "Key.h"
#include "Gift.h"
#include "MovingObj.h"
#include "Sound.h"
#include "Vertex.h"

using std::string;
using namespace std;
class MovingObj;

class SuperPacMan : public MovingObj {
public:
    SuperPacMan(int x, int y);
    int getX() const;
    int getY() const;

    void move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c);
    bool checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c);
        bool pacManGhost(Board& board);
        void setTexture();
        sf::Sprite& getSprite();
        void setPosition(int x, int y);
        sf::Texture& getTexture();
        void change_map(Board& board, sf::Vector2f& pos, sf::Vector2f& pos2, Vertex& vertex);
        void new_and_old_position_up(sf::Vector2f& pos, sf::Vector2f& pos2);
        void new_and_old_position_down(sf::Vector2f& pos, sf::Vector2f& pos2);
        void new_and_old_position_left(sf::Vector2f& pos, sf::Vector2f& pos2);
        void new_and_old_position_right(sf::Vector2f& pos, sf::Vector2f& pos2);
        bool IsSupPac(Board& board);
        bool IsStopGhost(Board& board);
        void change_pac_sup(Board& board, sf::Vector2f& pos);
        void imag_according_direction(sf::Sprite& m_sprite, string imag, sf::Vector2f& pos, Board& board, Vertex& vertex);
        void find_pac_change_to_sup(Board& board, sf::Vector2f& pos);
        void check_which_imag(string imag, sf::Vector2f& pos, sf::Vector2f& pos2);
        void eat(Board& board, sf::Vector2f& pos);
        void delete_from_window_and_arr(Board& board, std::vector<std::unique_ptr<StaticObj>>::iterator it, int x, int y);

    private:
        int x_;
        int y_;
        sf::Vector2f movement;
        bool Is_TimePlusGift;
        bool Is_LivePlusGift;
        bool Is_StopGhostGift;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        Sound sound;
        Vertex vertex;
        sf::RenderWindow m_window;
};