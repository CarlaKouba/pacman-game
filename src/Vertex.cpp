#include"Vertex.h"

Vertex::Vertex()
    :m_lives(3), m_score(0) {}

int Vertex::get_Lives() {
    return m_lives;
}

void Vertex::set_Lives_Plus() {
    m_lives++;
}

void Vertex::set_Score_Plus(int i) {
    m_score = m_score + i;
}

void Vertex::set_Lives_Minus() {
    m_lives--;
}

void Vertex::printLives(int height, int width) {

    font_falilure();
    lives_left.str(std::string());
    lives_left << "Lives: " << m_lives;
    text_for_lives.setString(lives_left.str());
    text_for_lives.setFont(font);
    text_for_lives.setCharacterSize(24);
    text_for_lives.setPosition(height / 35, width);
    text_for_lives.setFillColor(sf::Color::Yellow);
}

void Vertex::printScore(int height, int width) {

    font_falilure();
    score.str(std::string());
    score << "Score: " << m_score;
    text_for_score.setString(score.str());
    text_for_score.setFont(font);
    text_for_score.setCharacterSize(24);
    text_for_score.setPosition(height / 2, width);
    text_for_score.setFillColor(sf::Color::Yellow);
}

void Vertex::TimerRestart() {
    timer.restart();
}

void Vertex::set_Time(int height, int width) {

    remainingTime = sf::seconds(100.f);
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setPosition(height - 100, width);
    timerText.setFillColor(sf::Color::Yellow);
}

sf::Time& Vertex::set_elapsedTime() {
    elapsedTime = timer.restart();
    remainingTime -= elapsedTime;
    return remainingTime;
}

sf::Text& Vertex::get_TextGameOver() {
    return text_game_over;
}

sf::Text& Vertex::get_Score() {
    return text_for_score;
}

sf::Text& Vertex::get_win_text() {
    return win_text;
}

bool Vertex::TimeIsOver(sf::RenderWindow& m_window, int height, int width)
{
    if (remainingTime.asSeconds() <= 0) {
        remainingTime = sf::seconds(0.f);
        string_for_game_over << "Game Over";
        text_game_over.setString(string_for_game_over.str());
        text_game_over.setFont(font);
        text_game_over.setCharacterSize(24);
        text_game_over.setPosition(height / 2, width / 2);
        text_game_over.setFillColor(sf::Color::Red);
        m_window.clear();
        return true;
    }
    return false;
}

void Vertex::Lives_zero(sf::RenderWindow& m_window, int height, int width)
{
    string_for_game_over << "Game Over";
    text_game_over.setString(string_for_game_over.str());
    text_game_over.setFont(font);
    text_game_over.setCharacterSize(24);
    text_game_over.setPosition(height / 2, width / 2);
    text_game_over.setFillColor(sf::Color::Red);
    m_window.clear();
}

void Vertex::TimePrinting(sf::RenderWindow& m_window) {
    std::stringstream ss1;
    ss1 << std::setfill('0') << std::setw(2) << (int)remainingTime.asSeconds() / 60 << ":" << std::setfill('0') << std::setw(2) << (int)remainingTime.asSeconds() % 60;
    timerText.setString(ss1.str());
    m_window.draw(timerText);
    m_window.draw(text_for_lives);
    m_window.draw(text_for_score);
}

void Vertex::Time_Plus() {
    remainingTime += sf::seconds(10.f);

}

void Vertex::win(sf::RenderWindow& m_window, int height, int width)
{
    win_string.str(std::string());
    win_string << "YOU WON!!!!!!!!!";
    win_text.setString(win_string.str());
    win_text.setFont(font);
    win_text.setCharacterSize(24);
    win_text.setPosition(height / 2, width / 2);
    win_text.setFillColor(sf::Color::Red);
    score.str(std::string());
    score << "Your Score is: " << m_score;
    text_for_score.setString(score.str());
    text_for_score.setFont(font);
    text_for_score.setCharacterSize(24);
    text_for_score.setPosition(height / 2, width);
    text_for_score.setFillColor(sf::Color::Yellow);
    m_window.clear();

}

void Vertex::font_falilure() {
    if (!font.loadFromFile("C:\\Windows\\Fonts\\RAVIE.ttf"))
    {
        std::cerr << "failure";
    }
}