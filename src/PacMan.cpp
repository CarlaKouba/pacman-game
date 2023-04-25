#pragma once
#include "PacMan.h"

PacMan::PacMan(int x, int y)
    : x_(x), y_(y), Is_LivePlusGift(false), Is_StopGhostGift(false), Is_TimePlusGift(false) {}
// -----------------------------------------------------------------------------------------
int PacMan::getX() const {
    return x_;
}
// -----------------------------------------------------------------------------------------
int PacMan::getY() const {
    return y_;
}
// -----------------------------------------------------------------------------------------

void PacMan::imag_according_direction(sf::Sprite& m_sprite, string imag, sf::Vector2f &pos, Board &board, Vertex & vertex)
{
    if (!m_texture.loadFromFile(imag)) {
        std::cerr << "Failed to load cake texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(pos.x, pos.y);
    pos = m_sprite.getPosition();
    sf::Vector2f pos2;
    board.set_arr(pos.x, pos.y);
    check_which_imag(imag, pos, pos2);
    change_map(board, pos, pos2, vertex);
}

void PacMan::check_which_imag(string imag, sf::Vector2f& pos, sf::Vector2f &pos2)
{
    if (imag == "PacmanUp.png")
    {
        new_and_old_position_up(pos, pos2);
    }

    else if (imag == "PacmanDown.png")
    {
        new_and_old_position_down(pos, pos2);
    }
    else if (imag == "Pacman.png")
    {
        new_and_old_position_right(pos, pos2);
    }

    else if (imag == "PacmanLeft.png")
    {
        new_and_old_position_left(pos, pos2);
    }
}
// -----------------------------------------------------------------------------------------
void PacMan::move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)
{ 
    sf::Vector2f pos = m_sprite.getPosition();
  
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
    {
        imag_according_direction(m_sprite, "PacmanUp.png", pos, board, vertex);
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
    {
        imag_according_direction(m_sprite, "Pacman.png", pos, board, vertex);

    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
    {
        imag_according_direction(m_sprite, "PacmanLeft.png", pos, board, vertex);
   
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    {
        imag_according_direction(m_sprite, "PacmanDown.png", pos, board, vertex);
    }
}
// -----------------------------------------------------------------------------------------
sf::Sprite& PacMan::getSprite() {
    return m_sprite;
}
// -----------------------------------------------------------------------------------------
void PacMan::delete_from_window_and_arr(Board &board, std::vector<std::unique_ptr<StaticObj>>::iterator it, int x, int y)
{
    board.get_m_static().erase(it, board.get_m_static().end());
    sound.pacmanWalking().stop();
    sound.pacmanCakeEating().play();
    board.set_arr(x, y);
}
// -----------------------------------------------------------------------------------------
void PacMan::eat(Board& board, sf::Vector2f &pos)
{
    for (const std::unique_ptr<StaticObj>& cake : board.get_m_static())
    {
        auto it = std::remove_if(board.get_m_static().begin(), board.get_m_static().end(),
            [&](const std::unique_ptr<StaticObj>& cake) {
                return (cake->getX() == pos.x && cake->getY() == pos.y);
            });

        delete_from_window_and_arr(board, it, pos.x, pos.y);
    }
}
// -----------------------------------------------------------------------------------------

void PacMan::eat_key_and_door(Board& board, sf::Vector2f &pos)
{
    eat(board, pos);

        for (const std::unique_ptr<StaticObj>& door : board.get_m_static())
        {
            int x, y;
            for (const std::unique_ptr<StaticObj>& door : board.get_m_static())
            {
                if (door->getX() == pos.x && door->getY() == pos.y - 20 ||
                    door->getX() == pos.x + 20 && door->getY() == pos.y ||
                    door->getX() == pos.x && door->getY() == pos.y + 20 ||
                    door->getX() == pos.x - 20 && door->getY() == pos.y)
                {
                    if (board.get_arr()[door->getY() / 20][door->getX() / 20] == 'D')
                    {
                        x = door->getX();
                        y = door->getY();

                        break;
                    }
                }
            }
            auto it2 = std::remove_if(board.get_m_static().begin(), board.get_m_static().end(),
                [&](const std::unique_ptr<StaticObj>& door) {
                    return (door->getX() == x && door->getY() == y);
                });

           delete_from_window_and_arr(board, it2, x, y);
           break;
        }
    
}
// ----------------------------------------------------------------------------------------
bool PacMan::checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)
{
    sf::Vector2f pos = m_sprite.getPosition();
    if (board.get_arr()[pos.y / 20][pos.x / 20] == '#' ||
        board.get_arr()[pos.y / 20][pos.x / 20] == 'D') {
        return false;
    }

    else if (board.get_arr()[pos.y / 20][pos.x / 20] == '*') {
        vertex.set_Score_Plus(2);
        eat(board, pos);
        return true;
    }

    else if (board.get_arr()[pos.y / 20][pos.x / 20] == '%') {
        vertex.set_Score_Plus(6);
        eat_key_and_door(board, pos);
        return true;
    }

    else if (board.get_arr()[pos.y / 20][pos.x / 20] == '$') {
        vertex.set_Score_Plus(4);
        eat(board, pos);
       
        if (!Is_LivePlusGift) {
            vertex.set_Lives_Plus();
            Is_LivePlusGift = true;
        }

     else if (!Is_TimePlusGift) {
         vertex.Time_Plus();
         vertex.TimePrinting(m_window);
         Is_TimePlusGift = true;
     }

       
        else if (!Is_StopGhostGift) {
            Is_StopGhostGift = true;
            board.set_Is_StopGhostGift();
            IsStopGhost(board);
        }

      
        else if (!board.get_Is_SupPacGift()) {
            board.set_Is_SupPacGift();
            IsSupPac(board);
            Is_LivePlusGift = false;
            Is_TimePlusGift = false;
        }
        return true;
    }

    else if (board.get_arr()[pos.y / 20][pos.x / 20] == ' ') {
        return true;
    }
}
// -----------------------------------------------------------------------------------------
bool PacMan::IsSupPac(Board& board)
{
    if(board.get_Is_SupPacGift())
    return true;
}
// -----------------------------------------------------------------------------------------
bool PacMan::IsStopGhost(Board& board)
{
    if(Is_StopGhostGift)
    return true;
}
// -----------------------------------------------------------------------------------------

void PacMan::change_pac_sup(Board &board, sf::Vector2f& pos)
{
    pos = m_sprite.getPosition();
    find_pac_change_to_sup( board, pos);

    for (auto& obj : board.get_m_moving()) {
        if (dynamic_cast<SuperPacMan*>(obj.get())) {
            if (!m_texture.loadFromFile("SuperPac.png")) {
                std::cerr << "Failed to load cake texture" << std::endl;
                exit(EXIT_FAILURE);
            }
          
            m_sprite.setTexture(m_texture);
            m_sprite.setPosition(pos.x, pos.y);
            board.get_arr()[pos.y / 20][pos.x / 20] = '@';
            break;
        }
    }
}
// -----------------------------------------------------------------------------------------
void PacMan::find_pac_change_to_sup( Board& board, sf::Vector2f &pos)
{
    board.get_m_moving().erase(std::remove_if(board.get_m_moving().begin(), board.get_m_moving().end(),
        [](const std::unique_ptr<MovingObj>& obj) {
            return dynamic_cast<PacMan*>(obj.get()) != nullptr;
        }), board.get_m_moving().end());

    board.get_m_moving().push_back(std::make_unique<SuperPacMan>(pos.y, pos.x));
}

// -----------------------------------------------------------------------------------------
void PacMan::setTexture() {

    if (!m_texture.loadFromFile("Pacman.png")) {
        std::cerr << "Failed to load cake texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_sprite.setTexture(m_texture);
}

sf::Texture& PacMan::getTexture() {
    return m_texture;
}
// -----------------------------------------------------------------------------------------
void PacMan::setPosition( int x, int y)
{
    m_sprite.setPosition(x, y);
}
// -----------------------------------------------------------------------------------------
bool PacMan::pacManGhost(Board & board) {
    sf::Vector2f pos = m_sprite.getPosition();

    if (board.get_arr()[pos.y / 20][pos.x / 20] == '&')
    {
        return true;
    }
    return false;
}
// -----------------------------------------------------------------------------------------
void PacMan::change_map(Board& board, sf::Vector2f& pos, sf::Vector2f& pos2, Vertex& vertex)
{
    sound.pacmanWalking().play();
    char c;
    bool CharFound;
    if (!checkMove(board, vertex, CharFound, pos2, c)) {
        m_sprite.move(pos2);
        pos2 = m_sprite.getPosition();
        board.set_arr_a(pos2.x, pos2.y);    }

    else
    {
        pos = m_sprite.getPosition();
        board.set_arr_a(pos.x, pos.y);
    }
}
// -----------------------------------------------------------------------------------------
void PacMan::new_and_old_position_up(sf::Vector2f& pos, sf::Vector2f& pos2)
{
    m_sprite.move(sf::Vector2f(0, -20));
    pos2 = sf::Vector2f(0,20);
}
// -----------------------------------------------------------------------------------------
void PacMan::new_and_old_position_down(sf::Vector2f& pos, sf::Vector2f& pos2)
{
     m_sprite.move(sf::Vector2f(0, 20));
    pos2 = sf::Vector2f(0, -20);

}
// -----------------------------------------------------------------------------------------
void PacMan::new_and_old_position_left(sf::Vector2f& pos, sf::Vector2f& pos2)
{
    m_sprite.move(sf::Vector2f ( - 20, 0));
    pos2 = sf::Vector2f(20, 0);
}
// -----------------------------------------------------------------------------------------
void PacMan::new_and_old_position_right(sf::Vector2f& pos, sf::Vector2f& pos2)
{
    m_sprite.move(sf::Vector2f(20, 0));
    pos2 = sf::Vector2f(-20, 0);
}
// -----------------------------------------------------------------------------------------