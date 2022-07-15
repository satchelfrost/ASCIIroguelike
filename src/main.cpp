#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Level.h"
#include "Monster.h"
#include "Character.h"

#ifdef WIN32
#else
  #include "getch.h"
#endif

void updateInput(char& input) {
  #ifdef WIN32
    input = _getwch(); //get keyboard input
  #else
    input = getch();
  #endif
}

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
  vector<Monster> enemies = { enemy, enemy1, enemy2,enemy3,enemy4,enemy5,enemy6,enemy7 };
	
	
	Level titleScreen("titleScreen.txt"); //title screen from text file
	titleScreen.printSection();           //print at least once
	char input;
  updateInput(input);
  #ifdef WIN32
	  system("cls");
  #else
    system("clear");
  #endif

	Level level01("level01.txt");                            //load level01   
	while (!level01.passedLevel() && !level01.gameOver()) {  //while we haven't had a game over or passed level
		level01.updateSection(p1, enemies, input);           //update changes to the level and sprites
    updateInput(input);
	}

	system("cls");  //clear level 1 so we can print level 2

	if (level01.gameOver()) {
		cout << "You were defeated...\n\n";
		cout << "Press 1 to continue\n";
		input = 'n';
		while (input != '1') {
			updateInput(input);
		}
	}
	else {
		Character p2;
		Level level02("finalScreen.txt");
		level02.printSection();
		while (true) {
			level02.updateSection(p2, input);
      updateInput(input);
		}
	}

	system("pause");
	return 0;
}