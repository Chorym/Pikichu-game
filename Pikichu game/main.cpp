#include <iostream>

#include <random>
#include <algorithm>

#include <string>

#include <Windows.h>
#include <mmsystem.h>
#include <playsoundapi.h>
#pragma comment(lib, "Winmm.lib")

#include <utility>
#include <fstream>

#include <chrono>
#include <conio.h>

using std::make_pair;
using std::pair;
using std::string;
using std::cout;
using std::cin;

//struct and typedef
typedef pair<int, int> Point;

//declaration
void setCursorPosition(int x, int y);
void clear2DArray(int** array, int board_y);
int** generateGameBoard(int board_y, int board_x);
void drawGameBoard(int** game_board_array, int board_y, int board_x);
void drawCurrentCell(int** game_board_array, int current_position_x, int current_position_y, int previous_position_x, int previous_position_y, Point selected_points[2]);
void selectCell(int** game_board_array, int position_x, int position_y);
void deselecteCell(int** game_board_array, int position_x, int position_y);
bool pathfinding2Cells(Point selected_points[2], int** game_board_array, int board_x, int board_y);
void mainGameLoop(int board_y, int board_x);
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option);
void printMainMenu(int current_option, int previous_option, bool change_option);
void printGameplayPresetScreen(int current_option, int previous_option, int difficulty, int time, int size, bool change_option);
void menuInteraction();
//BOOL WINAPI ConsoleHandler(DWORD dwCtrlType);
//

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

void setCursorPosition(int x, int y)
{
	cout << "\x1b[" << y << ";" << x << "H";
}

//printing and updating the settings menu
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option)
{
	if (change_option)
	{
		setCursorPosition(15, 2 * current_option + 3);
		cout << ">>>>";

		setCursorPosition(15, 2 * previous_option + 3);
		cout << "    ";

		setCursorPosition(30, 5);
		for (int i = 0; i < volume; i++)
			cout << "\xDB";
		for (int i = 0; i < 10 - volume; i++)
			cout << " ";
		cout << "> ";
		if (volume != 10)
			cout << 10 * volume << "% ";
		else
			cout << "100%";

		setCursorPosition(21, 7);
		if (light_mode == true)
			cout << "Light mode: On ";
		else
			cout << "Light mode: Off";
		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                     Settings                                    |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |       >>>>  Volume: <\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB>                                                |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |             Light mode: Off                                                     |     |" << "\n"; //6 
	cout << "|     |                                                                                 |     |" << "\n"; //7
	cout << "|     |                                                                                 |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |                           Return to previous menu....                           |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     | Move Up: W / Move Down: S / Move Left: A / Move Right: D / Confirm: E           |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//printing and updating the main menu
void printMainMenu(int current_option, int previous_option, bool change_option)
{
	if (change_option)
	{
		setCursorPosition(40, 2 * current_option + 3);
		cout << ">>";
		setCursorPosition(40 + 15, 2 * current_option + 3);
		cout << "<<";

		setCursorPosition(40, 2 * previous_option + 3);
		cout << "  ";
		setCursorPosition(40 + 15, 2 * previous_option + 3);
		cout << "  ";
		setCursorPosition(40 + 17, 2 * current_option + 3);


		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                             Untitled Matching Game                              |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |                                >>    Start    <<                                |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |                                   Leaderboard                                   |     |" << "\n"; //6
	cout << "|     |                                                                                 |     |" << "\n"; //7 
	cout << "|     |                                     Setting                                     |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |                                    Quit game                                    |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     | Move Up: W / Move Down: S / Confirm: E                                          |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//printing and updating the menu containing everything before the game starts
void printGameplayPresetScreen(int current_option, int previous_option, int difficulty, int time, int size, bool change_option)
{
	//difficulty: easy, normal, hard, custom
	//custom will not be logged into leaderboards
	//if choose custom, user can move cursor down to size and timer to change it themselves
	if (change_option)
	{
		setCursorPosition(15, 2 * current_option + 3);
		cout << ">>>>";

		setCursorPosition(15, 2 * previous_option + 3);
		cout << "    ";

		setCursorPosition(32, 4);
		switch (difficulty)
		{
		case 1:
			cout << "Easy  ";
			setCursorPosition(32, 6);
			cout << "4x6";
			setCursorPosition(32, 8);
			cout << "7 minutes";
			break;
		case 2:
			cout << "Normal";
			setCursorPosition(32, 6);
			cout << "6x8";
			setCursorPosition(32, 8);
			cout << "5 minutes";
			break;
		case 3:
			cout << "Hard  ";
			setCursorPosition(32, 6);
			cout << "8x10";
			setCursorPosition(32, 8);
			cout << "3 minutes";
			break;
		}
		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                Pre-game settings                                |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |        >>>> Difficulty: Normal                                                  |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |             Size: 8x6                                                           |     |" << "\n"; //6
	cout << "|     |                                                                                 |     |" << "\n"; //7
	cout << "|     |             Time: 5 minutes                                                     |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |             Return to main menu...                                              |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     |                                                                                 |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//Controls of all the menus
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

bool isObstructed(Point point, int** game_board_array)
{
	if (game_board_array[point.second][point.first] == -1) return false;
	else return true;
}

bool isStraightLine(Point start, Point end, int** game_board_array)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	//if the cells are next to each other
	if ((abs(distance_x) == 1 && distance_y == 0) || (distance_x == 0 && abs(distance_y) == 1))
	{
		return true;
	}

	//horizontal line
	if (distance_x != 0 && distance_y == 0)
	{
		int direction_x = distance_x / abs(distance_x);
		while (start.first != end.first)
		{
			start.first += direction_x;
			if (isObstructed(start, game_board_array) && start.first != end.first)
			{
				return false;
			}
			if (start.first == end.first)
			{
				return true;
			}
		}
	}
	
	//vertical line
	if (distance_x == 0 && distance_y != 0)
	{
		int direction_y = distance_y / abs(distance_y);
		while (start.second != end.second)
		{
			start.second += direction_y;
			if (isObstructed(start, game_board_array) && start.second != end.second)
			{
				return false;
			}
			if (start.second == end.second)
			{
				return true;
			}
		}
	}

	return false;
}

bool isLshapeLine(Point start, Point end, int** game_board_array)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	Point middle = make_pair(start.first + distance_x, start.second);

	if (!isObstructed(middle, game_board_array))
	{
		if (isStraightLine(start, middle, game_board_array) && isStraightLine(middle, end, game_board_array))
		{
			return true;
		}
	}

	middle = make_pair(start.first, start.second + distance_y);

	if (!isObstructed(middle, game_board_array))
	{
		if (isStraightLine(start, middle, game_board_array) && isStraightLine(middle, end, game_board_array))
		{
			return true;
		}
	}

	return false;
}

bool isUShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int middle_path_x = 0;
	int middle_path_y = 0;

	Point middle_1 = make_pair(middle_path_x, start.second);
	Point middle_2 = make_pair(middle_path_x, end.second);

	for (int i = 0; i < board_x; i++)
	{
		if (distance_x > 0)
		{
			if (i >= start.first && i <= end.first) continue;
		}
		else
		{
			if (i <= start.first && i >= end.first) continue;
		}

		if (isStraightLine(middle_1, middle_2, game_board_array))
		{
			if (isStraightLine(start, middle_1, game_board_array) && isStraightLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		else
		{
			middle_1.first++;
			middle_2.first++;
		}
	}

	middle_1 = make_pair(start.first, middle_path_y);
	middle_2 = make_pair(end.first, middle_path_y);

	for (int i = 0; i < board_y; i++)
	{
		if (distance_y > 0)
		{
			if (i >= start.second && i <= end.second) continue;
		}
		else
		{
			if (i <= start.second && i >= end.second) continue;
		}

		if (isStraightLine(middle_1, middle_2, game_board_array))
		{
			if (isStraightLine(start, middle_1, game_board_array) && isStraightLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		else
		{
			middle_1.second++;
			middle_2.second++;
		}
	}
	return false;
}

//more work
bool isZShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int direction_x = distance_x / abs(distance_x);
	int direction_y = distance_y / abs(distance_y);

	int middle_path_x = 0;
	int middle_path_y = 0;

	Point middle_1 = make_pair(middle_path_x, start.second);
	Point middle_2 = make_pair(middle_path_x, end.second);

	for (int i = start.first; i < end.first; i += direction_x)
	{
		if (isStraightLine(middle_1, middle_2, game_board_array))
		{
			if (isStraightLine(start, middle_1, game_board_array) && isStraightLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		else
		{
			middle_1.first += direction_x;
			middle_2.first += direction_x;
		}
	}

	middle_1 = make_pair(start.first, middle_path_y);
	middle_2 = make_pair(end.first, middle_path_y);

	for (int i = start.second; i < end.second; i += direction_y)
	{
		if (isStraightLine(middle_1, middle_2, game_board_array))
		{
			if (isStraightLine(start, middle_1, game_board_array) && isStraightLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		else
		{
			middle_1.second += direction_y;
			middle_2.second += direction_y;
		}
	}
	return false;
}

void clear2DArray(int** array, int board_y)
{
	for (int i = 0; i < board_y; i++)
	{
		delete []array[i];
	}
	delete []array;
}

int** generateGameBoard(int board_y, int board_x)
{
	int** game_board_array_pointer = nullptr;
	if ((board_x * board_y) % 2 == 1) return game_board_array_pointer;
	
	game_board_array_pointer = new int* [board_y];
	for (int i = 0; i < board_y; i++)
	{
		game_board_array_pointer[i] = new int[board_x];
	}

	//add value
	int* cells_value = new int[board_x * board_y];
	for (int i = 0; i < board_x * board_y; i += 2)
	{
		int random_int = rand() % 10;
		cells_value[i] = random_int;
		cells_value[i + 1] = random_int;
	}

	std::shuffle(cells_value, cells_value + (board_x * board_y), std::mt19937(std::random_device()()));

	int k = 0;
	for (int i = 0; i < board_y; i++)
	{
		for (int j = 0; j < board_x; j++)
		{
			game_board_array_pointer[i][j] = cells_value[k++];
		}
	}

	delete []cells_value;
	return game_board_array_pointer;
}

void drawGameBoard(int** game_board_array, int board_y, int board_x)
{
	for (int i = 0; i < board_y; i++)
	{
		for (int j = 0; j < board_x; j++)
		{
			setCursorPosition(8 * j + 1, 5 * i + 1);
			cout << "+-----+";
			setCursorPosition(8 * j + 1, 5 * i + 2);
			cout << "|     |";
			setCursorPosition(8 * j + 1, 5 * i + 3);
			if(game_board_array[i][j] != -1)
				cout << "|  " << game_board_array[i][j] << "  |";
			else
				cout << "|     |";
			setCursorPosition(8 * j + 1, 5 * i + 4);
			cout << "|     |";
			setCursorPosition(8 * j + 1, 5 * i + 5);
			cout << "+-----+";
		}
	}
}

//color the current cell that the player is on
void drawCurrentCell(int** game_board_array, int current_position_x, int current_position_y, int previous_position_x, int previous_position_y, Point selected_points[2])
{
	if ((previous_position_x != (selected_points[0].first) || 
		previous_position_y != selected_points[0].second) &&
		(previous_position_x != selected_points[1].first ||
		previous_position_y != selected_points[1].second))
	{
		setCursorPosition(8 * previous_position_x + 1, 5 * previous_position_y + 1);
		cout << "+-----+ ";
		setCursorPosition(8 * previous_position_x + 1, 5 * previous_position_y + 2);
		cout << "|     |";
		setCursorPosition(8 * previous_position_x + 1, 5 * previous_position_y + 3);
		if (game_board_array[previous_position_y][previous_position_x] != -1)
			cout << "|  " << game_board_array[previous_position_y][previous_position_x] << "  |";
		else
			cout << "|     |";
		setCursorPosition(8 * previous_position_x + 1, 5 * previous_position_y + 4);
		cout << "|     |";
		setCursorPosition(8 * previous_position_x + 1, 5 * previous_position_y + 5);
		cout << "+-----+";
	}
	
	setCursorPosition(8 * current_position_x + 1, 5 * current_position_y + 1);
	cout << "+-----+ ";
	setCursorPosition(8 * current_position_x + 1, 5 * current_position_y + 2);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * current_position_x + 1, 5 * current_position_y + 3);
	if (game_board_array[current_position_y][current_position_x] != -1)
		cout << "|\xDB\xDB" << game_board_array[current_position_y][current_position_x] << "\xDB\xDB|";
	else
		cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * current_position_x + 1, 5 * current_position_y + 4);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * current_position_x + 1, 5 * current_position_y + 5);
	cout << "+-----+";
}

//select any cell wanted with cords
void selectCell(int** game_board_array, int position_x, int position_y)
{
	setCursorPosition(8 * position_x + 1, 5 * position_y + 1);
	cout << "+-----+ ";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 2);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 3);
	if (game_board_array[position_y][position_x] != -1)
		cout << "|\xDB\xDB" << game_board_array[position_y][position_x] << "\xDB\xDB|";
	else
		cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 4);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 5);
	cout << "+-----+";
}

//deselect any cell wanted with cords
void deselecteCell(int** game_board_array, int position_x, int position_y)
{
	setCursorPosition(8 * position_x + 1, 5 * position_y + 1);
	cout << "+-----+ ";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 2);
	cout << "|     |";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 3);
	if (game_board_array[position_y][position_x] != -1)
		cout << "|  " << game_board_array[position_y][position_x] << "  |";
	else
		cout << "|     |";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 4);
	cout << "|     |";
	setCursorPosition(8 * position_x + 1, 5 * position_y + 5);
	cout << "+-----+";
}

//find if the 2 selected cells are connectable
bool pathfinding2Cells(Point selected_points[2], int** game_board_array, int board_x, int board_y)
{
	Point start = selected_points[0];
	Point end = selected_points[1];

	bool found_path = false;

	if (game_board_array[start.second][start.first] != game_board_array[end.second][end.first] || start == end)
	{
		found_path = false;
	}
	else if (isStraightLine(start, end, game_board_array))
	{
		found_path = true;
	}
	else if (isLshapeLine(start, end, game_board_array))
	{
		found_path = true;
	}
	else if (isUShapeLine(start, end, game_board_array, board_x, board_y))
	{
		found_path = true;
	}
	else if (isZShapeLine(start, end, game_board_array, board_x, board_y))
	{
		found_path = true;
	}

	if (found_path)
	{
		game_board_array[start.second][start.first] = -1;
		game_board_array[end.second][end.first] = -1;
		selected_points[0].first = -1;
		selected_points[0].second = -1;
		selected_points[1].first = -1;
		selected_points[1].second = -1;
		return true;
	}
	else
	{
		selected_points[0].first = -1;
		selected_points[0].second = -1;
		selected_points[1].first = -1;
		selected_points[1].second = -1;
		return false;
	}
}

void mainGameLoop(int board_y, int board_x)
{
	int current_cells_on_board = board_x * board_y;

	int** game_board_array = generateGameBoard(board_y, board_x);
	drawGameBoard(game_board_array, board_y, board_x);

	bool run = true;
	int moving = false;

	bool key_pressed_E = false;
	bool key_pressed_Q = false;

	int current_position_x = 0;
	int current_position_y = 0;
	int previous_position_x = 0;
	int previous_position_y = 0;

	//selected_points array hold the 2 points that the player chose to connect
	Point point_1 = make_pair(-1, -1);
	Point point_2 = make_pair(-1, -1);
	Point selected_points[] = {point_1, point_2};

	drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_points);

	while (run)
	{
		//move horizontally
		if (GetAsyncKeyState('D') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_x++;
			if (current_position_x > board_x - 1) current_position_x = 0;
			moving = true;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_x--;
			if (current_position_x < 0) current_position_x = board_x - 1;
			moving = true;
		}


		//move vertically
		if (GetAsyncKeyState('W') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y--;
			if (current_position_y < 0) current_position_y = board_y - 1;
			moving = true;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y++;
			if (current_position_y > board_y - 1) current_position_y = 0;
			moving = true;
		}


		//movement
		if (moving)
		{
			drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_points);
			Sleep(200);
			moving = false;
		}


		//selecting and drawing cells
		if (GetAsyncKeyState('E') & 0x8000 && !key_pressed_E)
		{
			if (game_board_array[current_position_y][current_position_x] != -1)
			{
				if (selected_points[0].first == -1 && current_position_x != -1)
				{
					if (current_position_x != selected_points[0].first && current_position_y != selected_points[0].second)
					{
						selected_points[0].first = current_position_x;
						selected_points[0].second = current_position_y;
						selectCell(game_board_array, current_position_x, current_position_y);
					}
				}
				else if (selected_points[1].first == -1 && current_position_x != -1)
				{
					if (current_position_x != selected_points[1].first && current_position_y != selected_points[1].second)
					{
						selected_points[1].first = current_position_x;
						selected_points[1].second = current_position_y;
						selectCell(game_board_array, current_position_x, current_position_y);
					}
				}
			}
			key_pressed_E = true;
		}
		if (!(GetAsyncKeyState('E') & 0x8000) && key_pressed_E) key_pressed_E = false;


		//canceling cells
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			if (current_position_x == selected_points[0].first && current_position_y == selected_points[0].second && current_position_x != -1)
			{
				selected_points[0].first = -1;
				selected_points[0].second = -1;
				deselecteCell(game_board_array, current_position_x, current_position_y);
			}
			else if (current_position_x == selected_points[1].first && current_position_y == selected_points[1].second && current_position_x != -1)
			{
				selected_points[1].first = -1;
				selected_points[1].second = -1;
				deselecteCell(game_board_array, current_position_x, current_position_y);
			}
			key_pressed_Q = true;
		}
		if (!(GetAsyncKeyState('Q') & 0x8000) && key_pressed_Q) key_pressed_Q = false;

		//if 2 cells are selected
		if (selected_points[0].first != -1 && selected_points[1].first != -1)
		{
			if (pathfinding2Cells(selected_points, game_board_array, board_x, board_y)) current_cells_on_board -= 2;
			setCursorPosition(0, 0);
			drawGameBoard(game_board_array, board_y, board_x);
			drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_points);
		}

		if (current_cells_on_board == 0) //u won yay
		{
			setCursorPosition(0, 50);
			cout << "u won yay\n";
			run = false;
		}

		//exit game
		if (GetAsyncKeyState('F') & 0x8000)
		{
			setCursorPosition(0, 50);
			run = false;
		}


	}

	clear2DArray(game_board_array, board_y);
}

int main()
{
	/*
	debug
	std::fstream fin;
	fin.open("debug.txt");
	*/

	HWND console = GetConsoleWindow();
	MoveWindow(console, 225, 150, 1080, 720, TRUE);

	//uncomment this to load the menu
	/*
	printMainMenu(0, 0, false);
	menuInteraction();
	*/

	//uncomment this to load the gameplay
	
	srand(time(0));
	int board_y = 6;
	int board_x = 8;
	if (board_y * board_x % 2 != 0)
	{
		cout << "wrong dimensions" << "\n";
		return 0;
	}

	mainGameLoop(board_y, board_x);
	
	return 0;
}