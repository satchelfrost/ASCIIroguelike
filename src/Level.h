#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Player.h"
#include <fstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "Character.h"
#include "Monster.h"

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;

class Level
{
public:
	Level(string level);
	void updateSection(Character &p, vector<Monster> &enemies, char input);  //one character multiple enemies
	void updateSection(Character &p, Monster &enemy, char input);            //one character one enemy
	void updateSection(Character &p, char input);                            //one character no enemies
	bool passedLevel() { return _passedLevel; }
	bool gameOver() { return _gameOver; }
	void printSection();

private:
	vector<string> _levelLine;                            //vector that holds each line of the level
	vector<char> _enemies = { '&','$','%' };              //enemy sprites
	
	int _kScreenHeight = 24;       //height of the screen 24
	int _kScrollAmt = 15;          //amount screen will scroll
	int _levelHeight;              //height of the entire level
	int _levelWidth;               //width of the entire level
	int _top = 0;                  //initialize the top of the screen to start at zero
	int _bottom = _kScreenHeight;  //initialize the bottom of the screen to be the screen height

	bool _gameOver = false;
	bool _obtainedStone = false;               //decides if the player has obtained the stone of truth
	bool _passedLevel = false;                 //will be changed to true when player passes the level
	bool _firstUpdate = true;                  //needed because the first level update is special
	bool _dialogHasBeenWritten = false;        //needed so that the dialog is only updated after a new change
	char _movements[4] = { 'w','s','a','d' };  //possible movements corresponding to up, down, left, and right
	
	
	bool isEnemyAround(Character &p, Monster &enemy); //checks if an enemy is around character
	bool canMove(Character &p, char dir);             //decides if a character can move based on c.isBlocked()
	bool enemyCanMove(Monster &m, char dir);          //decides if an enemy can move based on m.isBlocked()
	bool scrollScreen(Character &p);                  //scrolls screen the _scrollAmt (only up and down)
	bool enemyIsOnScreen(Monster &enemy);             //is an enemy anywhere on screen

	void resetCursor();                        //sets cursor off to the side
	void printEnemy(Monster &m);               //prints the enemy on the screen
	void displayCharacterInfo(Character &c);   //prints any charcter info e.g. health bar, etc.
	void displayHealthBar(Character &c);       //displays the health bar
	void displayEnemyHealth(Monster &m);       //display enemy health
	void clearEnemyHealth();                   //clears the enemy's health as is written to the screen
	void setCursorPosition(int x, int y);      //sets the cursor to a particular location
	void writeDialog(string dialog);           //writes string in the specified dialog area
	void manageCharacter(Character &p, char input);                         //see defintion in function
	void manageEnemy(Monster &enemy, char input);                        //see definition in function
	void printCharacter(Character &p);                                   //prints the main character
	void printCoordinates(Character &p);                                 //prints the character's coordinates
	void handleASpace(Character &p, char input);                         //handles when character lands on a space
	void handleStone(Character &p, char input);                          //handles stone of truth
	void healthPickup(Character &p, char input);                         //handles health pickup
	void handlePrevPosition(Character &p);                               //handles the characters previous position
	void destroySprite(Player &p);                                       //destroys spriteImage at previous position
	void spawnSprite(Player &p);                                         //spawn spriteImage at new position
	void clearDialog();                                                  //clears previous dialog
	void initialUpdate(bool firstUpdate, Monster &enemy, Character &p);  //handles the very first updateSection
	void initialUpdate(bool firstUpdate, vector<Monster> &enemy, Character &p);//first update multi-enemy
	void killSprite(Monster &p);                                          //kills the sprite permanantly
	void manageAttack(Character &p, Monster &enemy, char input);         //manage enemy and monster attack / health
	float distance(float x1, float y1, float x2, float y2);              //mathematical distance formula
	          
	char chaseCharacter(Character &p, Monster &enemy);                      //see definition in function
	char directionOfCharObject(Player &p, char object);                  //see definition in function
	char up(Player &p)    { return _levelLine[p.posY() - 1][p.posX()]; } //returns char above player
	char down(Player &p)  { return _levelLine[p.posY() + 1][p.posX()]; } //returns char below player
	char left(Player &p)  { return _levelLine[p.posY()][p.posX() - 1]; } //returns char to the left of player
	char right(Player &p) { return _levelLine[p.posY()][p.posX() + 1]; } //returns char to the right of player
};


