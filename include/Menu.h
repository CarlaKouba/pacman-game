#pragma once
#include <SFML/Graphics.hpp>
#include "Sound.h"

class Menu {
public:
	Menu();
	void ShowMenu();
	void CreateButtons(sf::Text& startText, sf::Text& helpText, sf::Text& exitText, int& height, int& width, sf::Texture& backgroundTexture, sf::Font& font, sf::Texture& HelpTexture);
	void getBoardSize(int& height, int& width, sf::Texture& backgroundTexture, sf::Texture& HelpTexture);
	void HelpAndBackButtons( sf::Text& Back, sf::Font& font, sf::RenderWindow& window);
	void DrawAndClear(sf::RenderWindow& window, sf::Text& startText, sf::Text& helpText, sf::Text& exitText, sf::Sprite& backgroundSprite);
	void MenuClick(sf::Event& event, int& height, int& width, sf::RenderWindow& window, sf::Text& startText,
		sf::Text& helpText, sf::Text& exitText, sf::Sprite& backgroundSprite, sf::Text& Back, sf::Font& font, bool& back_entered);

private:
	sf::Texture backgroundTexture;
	int height, width;
	sf::Sprite backgroundSprite;
	sf::Font font;
	//sf::RenderWindow window;
	sf::Text startText, helpText, exitText, Back;
	sf::Event event;
	Sound sound;
	sf::Sprite HelpSprite;
	sf::Texture HelpTexture;

};