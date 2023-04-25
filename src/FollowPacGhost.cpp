#include "FollowPacGhost.h"

const int delay = 5;

FollowPacGhost::FollowPacGhost(int x, int y)
	:Ghost(x, y), stopGhost(false)
{}

bool FollowPacGhost::IsSupPac(Board& board) {

	if (board.get_Is_StopGhostGift())
		return false;

	return true;
}

bool FollowPacGhost::IsStopGhost(Board& board) {
	if (board.get_Is_StopGhostGift())
		return false;

	return true;
}
void FollowPacGhost::move(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)

{
	sf::Vector2f pos = m_sprite.getPosition();
	int x = 0, y = 0;
	for (auto& obj : board.get_m_moving()) {
		if (auto  pacman = dynamic_cast<PacMan*>(obj.get())) {
			x = pacman->getSprite().getPosition().x;
			y = pacman->getSprite().getPosition().y;
			break;
		}
	}

	if (!board.get_Is_SupPacGift())
	{
		if (x < pos.x)
		{
			moving(sf::Vector2f(-20, 0), sf::Vector2f(20, 0), board, vertex, CharFound, pos2, pos, c);
		}

		else if (x > pos.x)
		{
			moving(sf::Vector2f(20, 0), sf::Vector2f(-20, 0), board, vertex, CharFound, pos2, pos, c);
		}
		else {
			if (y < pos.y)
			{
				moving(sf::Vector2f(0, -20), sf::Vector2f(0, 20), board, vertex, CharFound, pos2, pos, c);
			}

			else if (y > pos.y)
			{
				moving(sf::Vector2f(0, 20), sf::Vector2f(0, -20), board, vertex, CharFound, pos2, pos, c);
			}
		}
	}

	else
	{
		if (x > pos.x)
		{
			moving(sf::Vector2f(-20, 0), sf::Vector2f(20, 0), board, vertex, CharFound, pos2, pos, c);
		}

		else if (x < pos.x)
		{
			moving(sf::Vector2f(20, 0), sf::Vector2f(-20, 0), board, vertex, CharFound, pos2, pos, c);
		}
		else {
			if (y > pos.y)
			{
				moving(sf::Vector2f(0, -20), sf::Vector2f(0, 20), board, vertex, CharFound, pos2, pos, c);
			}

			else if (y < pos.y)
			{
				moving(sf::Vector2f(0, 20), sf::Vector2f(0, -20), board, vertex, CharFound, pos2, pos, c);
			}
		}
	}

}

void FollowPacGhost::setTexture() {

	if (!m_texture.loadFromFile("RedGhost.png")) {
		std::cerr << "Failed to load door texture" << std::endl;
		exit(EXIT_FAILURE);
	}

	m_sprite.setTexture(m_texture);
}
// -----------------------------------------------------------------------------------------
sf::Sprite& FollowPacGhost::getSprite() {
	return m_sprite;
}
// -----------------------------------------------------------------------------------------
void FollowPacGhost::setPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}
// -----------------------------------------------------------------------------------------
bool FollowPacGhost::checkMove(Board& board, Vertex& vertex, bool& CharFound, sf::Vector2f& pos2, char& c)
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

bool FollowPacGhost::pacManGhost(Board& board) {
	sf::Vector2f pos = m_sprite.getPosition();

	if (board.get_arr()[pos.y / 20][pos.x / 20] == 'a' && !board.get_Is_SupPacGift())
		return true;
	return false;
}

void FollowPacGhost::moving(sf::Vector2f speed, sf::Vector2f ops_speed, Board& board,
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

void FollowPacGhost::KeepChar(Board& board, sf::Vector2f& pos2, sf::Vector2f& pos, bool& CharFound) {
	pos2 = pos;
	board.get_arr()[pos.y / 20][pos.x / 20] = '&';
	CharFound = true;
}