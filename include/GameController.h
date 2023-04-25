#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "Sound.h"
#include "Vertex.h"

using std::string;
using namespace std;

class GameController {
public:
    GameController(int width, int height);
    void run();
    void displayTexts(sf::Text& text);
    void displayMovingObjects(Board& board);
    void displayStaticObjects(Board& board);
    void PacSupPacChecking(Board& board);
    void CheckIfOver(bool& over, sf::Event& event);
    void checkObjType(auto& obj, Board& board);
    void LosingLive(auto& obj, bool& over, sf::Event& event, Board& board);
    void get_MovingObjTexturePos(Board& board);

protected:
    sf::RenderWindow m_window;
    int height, width, m_lives, m_num_cakes;
    Vertex vertex;
    sf::Vector2f movement;
    bool m_second_level, m_third_level, restarted,is_super,
        first_level,second_level,third_level, finishLevel, lose,over;
    Board board;
    Sound sound;
    sf::Font font;
    sf::Clock stop_ghost;
    sf::Clock timer_for_move;
    sf::Event event;
    bool CharFound, first_Play;
    sf::Vector2f pos;
    sf::Vector2f pos2;
    char c;
};