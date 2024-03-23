#include <iostream>

#include <random>
#include <algorithm>

#include <string>
#include <Windows.h>

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
void clear2DArray(int** array, int length);
int** generateGameBoard(int length, int width);
void drawGameBoard(int** game_board_array, int length, int width);
void drawCurrentCell(int** game_board_array, int current_position_x, int current_position_y, int previous_position_x, int previous_position_y, Point selected_points[2]);
void selectCell(int** game_board_array, int position_x, int position_y);
void deselecteCell(int** game_board_array, int position_x, int position_y);
void pathfinding2Cells(Point selected_points[2], int** game_board_array);
void mainGameLoop(int board_length, int board_width);
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option);
void printMainMenu(int current_option, int previous_option, bool change_option);
void printGameplayPresetScreen(int current_option, int previous_option, int difficulty, int time, int size, bool change_option);
void menuInteraction();
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
				PlaySound(L"break.wav", GetModuleHandle(NULL), SND_SYNC);
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

bool isObstructed(int** game_board_array, Point point)
{
	if (game_board_array[point.second][point.first] == -1) return false;
	else return true;
}

bool isStraightLine(Point selected_points[2], int** game_board_array)
{
	int start_x = selected_points[0].first;
	int start_y = selected_points[0].second;
	int end_x = selected_points[1].first;
	int end_y = selected_points[1].second;

	int distance_x = end_x - start_x;
	int distance_y = end_y - start_y;

	//if the cells are next to each other
	if ((abs(distance_x) == 1 && distance_y == 0) || (distance_x == 0 && abs(distance_y) == 1))
	{
		return true;
	}

	//horizontal line
	if (distance_x != 0 && distance_y == 0)
	{
		int direction_x = distance_x / abs(distance_x);
		while (start_x != end_x)
		{
			start_x += direction_x;
			if (game_board_array[start_y][start_x] != -1 && start_x != end_x)
			{
				return false;
			}
			if (start_x == end_x)
			{
				return true;
			}
		}
	}
	
	//vertical line
	if (distance_x == 0 && distance_y != 0)
	{
		int direction_y = distance_y / abs(distance_y);
		while (start_y != end_y)
		{
			start_y += direction_y;
			if (game_board_array[start_y][start_x] != -1 && start_y != end_y)
			{
				return false;
			}
			if (start_y == end_y)
			{
				return true;
			}
		}
	}

	return false;
}

bool isLshapeLine(Point selected_points[2], int** game_board_array)
{
	Point start = selected_points[0];			
	Point end = selected_points[1];

	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	Point middle = make_pair(start.first + distance_x, start.second);

	Point path_1[2] = {start, middle};
	Point path_2[2] = {middle, end};

	if (!isObstructed(game_board_array, middle))
	{
		if (isStraightLine(path_1, game_board_array) && isStraightLine(path_2, game_board_array))
		{
			return true;
		}
	}

	middle = make_pair(start.first, start.second + distance_y);

	path_1[0] = start;
	path_1[1] = middle;
	path_2[0] = middle;
	path_2[1] = end;

	if (!isObstructed(game_board_array, middle))
	{
		if (isStraightLine(path_1, game_board_array) && isStraightLine(path_2, game_board_array))
		{
			return true;
		}
	}

	return false;
}

//more work
bool isUShapeLine(Point selected_points[2], int** game_board_array, int board_length, int board_width)
{

	Point start = selected_points[0];
	Point end = selected_points[1];

	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int middle_path_x = 0;
	int middle_path_y = 0;
	
	


	return false;
}

//more work
bool isZShapeLine(Point selected_points[2], int** game_board_array)
{
	return false;
}

void clear2DArray(int** array, int length)
{
	for (int i = 0; i < length; i++)
	{
		delete []array[i];
	}
	delete []array;
}

int** generateGameBoard(int length, int width)
{
	int** game_board_array_pointer = nullptr;
	if ((width * length) % 2 == 1) return game_board_array_pointer;
	
	game_board_array_pointer = new int* [length];
	for (int i = 0; i < length; i++)
	{
		game_board_array_pointer[i] = new int[width];
	}

	//add value
	int* cells_value = new int[width * length];
	for (int i = 0; i < width * length; i += 2)
	{
		int random_int = rand() % 10;
		cells_value[i] = random_int;
		cells_value[i + 1] = random_int;
	}

	std::shuffle(cells_value, cells_value + (width * length), std::mt19937(std::random_device()()));

	int k = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			game_board_array_pointer[i][j] = cells_value[k++];
		}
	}

	delete []cells_value;
	return game_board_array_pointer;
}

void drawGameBoard(int** game_board_array, int length, int width)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
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
void pathfinding2Cells(Point selected_points[2], int** game_board_array)
{
	if (game_board_array[selected_points[0].second][selected_points[0].first] != game_board_array[selected_points[1].second][selected_points[1].first])
	{
		selected_points[0].first = -1;
		selected_points[0].second = -1;
		selected_points[1].first = -1;
		selected_points[1].second = -1;
		return;
	}

	if (isStraightLine(selected_points, game_board_array))
	{
		game_board_array[selected_points[0].second][selected_points[0].first] = -1;
		game_board_array[selected_points[1].second][selected_points[1].first] = -1;
		selected_points[0].first = -1;
		selected_points[0].second = -1;
		selected_points[1].first = -1;
		selected_points[1].second = -1;
		return;
	}

	if (isLshapeLine(selected_points, game_board_array))
	{
		game_board_array[selected_points[0].second][selected_points[0].first] = -1;
		game_board_array[selected_points[1].second][selected_points[1].first] = -1;
		selected_points[0].first = -1;
		selected_points[0].second = -1;
		selected_points[1].first = -1;
		selected_points[1].second = -1;
		return;
	}

	selected_points[0].first = -1;
	selected_points[0].second = -1;
	selected_points[1].first = -1;
	selected_points[1].second = -1;
}

void mainGameLoop(int board_length, int board_width)
{
	int** game_board_array = generateGameBoard(board_length, board_width);
	drawGameBoard(game_board_array, board_length, board_width);

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
			if (current_position_x > board_width - 1) current_position_x = 0;
			moving = true;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_x--;
			if (current_position_x < 0) current_position_x = board_width - 1;
			moving = true;
		}


		//move vertically
		if (GetAsyncKeyState('W') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y--;
			if (current_position_y < 0) current_position_y = board_length - 1;
			moving = true;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y++;
			if (current_position_y > board_length - 1) current_position_y = 0;
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
			pathfinding2Cells(selected_points, game_board_array);
			setCursorPosition(0, 0);
			drawGameBoard(game_board_array, board_length, board_width);
			drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_points);
		}


		//exit game
		if (GetAsyncKeyState('F') & 0x8000)
		{
			setCursorPosition(0, 50);
			run = false;
		}
	}

	clear2DArray(game_board_array, board_length);
}

int main()
{
	/*
	debug
	std::fstream fin;
	fin.open("debug.txt");
	*/

	HWND console = GetConsoleWindow();
	MoveWindow(console, 225, 150, 800, 600, TRUE);

	//uncomment this to load the menu
	/*
	printMainMenu(0, 0, false);
	menuInteraction();
	*/

	//uncomment this to load the gameplay
	/*
	srand(time(0));
	int length = 6;
	int width = 8;
	if (length * width % 2 != 0)
	{
		cout << "wrong dimensions" << "\n";
		return 0;
	}

	mainGameLoop(length, width);
	*/
	return 0;
}