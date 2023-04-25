#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

class Sound {
public:
	Sound();
	sf::Sound& startSound();
	sf::Sound& pacmanWalking();
	sf::Sound& pacmanCakeEating();
	sf::Sound& pacmanDeath();
private:
	sf::SoundBuffer m_startBuffer;
	sf::SoundBuffer m_walkingBuffer; 
	sf::SoundBuffer m_cakeEatingBuffer;
	sf::SoundBuffer m_deathBuffer;
	sf::Sound m_startMusic;
	sf::Sound m_walkingMusic;
	sf::Sound m_cakeEatingMusic;
	sf::Sound m_deathMusic;
};
