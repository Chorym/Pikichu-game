#include <iostream>
#include <Windows.h>
#include "Controls.h"
#include "Game_logic.h"
#include "Rendering.h"
#include "Player_data_manip.h"

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
//add function to load 1 data set from the list to use when logged in
//continue making the screen for loging in
//add feature to load board if there is one
//finish by sunday night

int main()
{
	srand(time(0));

	bool run = true;

	int volume = 10;
	bool light_mode = false;

	//-2 for the actual size, as 2 is reserved for the rim
	int board_x;
	int board_y;
	int difficulty = 0;
	int** game_board_array = nullptr;

	bool load_game = false;

	PlayerData* player_data = new PlayerData[30];
	PlayerData current_player;

	readingPlayerData("Player_data.bin", player_data);

	resizeConsole(905, 600, 200, 200);

	bool returning = printLoginScreen(player_data, current_player);
	printMainMenu(0, 0, false, current_player, returning);
	while (run)
	{
		if (menuInteraction(volume, light_mode, board_x, board_y, difficulty, load_game, current_player, player_data, returning) == true)
		{
			//start game
			if (board_x == 12) resizeConsole(1401, 930, 200, 200);
			else if (board_x == 10) resizeConsole(1201, 780, 200, 200);
			else if (board_x == 8) resizeConsole(1001, 630, 200, 200);
			gameplayLoop(board_x, board_y, difficulty, game_board_array, load_game, current_player);

			//print the menu again after a game is done
			resizeConsole(905, 600, 200, 200);
			printMainMenu(0, 0, false, current_player, returning);
		}
		else
		{
			//quit game
			run = false;
		}
	}

	savePlayerData(player_data, current_player);
	writingPlayerData("Player_data.bin", player_data);

	clear2DArray(game_board_array, board_x);
	delete[]player_data;

	setCursorPosition(0, 20);
	return 0;
}