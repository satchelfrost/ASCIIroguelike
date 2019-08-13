#pragma once
#include <iostream>

class Player
{
public:
	Player();
	Player(int posX, int posY, char playerSym);
	int  posX()           { return _posX;		 }
	int  posY()           { return _posY;      }
	int  lastPosX()       { return _lastPosX;  }
	int  lastPosY()       { return _lastPosY;  }
	char playerSymbol()   { return _playerSym; }
	void setSym(char sym) { _playerSym = sym; }
	
	void setPos(int Y, int X);
	void updatePos(char dir); 
	void printPos();            
	void printLastPos();
	bool isOnSpace()  { return _onSpace; }
	bool wasOnSpace() { return _wasOnSpace; }
	void onSpace(bool onSpace) {_onSpace = onSpace; }
	void setWasOnSpace(bool wasOnSpace) { _wasOnSpace = wasOnSpace; }

private:
	int  _posX;
	int  _posY;      
	int  _lastPosX = 5;
	int  _lastPosY = 28;
	char _playerSym;
	bool _onSpace = false;
	bool _wasOnSpace = false;
};

