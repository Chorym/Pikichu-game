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
	/*
	debug
	std::fstream fin;
	fin.open("debug.txt");
	*/

	HWND console = GetConsoleWindow();
	MoveWindow(console, 225, 150, 1401, 903, TRUE);

	//uncomment this to load the menu
	/*
	printMainMenu(0, 0, false);
	menuInteraction();
	*/

	//uncomment this to load the gameplay
	
	srand(time(0));
	//-2 for the actual size, as 2 is reserved for the rim
	int board_x = 12;
	int board_y = 10;
	if (board_x * board_y % 2 != 0)
	{
		cout << "wrong dimensions" << "\n";
		return 0;
	}

	gameplayLoop(board_x, board_y);
	setCursorPosition(0, 54);
	return 0;
}