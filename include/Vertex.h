#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include <array>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class Vertex {
public:
	Vertex();
	void set_Lives_Minus();
	int get_Lives();
	void set_Lives_Plus();
	void printLives(int height, int width);
	void printScore(int height, int width);
	void TimerRestart();
	void set_Time(int height, int width);
	void set_DeltaTime();
	sf::Time& set_elapsedTime();
	sf::Text& get_TextGameOver();
	void font_falilure();
	bool TimeIsOver(sf::RenderWindow& m_window, int height, int width);
	void TimePrinting(sf::RenderWindow& m_window);
	void Time_Plus();
	void Lives_zero(sf::RenderWindow& m_window, int height, int width);
	sf::Clock get_super_pac_timer() { return super_pac_timer; }
	void set_super_pac_timer() { super_pac_timer.restart(); }
	void win(sf::RenderWindow& m_window, int height, int width);
	sf::Text& get_win_text();
	void set_Score_Plus(int i);
	sf::Text& get_Score();

private:
	sf::Clock timer, super_pac_timer;
	sf::Time super_pac_duration;
	sf::Font font;
	std::stringstream lives_left, score, string_for_game_over, timer_string, win_string;
	sf::Time  duration, remainingTime, elapsedTime;
	sf::Text timerText, text_game_over;
	sf::Text text_for_lives, win_text, text_for_score;
	sf::RenderWindow m_window;
	int m_lives, m_score;
};