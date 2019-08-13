#pragma once
#include "Player.h"
#include <vector>

using namespace std;

class Character : public Player
{
public:
	Character();
	int getHealth() { return _health; }             //gets the characters health
	int getInitialHealth() { return _initHealth; }  //initial health is used to show how much the health meter holds
	void subHealth() { _health -= 1; }              //decrement character's health
	void subHealth(int pow);                        //decrement by specific amount, e.g. more powerful enemy
	bool isBlocked(char c);                         //returns true if character is blocked
	char attack() { return _attack; };              //character's attack power
	void addHealth();                               //adds three units of health, but limits health to initHealth
	void addHealth(int add);                        //same as previous but with specific amount
	

private:
	const int _initHealth = 20;                     //max health for character
	int _health = _initHealth;                      //current health
	char _attack = ' ';                             //spacebar is the players attack
	vector<char> _solidObjects = { '#','@','%',
		                           '$','&','\\',
		                           '|','/','{',
		                           '}','(','`',
		                           ')','"','\'','~'}; //objects the character cannot overlap with
};

