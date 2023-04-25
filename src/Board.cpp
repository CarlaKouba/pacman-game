#include "Board.h"

Board::Board()
    :width(0), height(0)
{}
// -----------------------------------------------------------------------------------------
void Board::VectorsPushBack()
{
    m_moving.clear();
    m_static.clear();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            char c = arr[i][j];

            switch (enumObj(c)){
            case enumObj::GHOST_CH:{
                if (i % 2 != 0)
                    m_moving.push_back(std::make_unique<RandomGhost>(j * 20, i * 20));

                else
                    m_moving.push_back(std::make_unique<FollowPacGhost>(j * 20, i * 20));

                break;
            }
            case enumObj::WALL_CH: {
                m_static.push_back(std::make_unique<Wall>(j * 20, i * 20));
                break;
            }

            case enumObj::PACMAN_CH: {
                m_moving.push_back(std::make_unique<PacMan>(j * 20, i * 20));
                break;
            }
            case enumObj::DOOR_CH: {
                m_static.push_back(std::make_unique<Door>(j * 20, i * 20));
                break;
            }
            case enumObj::CAKE_CH: {
                m_static.push_back(std::make_unique<Cake>(j * 20, i * 20));
                break;
            }
            case enumObj::GIFT_CH: {
                m_static.push_back(std::make_unique<Gift>(j * 20, i * 20));
                break;
            }
            case enumObj::KEY_CH: {
                m_static.push_back(std::make_unique<Key>(j * 20, i * 20));
                break;
            }
            }
        }
    }
}
// -----------------------------------------------------------------------------------------
std::vector<std::unique_ptr<MovingObj>> &Board::get_m_moving() {
    return m_moving;
}
// -----------------------------------------------------------------------------------------
std::vector<std::unique_ptr<StaticObj>> &Board::get_m_static() {
    return m_static;
}
// -----------------------------------------------------------------------------------------
void Board::Levels(bool& first_level, bool& second_level, bool& third_level, bool& lose, bool& finishLevel, sf::RenderWindow& m_window, Vertex& vertex) {

    if (!first_level || (first_level && !second_level && !third_level && lose)) {
        if (lose) {
            lose = false;
            VectorsPushBack_afterLose();
        }
        else {
            Get_The_Level("1.txt");
            nextLevel(vertex, m_window, lose);
            first_level = true;
        }
    }
    else if (!second_level || (first_level && second_level && !third_level && lose)) {
        if (lose) {
            lose = false;
            VectorsPushBack_afterLose();
        }
        else {
            vertex.set_Score_Plus(50);
            Get_The_Level("2.txt");
            nextLevel(vertex, m_window, lose);
            second_level = true;
        }
    }
    else if (!third_level || (first_level && second_level && third_level && lose)) {
        if (lose) {
            lose = false;
            VectorsPushBack_afterLose();
        }
        else {
            vertex.set_Score_Plus(50);
            Get_The_Level("3.txt");
            nextLevel(vertex, m_window, lose);
            third_level = true;
        }
    }
}

void Board::nextLevel(Vertex& vertex, sf::RenderWindow& m_window, bool& lose) {
    m_window.close();
    m_window.create(sf::VideoMode(get_height() * 20, get_width() * 20 + 50), "PacMan Game");
    lose = true;
    VectorsPushBack();
}
// -----------------------------------------------------------------------------------------
std::vector<string>Board::get_arr()
{
    return arr;
}
// -----------------------------------------------------------------------------------------
void Board::set_arr( int x, int y)
{
    arr[y / 20][x / 20] = ' ';
}
// -----------------------------------------------------------------------------------------

void Board::set_arr_a(int x, int y)
{
    arr[y / 20][x / 20] = 'a';
}
// -----------------------------------------------------------------------------------------

void Board::Get_The_Level(const std::string& filename) {
    arr.clear();
    arr2.clear();
    std::ifstream infile(filename);
    std::string line;
    width = 0;
    while (getline(infile, line)) {
        width++;
        height = line.size() + 1;

        if (copy_to_arr_once)
        {
            arr.push_back(line);
            arr2.push_back(line);
        }
    }
}
// -----------------------------------------------------------------------------------------
bool Board::next_level(int width, int height, bool& finishLevel) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (arr[i][j] == '*')
                return false;
        }
    }
    finishLevel = true;
    return true;
}

int Board::get_height() {
    return height;
}

int Board::get_width() {
    return width;
}

bool Board::if_Finish(bool& third_level) {
    return third_level;
}

void Board::VectorsPushBack_afterLose()
{

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            char c = arr2[i][j];
            switch (enumObj(c))
            {
            case enumObj::GHOST_CH: {
                arr[i][j] = arr2[i][j];
                break;
            }
            case enumObj::PACMAN_CH: {
                arr[i][j] = arr2[i][j];
                break;
            }
            }
        }
    }

    VectorsPushBack();
}
// -----------------------------------------------------------------------------------------
void Board::returnObjects(Board& board, sf::Vector2f& pos, sf::Vector2f& pos2, char& c) {

    set_arr(pos2.x, pos2.y);
    arr[pos2.y / 20][pos2.x / 20] = c;
    arr[pos.y / 20][pos.x / 20] = '&';
}
// -----------------------------------------------------------------------------------------
