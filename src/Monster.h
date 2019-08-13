#pragma once
#include "Player.h"
#include <vector>

using namespace std;

class Monster : public Player
{
public:
	Monster();
	using Player::Player;                                     //use players constructor for now
	bool isBlocked(char c);                                   //check if monster can move in a particular direction
	bool shouldAttack();                                      //will return true if monster should attack
	void subHealth() { _health -= 1; }                        //subtracts one health unit from monster
	int getHealth() { return _health; }                       //returns monster's health
	void setAttackFreq(int freq) { _attackFrequency = freq; } //decides how frequently a monster can attack
	void setAttackPower(int pow) { _attackPower = pow; }      //returns how much power a monsters attack is
	int attackPower() { return _attackPower; }                //sets the monsters attack power
	bool isDead() { return _isDead; }                         //e.g. if isDead don't print
	void kill() { _isDead = true; }                           //kills monster

private:
	int _isDead = false;      //our monster should be alive by default
	int _health = 5;          //our monsters health is 5 by default
	int _attackFrequency = 5; //can be an integer 1 - 10 corresponds to attacking 10 % vs. 100 % of the time
	int _attackPower = 1;     //how many units of the characters health a monster will take
	vector<char> _solidObjects = { '#','@','%','$','&', ' ', '*','\\','|','/' };//objects the monster cannot overlap with
};

