#include"Sound.h"
Sound::Sound() {

	if (!m_startBuffer.loadFromFile("pacman_beginning.wav"))
		std::cerr << "error in loading sound file";
	m_startMusic.setBuffer(m_startBuffer);

	if (!m_walkingBuffer.loadFromFile("pacmanWalking.wav"))
		std::cerr << "error in loading sound file";
	m_walkingMusic.setBuffer(m_walkingBuffer);

	if (!m_cakeEatingBuffer.loadFromFile("pacman_eatfruit.wav"))
		std::cerr << "error in loading sound file";
	m_cakeEatingMusic.setBuffer(m_cakeEatingBuffer);

	if (!m_deathBuffer.loadFromFile("pacman_death.wav"))
		std::cerr << "error in loading sound file";
	m_deathMusic.setBuffer(m_deathBuffer);
}

sf::Sound& Sound::startSound() {
	return m_startMusic;
}

sf::Sound& Sound::pacmanWalking() {
	return m_walkingMusic;
}

sf::Sound& Sound::pacmanCakeEating() {
	return m_cakeEatingMusic;
}

sf::Sound& Sound::pacmanDeath() {
	return m_deathMusic;
}
