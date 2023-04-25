#include "RandomGhost.h"
#include <chrono>

const int delay = 5;
// -----------------------------------------------------------------------------------------
RandomGhost::RandomGhost(int x, int y)
    :Ghost(x, y), stopGhost(false) {}


bool RandomGhost::IsSupPac(Board& board) {

    if (board.get_Is_StopGhostGift())
        return false;

    return true;
}

bool RandomGhost::IsStopGhost(Board& board) {
    if (board.get_Is_StopGhostGift())
        return false;

    return true;
}
void RandomGhost::move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)
{

    sf::Vector2f pos = m_sprite.getPosition();
    board.set_arr(pos.x, pos.y);
    int randomNum = rand() % 4 + 1;

    switch (randomNum) {
    case 1:
        moving(sf::Vector2f(0, 20), sf::Vector2f(0, -20), board, vertex, CharFound, pos2, pos, c);
        break;

    case 2:
        moving(sf::Vector2f(0, -20), sf::Vector2f(0, 20), board, vertex, CharFound, pos2, pos, c);
        break;

    case 3:
        moving(sf::Vector2f(20, 0), sf::Vector2f(-20, 0), board, vertex, CharFound, pos2, pos, c);
        break;

    case 4:
        moving(sf::Vector2f(-20, 0), sf::Vector2f(20, 0), board, vertex, CharFound, pos2, pos, c);
        break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}
// -----------------------------------------------------------------------------------------
void RandomGhost::setTexture() {

    if (!m_texture.loadFromFile("PurpleGhost.png")) {
        std::cerr << "Failed to load door texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);
}
// -----------------------------------------------------------------------------------------
sf::Sprite& RandomGhost::getSprite() {

    return m_sprite;
}
// -----------------------------------------------------------------------------------------
void RandomGhost::setPosition(int x, int y)
{
    m_sprite.setPosition(x, y);
}
// -----------------------------------------------------------------------------------------
bool RandomGhost::checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)
{
    sf::Vector2f pos = m_sprite.getPosition();

    if (board.get_arr()[pos.y / 20][pos.x / 20] == '#' ||
        board.get_arr()[pos.y / 20][pos.x / 20] == 'D') {
        return false;
    }

    else {
        if (board.get_arr()[pos.y / 20][pos.x / 20] == '*')
        {
            c = '*';
            KeepChar(board, pos2, pos, CharFound);
            return true;
        }

        else if (board.get_arr()[pos.y / 20][pos.x / 20] == '$')
        {
            c = '$';
            KeepChar(board, pos2, pos, CharFound);
            return true;
        }

        else if (board.get_arr()[pos.y / 20][pos.x / 20] == '%')
        {
            c = '%';
            KeepChar(board, pos2, pos, CharFound);
            return true;
        }


    }
    return true;
}
// -----------------------------------------------------------------------------------------

bool RandomGhost::pacManGhost(Board& board) {
    sf::Vector2f pos = m_sprite.getPosition();

    if (board.get_arr()[pos.y / 20][pos.x / 20] == 'a' && !board.get_Is_SupPacGift())
    {
        return true;
    }
    return false;
}

void RandomGhost::moving(sf::Vector2f speed, sf::Vector2f ops_speed, Board& board,
    Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, sf::Vector2f& pos, char& c) {

    m_sprite.move(speed);
    pos = m_sprite.getPosition();
    board.get_arr()[pos.x / 20, pos.y / 20] = '&';

    if (!checkMove(board, vertex, CharFound, pos2, c)) {

        board.get_arr()[pos.x / 20, pos.y / 20] = ' ';
        m_sprite.move(ops_speed);
        pos = m_sprite.getPosition();
        board.get_arr()[pos.x / 20, pos.y / 20] = '&';
    }

    if (CharFound)
    {
        m_sprite.move(speed);
        pos = m_sprite.getPosition();
        board.returnObjects(board, pos, pos2, c);
        CharFound = false;
    }
}

void RandomGhost::KeepChar(Board& board, sf::Vector2f& pos2, sf::Vector2f& pos, bool& CharFound) {
    pos2 = pos;
    board.get_arr()[pos.y / 20][pos.x / 20] = '&';
    CharFound = true;
}
