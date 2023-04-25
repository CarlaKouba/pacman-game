#include "Menu.h"
#include "GameController.h"

Menu::Menu(){

    ShowMenu();
}
//----------------------------------------------------------
void Menu::ShowMenu() {

    font.loadFromFile("C:\\Windows\\Fonts\\GIGI.ttf");

    CreateButtons(startText, helpText, exitText, height, width, backgroundTexture,font, HelpTexture);
    
    sf::RenderWindow window(sf::VideoMode(height, width), "My Game");
    sound.startSound().play();
    backgroundSprite.setTexture(backgroundTexture);
    HelpSprite.setTexture(HelpTexture);
    bool back_entered = false;

    while (window.isOpen()){
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved)
            {
                if (startText.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    startText.setFillColor(sf::Color::Red);

                else
                    startText.setFillColor(sf::Color::Yellow);

                if (helpText.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    helpText.setFillColor(sf::Color::Red);

                else
                    helpText.setFillColor(sf::Color::Yellow);

                if (exitText.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    exitText.setFillColor(sf::Color::Red);

                else
                    exitText.setFillColor(sf::Color::Yellow);

            }

            if (event.type == sf::Event::MouseButtonReleased) {
                MenuClick(event, height, width, window, startText,
                    helpText, exitText, backgroundSprite, Back, font, back_entered);
            }
        }
        DrawAndClear(window, startText, helpText, exitText, backgroundSprite);

        window.display();
    }
}
//----------------------------------------------------
void Menu::CreateButtons(sf::Text& startText,sf::Text& helpText,sf::Text& exitText,int &height,int&width, sf::Texture& backgroundTexture,sf::Font& font, sf::Texture& HelpTexture)
{
    getBoardSize(height, width, backgroundTexture, HelpTexture);
    sf::Text start("START  THE  GAME", font, 50);
    sf::Text help("HELP", font, 50);
    sf::Text exit("EXIT", font, 50);

    startText = start;
    helpText = help;
    exitText = exit;

    startText.setPosition(height / 25, width / 5);
    helpText.setPosition(height / 10, width / 5 + 150);
    exitText.setPosition(height / 10, width / 5 + 300);

    startText.setFillColor(sf::Color::Yellow);
    helpText.setFillColor(sf::Color::Yellow);
    exitText.setFillColor(sf::Color::Yellow);
}
//-----------------------------------
void Menu::getBoardSize(int& height, int& width, sf::Texture& backgroundTexture, sf::Texture &HelpTexture) {

    backgroundTexture.loadFromFile("pacmanBackGround.png");
    HelpTexture.loadFromFile("Help.png");
    height = backgroundTexture.getSize().x;
    width = backgroundTexture.getSize().y;
}
//-----------------------------------
void Menu::HelpAndBackButtons( sf::Text& Back, sf::Font& font, sf::RenderWindow& window)
{
    sf::Text BackText("Back To Menu", font, 26);
    Back = BackText;
    Back.setPosition(50, 400);
    window.clear();
    window.draw(HelpSprite);
    window.draw(Back);

}
//-----------------------------------
void Menu::DrawAndClear(sf::RenderWindow& window, sf::Text& startText, sf::Text& helpText, sf::Text& exitText,sf::Sprite& backgroundSprite) 
{
    window.clear();
    window.draw(backgroundSprite);
    window.draw(startText);
    window.draw(helpText);
    window.draw(exitText);
}
//-----------------------------------
void Menu::MenuClick(sf::Event& event,int& height,int&width, sf::RenderWindow& window, sf::Text& startText, 
    sf::Text& helpText, sf::Text& exitText, sf::Sprite& backgroundSprite, sf::Text& Back, sf::Font& font,bool & back_entered) {

    if (startText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        window.close();
        sound.startSound().stop();
        GameController object(height, width);
    }

    else if (helpText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        back_entered = false;
        while (window.isOpen() && !back_entered) {

            HelpAndBackButtons( Back, font, window);
            window.pollEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (Back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                back_entered = true;
                DrawAndClear(window, startText, helpText, exitText, backgroundSprite);
            }
            window.display();
        }
    }
    else if (exitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        window.close();
        exit(EXIT_SUCCESS);
    }
}

