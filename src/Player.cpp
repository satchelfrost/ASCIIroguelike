#include "Player.h"

using namespace std;

Player::Player()
{//default constructor can be the main player sprite and start position
	_posX = 28;
	_posY = 5;
	_playerSym = '@';
}

Player::Player(int posX, int posY, char playerSym)
{//any other player instantiated will need their position and symbol to start.
	_posX = posX;
	_posY = posY;
	_playerSym = playerSym;
}

void Player::updatePos(char dir)
{
	//save old positions first
	_lastPosX = _posX;
	_lastPosY = _posY;

	//update new positions
	switch (dir) {
	case 'd': _posX++; break;
	case 'a': _posX--; break;
	case 'w': _posY--; break;
	case 's': _posY++; break;
	}	
}

void Player::setPos(int Y, int X)
{
	_posX = X;
	_posY = Y;
	//cout << "_posY " << _posY;
}

void Player::printPos()
{
	cout << "\nThe player position is: (" << _posX
		 << "," << _posY << ")\n";
}

void Player::printLastPos()
{
	cout << "\nThe last player position was: (" << _lastPosX
		<< "," << _lastPosY << ")\n";
}
