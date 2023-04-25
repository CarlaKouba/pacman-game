#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "MovingObj.h"
#include "StaticObj.h"
#include "Ghost.h"
#include "Door.h"
#include "Gift.h"
#include "Cake.h"
#include "Wall.h"
#include "Key.h"
#include "PacMan.h"
#include "FollowPacGhost.h"
#include "RandomGhost.h"
#include "EnumObj.h"

class Board{
public:
    Board();
    void Levels(bool& first_level, bool& second_level, bool& third_level, bool& lose, bool& finishLevel, sf::RenderWindow& m_window, Vertex& vertex);
    void VectorsPushBack();
    std::vector<std::unique_ptr<MovingObj>> &get_m_moving();
    std::vector<std::unique_ptr<StaticObj>>& get_m_static();
    std::vector<string> get_arr();
    void set_arr(int x, int y);
    void set_arr_a(int x, int y);
    bool get_Is_SupPacGift() { return Is_SupPacGift; }
    void set_Is_SupPacGift() { Is_SupPacGift = true;}
    void set_Is_SupPacGift_f() { Is_SupPacGift = false; }
    bool get_Is_StopGhostGift() { return Is_StopGhostGift; }
    void set_Is_StopGhostGift() { Is_StopGhostGift = true; }
    void set_Is_StopGhostGift_f() { Is_StopGhostGift = false; }
    void Get_The_Level(const std::string& filename);
    bool next_level(int width, int height, bool& level);
    int get_height();
    int get_width();
    bool if_Finish(bool& third_level);
    void VectorsPushBack_afterLose();
    void returnObjects(Board& board, sf::Vector2f& pos, sf::Vector2f& pos2, char& c);
    void nextLevel(Vertex& vertex, sf::RenderWindow& m_window, bool& lose);


private:
    vector<std::unique_ptr<MovingObj>> m_moving;
    vector<std::unique_ptr<StaticObj>> m_static;
    std::vector<string> arr;
    std::vector<string> arr2;
    bool copy_to_arr_once;
    int width, height, firstWidth, firstHeight, level_width, level_height, width_plus;
    bool first_level, second_level, third_level, if_died;
    ifstream infile;
    string line;
    std::vector<std::vector<int>> levelData;
    bool Is_SupPacGift;
    bool Is_StopGhostGift;

};