#include "Monster.h"



Monster::Monster()
{

}

bool Monster::isBlocked(char c)
{//check if monster can move in a particular position
	for (char object : _solidObjects) if (c == object) return true;
	return false;
}

bool Monster::shouldAttack()
{ //handles monsters attack
	int range = 1 + rand() % 10;                //random integer between 1 and 10; inclusive.
	if (range <= _attackFrequency) return true; //percentage of the time the enemy will attack
	                                            //e.g. if _attackFrequency is 3, then the enemy
	                                            //will attack 30 % of the time.
	                                            //for every 10 game ticks, the enemy will attack 3 times
	return false;
}


