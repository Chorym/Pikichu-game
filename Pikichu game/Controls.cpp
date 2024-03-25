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

void gameplayLoop(int board_x, int board_y)
{
	printGameplayFrame(board_x, board_y);
	int current_cells_on_board = board_x * board_y;

	int** game_board_array = generateGameBoard(board_x, board_y);
	drawGameBoard(game_board_array, board_x, board_y);

	bool run = true;
	int moving = false;

	bool key_pressed_E = false;
	bool key_pressed_Q = false;

	Point current_point = make_pair(0, 0);
	Point previous_point = make_pair(0, 0);

	//used to clear points value
	Point empty = make_pair(-1, -1);

	//selected_points array hold the 2 points that the player chose to connect
	Point point_1 = make_pair(-1, -1);
	Point point_2 = make_pair(-1, -1);
	Point selected_points[] = { point_1, point_2 };

	drawCurrentCell(game_board_array, current_point, previous_point, selected_points);

	//run = false;
	while (run)
	{
		//move horizontally
		if (isPressing('D') && !isPressing('W') && !isPressing('S'))
		{
			previous_point = current_point;
			current_point.first++;
			if (current_point.first > board_x - 1) current_point.first = 0;
			moving = true;
		}
		if (isPressing('A') && !isPressing('W'))
		{
			previous_point.first = current_point.first;
			previous_point.second = current_point.second;
			current_point.first--;
			if (current_point.first < 0) current_point.first = board_x - 1;
			moving = true;
		}


		//move vertically
		if (isPressing('W') && !isPressing('A'))
		{
			previous_point = current_point;
			current_point.second--;
			if (current_point.second < 0) current_point.second = board_y - 1;
			moving = true;
		}
		if (isPressing('S') && !isPressing('A'))
		{
			previous_point = current_point;
			current_point.second++;
			if (current_point.second > board_y - 1) current_point.second = 0;
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
			if (pathfinding2Cells(selected_points, game_board_array, board_x, board_y)) current_cells_on_board -= 2;
			drawGameBoard(game_board_array, board_x, board_y);
			drawCurrentCell(game_board_array, current_point, previous_point, selected_points);
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

void menuInteraction()
{
	bool run = true;

	int current_menu = 0; //0 is main menu, 1 is settings menu

	int current_option = 1;
	int previous_option = 1;

	int main_menu_option_amount = 4;
	int settings_menu_option_amount = 1;

	int volume = 10; //1 to 10, step = 1
	bool light_mode = false;

	int difficulty = 2; //1 is easy, 2 is normal, 3 is hard
	int time = 2; //same as dif
	int size = 2; //same as dif

	bool change_volume = false;
	bool change_lighting = false;

	while (run)
	{
		//Changing options in main menu or settings
		if (GetAsyncKeyState('W') && 0x8000)
		{
			previous_option = current_option;
			current_option--;
			if (current_option <= 0)
			{
				current_option = main_menu_option_amount;
			}
			if (current_menu == 0)
				printMainMenu(current_option, previous_option, true);
			else if (current_menu == 1)
				printSettingsMenu(current_option, previous_option, volume, light_mode, true);
			Sleep(200);
		}
		if (GetAsyncKeyState('S') && 0x8000)
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
				printSettingsMenu(current_option, previous_option, volume, light_mode, true); break;
			case 2:
				printGameplayPresetScreen(current_option, previous_option, difficulty, time, size, true); break;
			}
			Sleep(200);
		}

		//Changing settings in settings and game menu
		if (GetAsyncKeyState('A') && 0x8000 && current_menu == 1)
		{
			if (current_option == 1)
			{
				volume--;
				if (volume < 1) volume = 10;
				printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				PlaySound(L"C:\\Users\\PC\\source\\repos\\Pikichu game\\SFX\\break.wav", NULL, SND_FILENAME | SND_ASYNC);
				Sleep(200);
			}
			if (current_option == 2)
			{
				if (light_mode == true)
				{
					light_mode = false;
					cout << "\x1b[0m";
					printSettingsMenu(current_option, previous_option, volume, light_mode, false);
					printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				}
				else
				{
					light_mode = true;
					cout << "\x1b[30m";
					cout << "\x1b[47m";
					printSettingsMenu(current_option, previous_option, volume, light_mode, false);
					printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				}
				Sleep(200);
			}
		}
		if (GetAsyncKeyState('D') && 0x8000 && current_menu == 1)
		{
			if (current_option == 1)
			{
				volume++;
				if (volume > 10) volume = 1;
				printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				Sleep(200);
			}
			if (current_option == 2)
			{
				if (light_mode == true)
				{
					light_mode = false;
					cout << "\x1b[0m";
					printSettingsMenu(current_option, previous_option, volume, light_mode, false);
					printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				}
				else
				{
					light_mode = true;
					cout << "\x1b[30m";
					cout << "\x1b[47m";
					printSettingsMenu(current_option, previous_option, volume, light_mode, false);
					printSettingsMenu(current_option, previous_option, volume, light_mode, true);
				}
				Sleep(200);
			}
		}

		//confirm current option
		if (GetAsyncKeyState('E') && 0x8000)
		{
			//from main to settings
			if (current_menu == 0 && current_option == 3)
			{
				current_menu = 1;
				current_option = 1;
				previous_option = 1;
				printSettingsMenu(current_option, previous_option, volume, light_mode, false); //this to switch to the menu
				printSettingsMenu(current_option, previous_option, volume, light_mode, true); //this to change the settings correctly
				//move the select cursor back
				setCursorPosition(15, 2 * current_option + 3);
				cout << ">>>>";
			}
			//from settings to main
			if (current_menu == 1 && current_option == 4)
			{
				current_menu = 0;
				current_option = 1;
				previous_option = 1;
				printMainMenu(0, 0, false);
			}
			//quit game
			if (current_menu == 0 && current_option == 4)
			{
				setCursorPosition(0, 16);
				run = false;
				return;
			}
			Sleep(200);
		}
	}
}