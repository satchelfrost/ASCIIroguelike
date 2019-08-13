/*

Original project Created by Reese A. Gallagher

Description:
This is an ascii rogulike RPG I built in my free time.
It could easily be expanded by creating more levels and differnt power ups,
but for now it is a working prototype which has a beginning, middle, and an end!

Art:
title screen letters are courtesy of:
http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
Tree art: unknown artist from asciiart.eu

*/



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Level.h"
#include "Monster.h"
#include "Character.h"


int main() 
{	
	
	Character p1;

	//instantiate enemies with symbol and coordinates
	Monster enemy(5, 5, '%');
	Monster enemy1(10, 26, '%');
	Monster enemy2(50, 26, '%');
	Monster enemy3(7, 41, '%');
	Monster enemy4(9, 102, '%');
	Monster enemy5(3, 103, '%');
	Monster enemy6(15, 103, '%');
	
	Monster enemy7(15, 132, '&'); //boss enemy
	enemy7.setAttackPower(3);     //has a higher attack power as opposed to 1
	enemy7.setAttackFreq(7);      //attack frequency is 70%

	//containter for monsters
    vector<Monster> enemies = { enemy,enemy1,enemy2,enemy3,enemy4,enemy5,enemy6,enemy7 };
	
	
	Level titleScreen("titleScreen.txt"); //title screen from text file
	titleScreen.printSection();           //print at least once
	char input = _getwch();               //wait for user to press any key
	system("cls");                        //clear screen; windows only

	Level level01("level01.txt");                            //load level01   
	while (!level01.passedLevel() && !level01.gameOver()) {  //while we haven't had a game over or passed level
		level01.updateSection(p1, enemies, input);           //update changes to the level and sprites
		input = _getwch();                                   //get keyboard input
	}

	system("cls");  //clear level 1 so we can print level 2

	if (level01.gameOver()) {
		cout << "You were defeated...\n\n";
		cout << "Press 1 to continue\n";
		input = 'n';
		while (input != '1') {
			input = _getwch();                       //wait for user to hit specified key
		}
	}
	
	else {                                           //otherwise
		Character p2;                                //instantiate player for level 2
		Level level02("finalScreen.txt");            //load level02
		level02.printSection();                      //print at least once
		while (true) {                               //never ending loop since they won the game
			level02.updateSection(p2, input);        //last level only contains the character
			input = _getwch();                       //get keyboard input
		}
	}

	system("pause");
	return 0;
}



