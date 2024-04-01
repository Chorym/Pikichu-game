#include <iostream>

//playsound
#include <Windows.h>
#include <mmsystem.h>
#include <playsoundapi.h>
#pragma comment(lib, "Winmm.lib")

#include "Rendering.h"
#include "Game_logic.h"

using std::cout;
using std::make_pair;

bool isPressing(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

void gameplayLoop(int board_x, int board_y, int difficulty)
{
	//calculate timer
	int max_time = (9 - (2 * difficulty)) * 60;
	int start_game_time = currentSystemTime();
	int current_system_time = currentSystemTime();
	int previous_second = currentSystemTime();

	//
	printGameplayFrame(board_x, board_y);
	int current_cells_on_board = (board_x - 2) * (board_y - 2);

	//
	int** game_board_array = generateGameBoard(board_x, board_y);
	drawGameBoard(game_board_array, board_x, board_y);

	//some info about the current board state
	setCursorPosition(board_x * 11 + 7, 11);
	cout << max_time << "s   ";
	setCursorPosition(board_x * 11, 12);
	cout << "Remaining cells: " << current_cells_on_board;

	//
	bool run = true;
	int moving = false;

	//make sure these keys can only be pressed once until released again
	bool key_pressed_E = false;
	bool key_pressed_Q = false;

	//used to mark current cell
	Point current_point = make_pair(1, 1);
	Point previous_point = make_pair(1, 1);

	//used to clear points value
	Point empty = make_pair(-1, -1);

	//selected_points array hold the 2 points that the player chose to connect
	Point point_1 = empty;
	Point point_2 = empty;
	Point selected_points[] = { point_1, point_2 };

	Point middle_1 = empty;
	Point middle_2 = empty;
	Point mid_points[2] = { middle_1, middle_2 };

	//
	drawCurrentCell(game_board_array, current_point, previous_point, selected_points);

	//run = false; debug
	while (run)
	{
		//update timer
		current_system_time = currentSystemTime();
		if (current_system_time - previous_second >= 1)
		{
			previous_second = current_system_time;
			setCursorPosition(board_x * 11 + 7, 11);
			cout << max_time - (current_system_time - start_game_time) << "s   ";
			setCursorPosition(0, 0);
		}
		if (current_system_time - start_game_time >= max_time)
		{
			setCursorPosition(board_x * 11 + 7, 11);
			cout << "lmao skill issue";
			return;
		}

		//move horizontally
		if (isPressing('D') && !isPressing('W') && !isPressing('S'))
		{
			previous_point = current_point;
			current_point.first++;
			if (current_point.first > board_x - 2) current_point.first = 1;
			moving = true;
		}
		if (isPressing('A') && !isPressing('W'))
		{
			previous_point.first = current_point.first;
			previous_point.second = current_point.second;
			current_point.first--;
			if (current_point.first < 1) current_point.first = board_x - 2;
			moving = true;
		}


		//move vertically
		if (isPressing('W') && !isPressing('A'))
		{
			previous_point = current_point;
			current_point.second--;
			if (current_point.second < 1) current_point.second = board_y - 2;
			moving = true;
		}
		if (isPressing('S') && !isPressing('A'))
		{
			previous_point = current_point;
			current_point.second++;
			if (current_point.second > board_y - 2) current_point.second = 1;
			moving = true;
		}


		//movement
		if (moving)
		{
			drawCurrentCell(game_board_array, current_point, previous_point, selected_points);
			Sleep(200);
			moving = false;
		}


		//selecting and drawing cells
		if (isPressing('E') && !key_pressed_E)
		{
			if (game_board_array[current_point.first][current_point.second] != -1)
			{
				if (selected_points[0] == empty)
				{
					selected_points[0] = current_point;
					selectCell(game_board_array, current_point);
				}
				else if (selected_points[1] == empty)
				{
					selected_points[1] = current_point;
					selectCell(game_board_array, current_point);
				}
			}
			key_pressed_E = true;
		}
		if (!(isPressing('E')) && key_pressed_E) key_pressed_E = false;


		//canceling cells
		if (isPressing('Q'))
		{
			if (current_point == selected_points[0])
			{
				selected_points[0] = empty;
				deselecteCell(game_board_array, current_point);
			}
			else if (current_point == selected_points[1])
			{
				selected_points[1] = empty;
				deselecteCell(game_board_array, current_point);
			}
			key_pressed_Q = true;
		}
		if (!isPressing('Q') && key_pressed_Q) key_pressed_Q = false;

		//if 2 cells are selected
		if (selected_points[0] != empty && selected_points[1] != empty)
		{
			if (pathfinding2Cells(selected_points, mid_points, game_board_array, board_x, board_y))
			{
				current_cells_on_board -= 2;
				setCursorPosition(board_x * 11 + 17, 12);
				cout << current_cells_on_board << "  ";
				drawGameBoard(game_board_array, board_x, board_y);
				drawCurrentCell(game_board_array, current_point, previous_point, selected_points);

				if (mid_points[0] == empty)
				{
					drawConnection(selected_points[0], selected_points[1]);
				}
				else if (mid_points[1] == empty)
				{
					drawConnection(selected_points[0], mid_points[0]);
					drawConnection(mid_points[0], selected_points[1]);
				}
				else
				{
					drawConnection(selected_points[0], mid_points[0]);
					drawConnection(mid_points[0], mid_points[1]);
					drawConnection(mid_points[1], selected_points[1]);
				}
			}
			else
			{
				drawGameBoard(game_board_array, board_x, board_y);
				drawCurrentCell(game_board_array, current_point, previous_point, selected_points);
			}
			selected_points[0] = empty;
			selected_points[1] = empty;
			mid_points[0] = empty;
			mid_points[1] = empty;
		}

		if (current_cells_on_board == 0) //u won yay
		{
			setCursorPosition(0, 50);
			cout << "u won yay\n";
			run = false;
		}

		//exit game
		if (isPressing('F'))
		{
			setCursorPosition(0, 50);
			run = false;
		}

		//only for debugging, will be removed in the final ship
		if (isPressing('R'))
		{
			Point debug_point = current_point;
			clearCell(debug_point, game_board_array);
			drawGameBoard(game_board_array, board_x, board_y);
			drawCurrentCell(game_board_array, current_point, previous_point, selected_points);
		}
	}

	clear2DArray(game_board_array, board_x);
}

bool menuInteraction(int& volume, bool& light_mode, int& board_x, int& board_y, int& difficulty)
{
	bool run = true;

	int current_menu = 0; //0 is main menu, 1 is settings menu

	int current_option = 1;
	int previous_option = 1;

	int main_menu_option_amount = 4;
	int settings_menu_option_amount = 1;

	difficulty = 2;

	bool change_volume = false;
	bool change_lighting = false;

	while (run)
	{
		//Changing options in main menu or settings
		if (isPressing('W'))
		{
			previous_option = current_option;
			current_option--;
			if (current_option <= 0)
			{
				current_option = main_menu_option_amount;
			}
			switch (current_menu)
			{
			case 0:
				printMainMenu(current_option, previous_option, true); break;
			case 1:
				printSettingsMenu(current_option, previous_option, volume, light_mode, true, false); break;
			}
			Sleep(200);
		}
		else if (isPressing('S'))
		{
			previous_option = current_option;
			current_option++;
			if (current_option == main_menu_option_amount + 1)
			{
				current_option = 1;
			}
			switch (current_menu)
			{
			case 0:
				printMainMenu(current_option, previous_option, true); break;
			case 1:
				printSettingsMenu(current_option, previous_option, volume, light_mode, true, false); break;
			}
			Sleep(200);
		}

		//Changing settings in settings and game menu
		if (isPressing('A') && !isPressing('W') && !isPressing('S'))
		{
			if (current_menu == 1 && current_option == 1)
			{
				volume--;
				if (volume < 1) volume = 10;
				printSettingsMenu(current_option, previous_option, volume, light_mode, true, false);
				PlaySound(L"C:\\Users\\PC\\source\\repos\\Pikichu game\\SFX\\break.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			if (current_menu == 2)
			{
				difficulty--;
				if (difficulty < 1)
				{
					difficulty = 3;
				}
				printGameplayPresetScreen(difficulty, true);
			}
			Sleep(200);
		}
		else if (isPressing('D') && !isPressing('W') && !isPressing('S'))
		{
			if (current_menu == 1 && current_option == 1)
			{
				volume++;
				if (volume > 10) volume = 1;
				printSettingsMenu(current_option, previous_option, volume, light_mode, true, false);
			}
			if (current_menu == 2)
			{
				difficulty++;
				if (difficulty > 3)
				{
					difficulty = 1;
				}
				printGameplayPresetScreen(difficulty, true);
			}
			Sleep(200);
		}

		//confirm current option
		if (isPressing('E'))
		{
			//main menu
			if (current_menu == 0)
			{
				//from main to settings
				if (current_option == 1)
				{
					current_menu = 2;
					current_option = 1;
					previous_option = 1;
					printGameplayPresetScreen(difficulty, false);
				}
				if (current_option == 3)
				{
					current_menu = 1;
					current_option = 1;
					previous_option = 1;
					printSettingsMenu(current_option, previous_option, volume, light_mode, true, true); 
					setCursorPosition(14, 2 * current_option + 2);
					cout << ">>>>";
				}
				if (current_option == 4)
				{
					setCursorPosition(0, 16);
					run = false;
					return false;
				}
			}
			//settings menu
			else if (current_menu == 1)
			{
				if (current_option == 2)
				{
					light_mode = !light_mode;
					if (light_mode)
					{
						cout << "\x1b[30m";
						cout << "\x1b[47m";
					}
					else
					{
						cout << "\x1b[0m";
					}
					printSettingsMenu(current_option, previous_option, volume, light_mode, true, true);
				}
			}
			Sleep(200);
		}

		//return to previous menu
		if ((isPressing('R') && current_menu == 1) || (isPressing('R') && current_menu == 2))
		{
			current_menu = 0;
			current_option = 1;
			previous_option = 1;
			printMainMenu(0, 0, false);
		}

		//start game
		if (isPressing('F') && current_menu == 2)
		{
			switch (difficulty)
			{
			case 1:
				//easy
				board_x = 8;
				board_y = 6;
				break;
			case 2:
				//normal
				board_x = 10;
				board_y = 8;
				break;
			case 3:
				//hard
				board_x = 12;
				board_y = 10;
				break;
			}
			Sleep(200);
			return true;
		}
	}
}