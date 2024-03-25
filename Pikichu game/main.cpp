#include <iostream>
#include <Windows.h>
#include "Controls.h"
#include "Game_logic.h"
#include "Rendering.h"

using std::make_pair;
using std::string;
using std::cout;
using std::cin;

//struct and typedef
typedef std::pair<int, int> Point;

/*
Notes:

function name should be writen like this:
type functionName(){}
camel case

Variable should be:
type variable_name;
snake case

Struct/Class should be:
Struct/Class Item(){};
one word, captital first letter

*/

//bug to fix for menu
//when setting option move from 3 to 2 and switch on light mode
// 2 select cursor appear
// 
// error at line 237
// 
//move cursor to x;y on the console
//x is the horizontal axis
//y is the vertical axis

//to do
//add leaderboard
//add bin file to store var
//redecorate everything
//fix the printing and x / y order of functions

int main()
{
	srand(time(0));

	bool run = true;

	int volume = 10;
	bool light_mode = false;

	//-2 for the actual size, as 2 is reserved for the rim
	int board_x;
	int board_y;

	resizeConsole(905, 400, 200, 200);
	printMainMenu(0, 0, false);
	while (run)
	{
		if (menuInteraction(volume, light_mode, board_x, board_y) == true)
		{
			//start game
			resizeConsole(1401, 930, 200, 200);
			gameplayLoop(board_x, board_y);

			//print the menu again after a game is done
			resizeConsole(905, 400, 200, 200);
			printMainMenu(0, 0, false);
		}
		else
		{
			//quit game
			run = false;
		}
	}

	//setCursorPosition(0, 54);
	return 0;
}