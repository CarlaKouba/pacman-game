#include "GameController.h"

using std::string;
using namespace std;

const int delay = 10;

GameController::GameController(int width,int heigh)
    :is_super(false), restarted(false),
    first_level(false), second_level(false), third_level(false), lose(false), finishLevel(false),over(false)
    , CharFound(false)
{  
    run();
}
//------------------------------------------------------------------------
void GameController::run()
{
    while (board.next_level(board.get_width(), board.get_height(), 
        finishLevel) && board.if_Finish(third_level))
    {
        vertex.win(m_window, board.get_height() * 20, board.get_width() * 20);
        m_window.draw(vertex.get_Score());
        displayTexts(vertex.get_win_text());
    }

    board.set_Is_SupPacGift_f();
    board.set_Is_StopGhostGift_f();
    board.Levels(first_level, second_level, third_level, lose, finishLevel, m_window, vertex);
    vertex.printLives(board.get_height() * 20, board.get_width() * 20);
    vertex.printScore(board.get_height() * 20, board.get_width() * 20);
    if (first_Play) {
        vertex.set_Time(board.get_height() * 20, board.get_width() * 20);
        first_Play = false;
    }

    stop_ghost.restart();
    vertex.set_super_pac_timer();
    get_MovingObjTexturePos(board);


    while (m_window.isOpen()) {
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        while (true)
        {
            for (auto& obj : board.get_m_moving())
            {
                checkObjType(obj,board);
                LosingLive(obj, over, event,board);
                vertex.printScore(board.get_height() * 20, board.get_width() * 20);
                displayMovingObjects(board);
                displayStaticObjects(board);
                vertex.set_elapsedTime();
                CheckIfOver(over, event);
            }
        }
    }
}
//------------------------------------------------------------------------
void GameController::displayTexts(sf::Text& text) {
    sf::Event event;

    m_window.draw(text);
    m_window.display();
    m_window.clear();
    m_window.pollEvent(event);

    if (event.type == 0)
        m_window.close();
}
//------------------------------------------------------------------------
void GameController::displayMovingObjects(Board&board){
    bool jj = false;
    int x, y;
    for (auto& obj : board.get_m_moving())
    {
        sf::Vector2f pos = obj->getSprite().getPosition();
        if (!jj)
        {
            if (dynamic_cast<PacMan*>(obj.get()))
            {
                if (obj->IsSupPac(board))
                {
                    jj = true;
                    obj->change_pac_sup(board, pos);
                    m_window.draw(obj->getSprite());
                    vertex.set_super_pac_timer();

                }
            }

            else if (dynamic_cast<SuperPacMan*>(obj.get()))
            {

                if (vertex.get_super_pac_timer().getElapsedTime().asSeconds() > 10)
                {
                    jj = true;
                    obj->change_pac_sup(board, pos);
                    board.set_Is_SupPacGift_f();
                }
            }
        }
        m_window.draw(obj->getSprite());

    }
}
//------------------------------------------------------------------------
void GameController::displayStaticObjects(Board& board){
    for (auto& obj : board.get_m_static())
    {
        obj->setTexture();
        obj->setPosition(obj->getX(), obj->getY());
        m_window.draw(obj->getSprite());
    }
}
//------------------------------------------------------------------------
void GameController::CheckIfOver(bool &over, sf::Event& event)
{
    if (!over && vertex.TimeIsOver(m_window, board.get_height() * 20, board.get_width() * 20))
        over = true;

    while (over)
        displayTexts(vertex.get_TextGameOver());

    if (over || !vertex.TimeIsOver(m_window, board.get_height() * 20, board.get_width() * 20))
        vertex.TimePrinting(m_window);

    m_window.display();
    m_window.clear();
    m_window.pollEvent(event);

    if (event.type == 0)
    {
        m_window.close();
        exit(EXIT_SUCCESS);
    }
}
//------------------------------------------------------------------------
void GameController::checkObjType(auto&obj, Board& board) {

    // to make the superpacman movement faster
    if (dynamic_cast<SuperPacMan*>(obj.get()))
    {
        obj->move(board, vertex, CharFound, pos2, c);
        if (board.next_level(board.get_width(), board.get_height(), finishLevel)) {
            run();
        }
    }

    else if (dynamic_cast<FollowPacGhost*>(obj.get()) || dynamic_cast<RandomGhost*>(obj.get()))
    {
        if (stop_ghost.getElapsedTime().asSeconds() > 10)
        {
            board.set_Is_StopGhostGift_f();
            obj->IsStopGhost(board);
            stop_ghost.restart();
        }
        if (obj->IsStopGhost(board))
        {
            obj->move( board, vertex,CharFound,pos2,c);
            if (board.next_level(board.get_width(), board.get_height(), finishLevel)) {
                run();
            }
        }
    }
    else
        obj->move(board, vertex, CharFound, pos2, c);
}
//------------------------------------------------------------------------
void GameController::LosingLive(auto& obj,bool& over, sf::Event& event, Board& board) {
    
    if (obj->pacManGhost(board))
    {
        sound.pacmanDeath().play();
        vertex.set_Lives_Minus();
        sf::Vector2f pos = obj->getSprite().getPosition();
        board.set_arr(pos.x, pos.y);

        while (vertex.get_Lives() == 0)
        {
            if (!over)
            {
                vertex.Lives_zero(m_window, board.get_height() * 20, board.get_width() * 20);
                displayTexts(vertex.get_TextGameOver());
                over = true;
            }
            m_window.pollEvent(event);

            if (event.type == 0)
            {
                m_window.close();
                exit(EXIT_SUCCESS);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        m_window.clear();
        lose = true;
        run();
    }
}
//------------------------------------------------------------------------
void GameController::get_MovingObjTexturePos(Board& board) {

    for (auto& obj : board.get_m_moving())
    {
        obj->setTexture();
        obj->setPosition(obj->getX(), obj->getY());
    }
}
// -----------------------------------------------------------------------------------------
