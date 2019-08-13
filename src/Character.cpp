#include "Character.h"



Character::Character()
{
}

bool Character::isBlocked(char c)
{
	for (char object : _solidObjects) if (c == object) return true;
	return false;
}

void Character::addHealth()
{
	_health += 3;
	if (_health > _initHealth) _health = _initHealth;
}

void Character::addHealth(int add)
{
	_health += add; 
	if (_health > _initHealth) _health = _initHealth;
}

void Character::subHealth(int pow)
{
	_health -= pow; 
	if (_health > _initHealth) _health = _initHealth;
}


