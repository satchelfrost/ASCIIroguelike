#include "Level.h"

Level::Level(string levelFile)
{   
	//load the level from the text file into vector
	ifstream inputFile;
	string input;
	inputFile.open(levelFile);
	while (getline(inputFile, input)) _levelLine.push_back(input);	
	inputFile.close();
	_levelHeight = _levelLine.size();     //define the level height
	_levelWidth = _levelLine[0].length(); //define the level width

	if (_levelHeight < _kScreenHeight) _bottom = _kScreenHeight = _levelHeight;
	//printSection();
}

bool Level::canMove(Character &p, char dir)
{//returns false if the player is not allowed to move in a particular direction
	switch (dir) {//checks if the direction moved is blocked by another character or a wall
	case 'w': if (p.isBlocked(up(p)))    { return false; break; }//check up
			  else return true;
	case 's': if (p.isBlocked(down(p)))  { return false; break; }//check down
			  else return true;
	case 'a': if (p.isBlocked(left(p)))  { return false; break; }//check left
			  else return true;
	case 'd': if (p.isBlocked(right(p))) { return false; break; }//check right
			  else return true;
	default: return true; //player is allowed to move in given direction
	}
}

bool Level::enemyCanMove(Monster &m, char dir)
{
	{//returns false if the player is not allowed to move in a particular direction
		switch (dir) {//checks if the direction moved is blocked by another character or a wall
		case 'w': if (m.isBlocked(up(m))) { return false; break; }//check up
				  else return true;
		case 's': if (m.isBlocked(down(m))) { return false; break; }//check down
				  else return true;
		case 'a': if (m.isBlocked(left(m))) { return false; break; }//check left
				  else return true;
		case 'd': if (m.isBlocked(right(m))) { return false; break; }//check right
				  else return true;
		default: return true; //player is allowed to move in given direction
		}
	}
}

char Level::directionOfCharObject(Player &p, char object)
{//returns the direction in which the player needs to move to get object
 //if the player is within one move of the object
	if (up(p)    == object) return 'w'; //up
	if (down(p)  == object) return 's'; //down
	if (left(p)  == object) return 'a'; //left
	if (right(p) == object) return 'd'; //right
	return false; //object not found
}

void Level::resetCursor()
{
	//resets the cursor to a position to the bottom right of the screen
	setCursorPosition(_levelWidth + 1, _bottom - _top - 2); 
}

void Level::writeDialog(string dialog)
{//writes dialog to the bottom right of the screen
	setCursorPosition(_levelWidth + 1, _bottom - _top - 1);
	cout << dialog;

	_dialogHasBeenWritten = true;
}

void Level::displayCharacterInfo(Character &c)
{
	displayHealthBar(c);
}

void Level::displayHealthBar(Character &c)
{
	//display health
	setCursorPosition(_levelWidth + 2, _bottom - _top - 3);
	cout << "Health:";

	//clear old health bar
	setCursorPosition(_levelWidth + 1, _bottom - _top - 2);
	cout << "                            ";

	//start new health bar
	setCursorPosition(_levelWidth + 1, _bottom - _top - 2);
	cout << "~";

	//each '|' represents a unit of health
	for (int i = 0; i < c.getHealth(); i++) cout << '|';
	
	//end health bar
	setCursorPosition(_levelWidth + 1 + c.getInitialHealth() + 1, _bottom - _top - 2);
	cout << "~";
}

void Level::displayEnemyHealth(Monster &m)
{
	//display health
	setCursorPosition(_levelWidth + 2, _bottom - _top - 5);
	cout << "Enemy Health: " << m.getHealth();
}

void Level::clearEnemyHealth() {
	setCursorPosition(_levelWidth + 2, _bottom - _top - 5);
	cout << "               ";
}

void Level::setCursorPosition(int x, int y)
{//puts the cursor on a particular position so that a character can be drawn
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

bool Level::scrollScreen(Character &p)
{//scrolls the screen and returns true when the screen has been scrolled (only up and down for now)

	//if the player is within 3 units of the bottom of the screen
	//and as long as the player is not at the bottom section of the level
	//scroll screen down
	if (p.posY() > _bottom - 3 && _bottom != _levelHeight) {
		_top += _kScrollAmt;    //set new top
		_bottom += _kScrollAmt; //set new bottom

		if (_bottom > _levelHeight) {               //if the bottom is now greater than the level height
			_bottom = _levelHeight;                 //readjust the bottom to be equal to level height
			_top = _levelHeight - _kScreenHeight;   //readjust the top
		}
		return true;
	}

	//if the player is within 3 units of the top of the screen
	//and as long as the player is not at the top section of the level
	//scroll screen up
	if (p.posY() < _top + 3 && _top != 0) {
		_top -= _kScrollAmt;    //set new top
		_bottom -= _kScrollAmt; //set new bottom

		if (_top < 0) {               //if the top is less than zero
			_top = 0;                 //readjust the top to equal zero
			_bottom = _kScreenHeight; //readjust the bottom
		}
		return true;
	}
	return false;
}

bool Level::isEnemyAround(Character &p, Monster &enemy)
{
	if (enemy.posX() == p.posX()) {//check up and down
		if (enemy.posY() + 1 == p.posY() || enemy.posY() - 1 == p.posY())
			return true;
	}

	if (enemy.posY() == p.posY()) {//check left and right
		if (enemy.posX() + 1 == p.posX() || enemy.posX() - 1 == p.posX())
			return true;
	}

	if (enemy.posY() + 1 == p.posY()) {//check upper diagonal
		if (enemy.posX() + 1 == p.posX() || enemy.posX() - 1 == p.posX())
			return true;
	}

	if (enemy.posY() - 1 == p.posY()) {//check lower diagonal
		if (enemy.posX() + 1 == p.posX() || enemy.posX() - 1 == p.posX())
			return true;
	}

	return false;
}

void Level::handleASpace(Character &p, char input)
{
	if (directionOfCharObject(p, ' ') == input) {
		p.onSpace(true);
		//if they haven't obtained the stone of truth then say so
		if (!_obtainedStone) writeDialog("You have not obtained the Stone of Truth!");
		else {
			writeDialog("You will now enter The Sacred Forest");
			_passedLevel = true;
		}
	}
	else p.onSpace(false);
}

void Level::handleStone(Character &p, char input)
{
	if (directionOfCharObject(p, '*') == input) {
		writeDialog("You obtained the Stone of Truth");
		_obtainedStone = true;
		p.addHealth(15);
		displayHealthBar(p);

	}
}

void Level::healthPickup(Character &p, char input)
{
	if (directionOfCharObject(p, '+') == input) {
		writeDialog("health +3!");
		p.addHealth();
		displayHealthBar(p);
	}
}

void Level::handlePrevPosition(Character &p)
{
	//Destroy the player sprite at old position
    //if the player was just on a space, replace previous position with a space
	if (p.wasOnSpace()) _levelLine[p.lastPosY()][p.lastPosX()] = ' ';
	//otherwise replace previous position with a period
	else                _levelLine[p.lastPosY()][p.lastPosX()] = '.';

	//if the player is currently on a space, then in the future you can say they were on a space.
	if (p.isOnSpace()) p.setWasOnSpace(true);
	else               p.setWasOnSpace(false);
}

void Level::destroySprite(Player &p)
{
	//Destroy sprite at old position
	_levelLine[p.lastPosY()][p.lastPosX()] = '.';
}

void Level::spawnSprite(Player &p)
{//Spawn the player sprite at new position
	
	_levelLine[p.posY()][p.posX()] = p.playerSymbol();
}

void Level::killSprite(Monster &p)
{//turn sprite into the background a.k.a '.'
	_levelLine[p.posY()][p.posX()] = '.';         //changes sprite to a '.' in memory
	setCursorPosition(p.posX(), p.posY() - _top); //sets the cursor to where the sprite currently is
	cout << _levelLine[p.posY()][p.posX()];       //commits the change to the screen

	p.kill();

	//p.setPos(0, 0); //set player sprite off the screen
	//p.setSym('#');

}

void Level::manageCharacter(Character &p, char input)
{//manage player movements and states
	//if we can move in the input direction, update sprite movements
	if (canMove(p, input)) {     //if main character can move carry out the following
		handleASpace(p, input);  //handle what happens if a player lands on a space
		handleStone(p, input);   //handle what happens if a player lands on a stone
		healthPickup(p, input);  //handles any health that the character picks up
		p.updatePos(input);      //update player coordinates
		//printCoordinates(p);   //print player coordinates; debug feature only
		handlePrevPosition(p);   //handles the previous position the Character was at
		spawnSprite(p);          //Spawn the player sprite at new position
	}
}

void Level::manageAttack(Character &p, Monster &enemy, char input)
{
	if (isEnemyAround(p,enemy))           //isEnemyAround(p)    //if enemy is near, someones health is going to suffer
	{
		if (input == p.attack()) {       //if the player attacked the enemy
			enemy.subHealth();           //the enemy's health suffered
			displayEnemyHealth(enemy);   //display the enemy's health

		}

		if (enemy.getHealth() <= 0) {
			killSprite(enemy);
			enemy.kill();
			clearEnemyHealth();
			
		}

		if (enemy.shouldAttack() && enemy.getHealth() > 0) {      //if the enemy should attack
			p.subHealth(enemy.attackPower());               //subtract character's health
			displayHealthBar(p);	     //then display the character's health bar
		}

		if (p.getHealth() <= 0) _gameOver = true; //if characters health is too low: game over
	}
}

void Level::manageEnemy(Monster &enemy, char input)
{//manage player movements
	//if we can move in the input direction, update sprite
	if (enemyCanMove(enemy, input)) {
		enemy.updatePos(input);    //update enemy coordinates
		destroySprite(enemy);      //Destroy sprite image at old position
		spawnSprite(enemy);        //Spawn the player sprite image at new position
	} 
}

void Level::printSection()
{
	//print out section of the level
	for (int i = _top; i < _bottom; i++) {      //prints from top to bottom
		for (int j = 0; j < _levelWidth; j++) { //prints from left to right
			setCursorPosition(j, i - _top);
			cout << _levelLine[i][j];
		}
	}
}

float Level::distance(float x1, float y1, float x2,  float y2)
{//distance formula between two players
	float xDiff = x2 - x1;
	float yDiff = y2 - y1;
	float xDs = xDiff * xDiff;
	float yDs = yDiff * yDiff;
	float distance = sqrt(xDs + yDs);

	return distance;
}

char Level::chaseCharacter(Character &p, Monster &enemy)
{//returns the "movement":'w','s','a','d' the enemy has to move to catch the player

	//gather the distances between the player and the enemy if the enemy were to move up, down, left, or right
	float d1 = distance(p.posX(), p.posY(), enemy.posX()    , enemy.posY() - 1); //if enemy moved up
	float d2 = distance(p.posX(), p.posY(), enemy.posX()    , enemy.posY() + 1); //if enemy moved down
	float d3 = distance(p.posX(), p.posY(), enemy.posX() - 1, enemy.posY()    ); //if enemy moved left
	float d4 = distance(p.posX(), p.posY(), enemy.posX() + 1, enemy.posY()    ); //if enemy moved right
	
	float distances[4] = { d1,d2,d3,d4 };

	//find the index of the shortest distance between player and enemy
	int index = 0;
	for (int i = 1; i < 4; i++) if (distances[i] < distances[index]) index = i; //save index of shortest distance
	return _movements[index];                                                   //use index to return a movement
}

void Level::printCoordinates(Character &p)
{//debug feature only
	setCursorPosition(_levelWidth + 1, _bottom - _top - 4);
	cout << "The player position is: (" << p.posX()
		<< "," << p.posY() << ") ";
}

void Level::printCharacter(Character &p)
{   
	//player
	//spawn the player at new position
	setCursorPosition(p.posX(), p.posY() - _top);
	cout << _levelLine[p.posY()][p.posX()];
	//destroy sprite at previous position
	setCursorPosition(p.lastPosX(), p.lastPosY()- _top);
	cout << _levelLine[p.lastPosY()][p.lastPosX()];

}

void Level::printEnemy(Monster &m)
{

	//Enemy
	setCursorPosition(m.posX(), m.posY() - _top);
	cout << _levelLine[m.posY()][m.posX()];
	//destroy sprite at previous position
	setCursorPosition(m.lastPosX(), m.lastPosY() - _top);
	cout << _levelLine[m.lastPosY()][m.lastPosX()];

}

bool Level::enemyIsOnScreen(Monster &enemy)
{
	if (enemy.posY() >= _top && enemy.posY() < _bottom && !enemy.isDead()) return true;
	else return false;
}

void Level::clearDialog()
{
	//first clear the dialog screen if it was used previously
	if (_dialogHasBeenWritten) {
		writeDialog("                                                  "); //clear previous dialog
		_dialogHasBeenWritten = false;
	}
}

void Level::initialUpdate(bool firstUpdate, Monster &enemy, Character &p)
{//only one enemy
	if (firstUpdate) {
		manageEnemy(enemy, chaseCharacter(p, enemy)); //put enemy in location, regardless if it is on screen
		printSection();                          //print the first section at least once
		displayHealthBar(p);                       //displays the characters health bar
		_firstUpdate = false;
	}
}

void Level::initialUpdate(bool firstUpdate, vector<Monster> &enemies, Character &p)
{//multiple enemies
	if (firstUpdate) {
		for (int i = 0; i < enemies.size(); i++)
			manageEnemy(enemies[i], chaseCharacter(p, enemies[i]));
		printSection();
		displayHealthBar(p);
		_firstUpdate = false;
	}
}

void Level::updateSection(Character &p, char input)
{//one character no enemies
	clearDialog();
	if (_firstUpdate) displayHealthBar(p);
	manageCharacter(p, input);
	if (scrollScreen(p)) printSection(); //if the screen has scrolled print out a new section of the level
	else {                               //otherwise print only what's necessary
		printCharacter(p);                             //print the character to the screen
		resetCursor();                                 //set cursor off to the side
	}
}

void Level::updateSection(Character &p, Monster &enemy, char input)
{//one character one enemy
	clearDialog();                                                         //clear previous dialog if necessary
	initialUpdate(_firstUpdate, enemy, p);                                 //handles the first update
	if (enemyIsOnScreen(enemy)) manageEnemy(enemy, chaseCharacter(p, enemy)); //manage enemy states
	manageCharacter(p, input);                                                //manage player states
	manageAttack(p, enemy, input);       //manage attacks of enemy and player
	if (scrollScreen(p)) printSection(); //if the screen has scrolled print out a new section of the level
	else {                               //otherwise print only what's necessary
		if (enemyIsOnScreen(enemy)) printEnemy(enemy); //print enemy if its on the screen
		printCharacter(p);                             //print the character to the screen
		resetCursor();                                 //set cursor off to the side
	}
}

void Level::updateSection(Character &p, vector<Monster> &enemies, char input)
{//one character, multiple enemies
	clearDialog();                           //clear previous dialog if necessary 
	initialUpdate(_firstUpdate, enemies, p); //handles the first update
	for (Monster &enemy : enemies)
		if (enemyIsOnScreen(enemy))
			manageEnemy(enemy, chaseCharacter(p, enemy));

	manageCharacter(p, input);

	for (Monster &enemy : enemies) {
		if (enemyIsOnScreen(enemy)) {
			manageAttack(p, enemy, input); //manage attacks
		}
	}

	if (scrollScreen(p)) printSection();
	else {
		for (Monster &enemy : enemies)
			if (enemyIsOnScreen(enemy))
				printEnemy(enemy);
		printCharacter(p);
		resetCursor();
	}

}






