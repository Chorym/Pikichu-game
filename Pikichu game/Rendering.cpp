#include <iostream>
#include <Windows.h>
#include <random>
#include <utility>
#include <math.h>
#include "Game_logic.h"
#include "Player_data_manip.h"

using std::cout;

typedef std::pair<int, int> Point;

//needs referencing
void resizeConsole(int width, int height, short bufferWidth, short bufferHeight)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT rect;
	GetWindowRect(consoleWindow, &rect);

	// Calculate new window size
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	// Resize the console window
	MoveWindow(consoleWindow, rect.left, rect.top, width, height, TRUE);

	// Resize the console screen buffer
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufferSize = { bufferWidth, bufferHeight };
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
}

//needs refferencing 
void setCursorPosition(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//printing and updating the settings menu
void printSettingsMenu(int current_option, int previous_option, bool light_mode, bool change_option, bool render, bool soundEnable)
{
	if (change_option)
	{
		setCursorPosition(14, 2 * current_option + 2);
		cout << ">>>>";

		setCursorPosition(14, 2 * previous_option + 2);
		cout << "    ";

		setCursorPosition(20, 4);
		if (soundEnable == true)
			cout << "Volume: On ";
		else
			cout << "Volume: Off";

		setCursorPosition(20, 6);
		if (light_mode == true)
			cout << "Light mode: On ";
		else
			cout << "Light mode: Off";
	}

	if (render)
	{
		system("cls");
		cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //0
		cout << "|     |                                            Settings                                           |     |" << "\n"; //1
		cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //2
		cout << "|     |                                                               |           Controls:           |     |" << "\n"; //3
		cout << "|     |             Volume: ON                                        | Up:   W                       |     |" << "\n"; //4
		cout << "|     |                                                               | Down: S                       |     |" << "\n"; //5
		cout << "|     |             Light mode: Off                                   |                               |     |" << "\n"; //6 
		cout << "|     |                                                               | Increase: D                   |     |" << "\n"; //7
		cout << "|     |                                                               | Decrease: A                   |     |" << "\n"; //8
		cout << "|     |                                                               |                               |     |" << "\n"; //9
		cout << "|     |                                                               | Choose: E                     |     |" << "\n"; //10
		cout << "|     |                                                               | Return: R                     |     |" << "\n"; //11
		cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //12
		cout << "|     |                                                                                               |     |" << "\n"; //13
		cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //14

		setCursorPosition(14, 2 * current_option + 2);
		cout << ">>>>";

		setCursorPosition(14, 2 * previous_option + 2);
		cout << "    ";

		setCursorPosition(20, 4);
		if (soundEnable == true)
			cout << "Volume: On ";
		else
			cout << "Volume: Off";

		setCursorPosition(20, 6);
		if (light_mode == true)
			cout << "Light mode: On ";
		else
			cout << "Light mode: Off";
	}
}

//printing and updating the main menu
void printMainMenu(int current_option, int previous_option, bool change_option, PlayerData current_player)
{
	if (change_option)
	{
		setCursorPosition(30, 2 * current_option + 2);
		cout << ">>";
		setCursorPosition(30 + 15, 2 * current_option + 2);
		cout << "<<";

		setCursorPosition(30, 2 * previous_option + 2);
		cout << "  ";
		setCursorPosition(30 + 15, 2 * previous_option + 2);
		cout << "  ";
		setCursorPosition(30 + 17, 2 * current_option + 2);


		return;
	}

	system("cls");
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                    Untitled Matching Game                                     |     |" << "\n"; //1
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                               |           Controls:           |     |" << "\n"; //3
	cout << "|     |                       >>    Start    <<                       |                               |     |" << "\n"; //4
	cout << "|     |                                                               | Up:      W                    |     |" << "\n"; //5
	cout << "|     |                           Load game                           | Down:    S                    |     |" << "\n"; //6
	cout << "|     |                                                               | Confirm: E                    |     |" << "\n"; //7 
	cout << "|     |                          Leaderboard                          |                               |     |" << "\n"; //8
	cout << "|     |                                                               |                               |     |" << "\n"; //9
	cout << "|     |                            Setting                            |                               |     |" << "\n"; //10
	cout << "|     |                                                               | Quit game: ESC                |     |" << "\n"; //11
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     | Player name:                                                                                  |     |" << "\n"; //13
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //14
	setCursorPosition(22, 13); cout << current_player.name;
	setCursorPosition(0, 0);

}

//printing and updating the menu containing everything before the game starts
void printGameplayPresetScreen(int difficulty, bool change_option)
{
	//difficulty: easy, normal, hard, custom
	//custom will not be logged into leaderboards
	//if choose custom, user can move cursor down to size and timer to change it themselves
	if (change_option)
	{
		setCursorPosition(32, 4);
		switch (difficulty)
		{
		case 1:
			cout << "Easy  ";
			setCursorPosition(26, 7);
			cout << "4x6";
			setCursorPosition(26, 8);
			cout << "7 minutes";
			break;
		case 2:
			cout << "Normal";
			setCursorPosition(26, 7);
			cout << "6x8";
			setCursorPosition(26, 8);
			cout << "5 minutes";
			break;
		case 3:
			cout << "Hard  ";
			setCursorPosition(26, 7);
			cout << "8x10";
			setCursorPosition(26, 8);
			cout << "3 minutes";
			break;
		}
		return;
	}

	system("cls");
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                       Gameplay settings                                       |     |" << "\n"; //1
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                               |           Controls:           |     |" << "\n"; //3
	cout << "|     |        >>>> Difficulty: Normal                                |                               |     |" << "\n"; //4
	cout << "|     |                                                               |                               |     |" << "\n"; //5
	cout << "|     |                                                               |                               |     |" << "\n"; //6
	cout << "|     |             Size: 8x6                                         | Increase: D                   |     |" << "\n"; //7
	cout << "|     |             Time: 5 minutes                                   | Decrease: A                   |     |" << "\n"; //8
	cout << "|     |                                                               |                               |     |" << "\n"; //9
	cout << "|     |                                                               |                               |     |" << "\n"; //10
	cout << "|     |                                                               | Return: R                     |     |" << "\n"; //11
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     |                                    !!! Press F to Start !!!                                   |     |" << "\n"; //13
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//gameplay screen decor
void printGameplayFrame(int board_x, int board_y)
{
	system("cls");

	//frame around the game board
	cout << "[]--";
	for (int i = 0; i < board_x * 8; i++) cout << "-";
	cout << "[]";
	for (int i = 0; i < board_x * 5 + 7; i++) cout << "-";
	cout << "[]" << "\n";

	cout << "| []";
	for (int i = 0; i < board_x * 8 - 3; i++) cout << "-";
	cout << "[] | []";
	for (int i = 0; i < board_x * 5 + 3; i++) cout << "-";
	cout << "[] |" << "\n";

	for (int i = 0; i < board_y * 5; i++)
	{
		cout << "| |"; 
		for (int j = 0; j < board_x * 8 - 1; j++) cout << " ";
		cout << "| | |";
		for (int j = 0; j < board_x * 5 + 5; j++) cout << " ";
		cout << "| |" << "\n";
	}

	cout << "| []";
	for (int i = 0; i < board_x * 8 - 3; i++) cout << "-";
	cout << "[] | []";
	for (int i = 0; i < board_x * 5 + 3; i++) cout << "-";
	cout << "[] |" << "\n";

	cout << "[]--";
	for (int i = 0; i < board_x * 8; i++) cout << "-";
	cout << "[]";
	for (int i = 0; i < board_x * 5 + 7; i++) cout << "-";
	cout << "[]" << "\n";
	
	//rendering the text on the right of the board
	setCursorPosition(board_x * 11, 4);
	cout << "Controls:";
	setCursorPosition(board_x * 11 - 7, 6);
	cout << "Up:    W   |   Select:   E";
	setCursorPosition(board_x * 11 - 7, 7);
	cout << "Left:  A   |   Deselect: Q";
	setCursorPosition(board_x * 11 - 7, 8);
	cout << "Down:  S   |   Help: H (non-functional)";
	setCursorPosition(board_x * 11 - 7, 9);
	cout << "Right: D   |   End game: F";

	setCursorPosition(board_x * 11, 11);
	cout << "Time: ";

	setCursorPosition(board_x * 8 + 6, 14);
	cout << "[]";
	for (int i = 0; i < board_x * 5 + 3; i++) cout << "-";
	cout << "[]" << "\n";
}

void printLeaderboardScreen(PlayerData player_data[], bool change_option)
{
	system("cls");
}

//first screen of everything
void printLoginScreen(PlayerData player_data[], PlayerData& current_player)
{
	system("cls");
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                    Untitled Matching Game                                     |     |" << "\n"; //1
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                               |             Login             |     |" << "\n"; //3
	cout << "|     |                       >>    Start    <<                       |                               |     |" << "\n"; //4
	cout << "|     |                                                               | Name:                         |     |" << "\n"; //5
	cout << "|     |                           Load game                           |                               |     |" << "\n"; //6
	cout << "|     |                                                               |                               |     |" << "\n"; //7 
	cout << "|     |                          Leaderboard                          |                               |     |" << "\n"; //8
	cout << "|     |                                                               |                               |     |" << "\n"; //9
	cout << "|     |                            Setting                            |                               |     |" << "\n"; //10
	cout << "|     |                                                               |                               |     |" << "\n"; //11
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     |                                                                                               |     |" << "\n"; //13
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //14


	setCursorPosition(78, 5);
	string name;
	std::getline(std::cin, name);

	int i = 0;
	while (player_data[i].name != name)
	{
		//if new name, assign a new spot for that name
		if (player_data[i].name == "" && i < 30)
		{
			player_data[i].name = name;
			current_player.name = name;
			return;
		} 

		//if out of space, just overwrite the first slot
		if (i == 30)
		{
			i = 0;
			player_data[i].name = name;
			current_player.name = name;
			return;
		}

		i++;
	}

	//otherwise, load player data
	loadPlayerData(player_data, current_player, name);
}

//
//gameplay related rendering
//

//draw a dotted line connecting 2 cells on the board
/*
void drawConnection(Point start, Point end)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int direction;

	if (distance_x != 0)
	{
		direction = distance_x / abs(distance_x);
		if (direction > 0)
		{
			setCursorPosition(8 * start.first + 6, 5 * start.second + 4);
			cout << "O";
			for (int i = 0; i < abs(distance_x * 8 - 1); i++) cout << "-";
			cout << "O";
		}
		else
		{
			setCursorPosition(8 * end.first + 6, 5 * end.second + 4);
			cout << "O";
			for (int i = 0; i < abs(distance_x * 8 + 1); i++) cout << "-";
			cout << "O";
		}
	}
	else
	{
		direction = distance_y / abs(distance_y);
		if (direction > 0)
		{
			setCursorPosition(8 * start.first + 6, 5 * start.second + 4);
			cout << "O";
			for (int i = 0; i < abs(5 * distance_y - 1); i++)
			{
				setCursorPosition(8 * start.first + 6, 5 * start.second + 5 + i);
				cout << "|";
			}
			setCursorPosition(8 * end.first + 6, 5 * end.second + 4);
			cout << "O";
		}
		else
		{
			setCursorPosition(8 * end.first + 6, 5 * end.second + 4);
			cout << "O";
			for (int i = 0; i < abs(5 * distance_y + 9); i++)
			{
				setCursorPosition(8 * end.first + 6, 5 * end.second + 5 + i);
				cout << "|";
			}
			setCursorPosition(8 * start.first + 6, 5 * start.second + 4);
			cout << "O";
		}
	}
}
*/

//improved code using chat gpt, needs reference
void drawConnection(Point points[4])
{
	int number_of_points = 4;
	Point empty = std::make_pair(-1, -1);

	for (int i = 0; i < 4; i++)
	{
		if (points[i] == empty) number_of_points--;
	}

	for (int i = 0; i < number_of_points - 1; i++)
	{
		Point start = points[i];
		Point end = points[i + 1];
		
		int distance_x = end.first - start.first;
		int distance_y = end.second - start.second;

		int direction_x = (distance_x != 0) ? distance_x / abs(distance_x) : 0;
		int direction_y = (distance_y != 0) ? distance_y / abs(distance_y) : 0;

		int start_x = 8 * start.first + 6;
		int start_y = 5 * start.second + 4;

		int end_x = 8 * end.first + 6;
		int end_y = 5 * end.second + 4;

		int time_millseconds = 250;

		if (distance_x != 0)
		{
			setCursorPosition((direction_x > 0) ? start_x : end_x, start_y);
			cout << "O";
			for (int i = 0; i < abs(distance_x) * 8 - 1; i++) cout << "-";
			cout << "O";
		}
		else
		{
			setCursorPosition(start_x, (direction_y > 0) ? start_y : end_y);
			cout << "O";
			for (int i = 0; i < abs(distance_y) * 5 - 1; i++)
			{
				setCursorPosition(start_x, (direction_y > 0) ? start_y + 1 + i : end_y + 1 + i);
				cout << "|";
			}
			setCursorPosition(end_x, (direction_y > 0) ? end_y : start_y);
			cout << "O";
		}
	}
	
	async_sleep_milliseconds(250);

	for (int i = 0; i < number_of_points - 1; i++)
	{
		Point start = points[i];
		Point end = points[i + 1];

		int distance_x = end.first - start.first;
		int distance_y = end.second - start.second;

		int direction_x = (distance_x != 0) ? distance_x / abs(distance_x) : 0;
		int direction_y = (distance_y != 0) ? distance_y / abs(distance_y) : 0;

		int start_x = 8 * start.first + 6;
		int start_y = 5 * start.second + 4;

		int end_x = 8 * end.first + 6;
		int end_y = 5 * end.second + 4;

		int time_millseconds = 250;

		if (distance_x != 0)
		{
			setCursorPosition((direction_x > 0) ? start_x : end_x, start_y);
			cout << " ";
			for (int i = 0; i < abs(distance_x) * 8 - 1; i++) cout << " ";
			cout << " ";
		}
		else
		{
			setCursorPosition(start_x, (direction_y > 0) ? start_y : end_y);
			cout << " ";
			for (int i = 0; i < abs(distance_y) * 5 - 1; i++)
			{
				setCursorPosition(start_x, (direction_y > 0) ? start_y + 1 + i : end_y + 1 + i);
				cout << " ";
			}
			setCursorPosition(end_x, (direction_y > 0) ? end_y : start_y);
			cout << " ";
		}
	}
}

void clear2DArray(int** &array, int board_x)
{
	if (array == nullptr) return;

	for (int i = 0; i < board_x; i++)
	{
		delete[]array[i];
	}
	delete[]array;

	array = nullptr;
}

int** generateGameBoard(int board_x, int board_y, int** &game_board_array_pointer, bool load_new_board)
{
	//if new game, clear old game before starting to prevent leaks
	if (game_board_array_pointer != nullptr && load_new_board) 
		clear2DArray(game_board_array_pointer, board_x);
	//when there is an old board state and dont want to reset
	else if (game_board_array_pointer != nullptr && !load_new_board) 
		return game_board_array_pointer;

	game_board_array_pointer = nullptr;
	if ((board_x * board_y) % 2 == 1) return game_board_array_pointer;

	game_board_array_pointer = new int* [board_x];
	for (int i = 0; i < board_x; i++)
	{
		game_board_array_pointer[i] = new int[board_y];
	}

	//create value
	int cells_amount = (board_x - 2) * (board_y - 2);
	int* cells_value = new int[cells_amount];
	for (int i = 0; i < cells_amount; i += 2)
	{
		int random_int = rand() % 10;
		cells_value[i] = random_int;
		cells_value[i + 1] = random_int;
	}
	
	//shuffle value
	std::shuffle(cells_value, cells_value + (cells_amount), std::mt19937(std::random_device()()));

	//add value
	int k = 0;
	for (int i = 0; i < board_y; i++)
	{
		for (int j = 0; j < board_x; j++)
		{
			if (i == 0 || j == 0 || i == board_y - 1 || j == board_x - 1) game_board_array_pointer[j][i] = -1;
			else game_board_array_pointer[j][i] = cells_value[k++];
		}
	}

	delete[]cells_value;
	return game_board_array_pointer;
}

void drawGameBoard(int** game_board_array, int board_x, int board_y)
{
	for (int i = 0; i < board_y; i++)
	{
		for (int j = 0; j < board_x; j++)
		{
			if (game_board_array[j][i] == -1)
			{
				for (int k = 0; k < 5; k++)
				{
					setCursorPosition(8 * j + 3, 5 * i + 2 + k);
					cout << "       ";
				}
			}
			else
			{
				setCursorPosition(8 * j + 3, 5 * i + 2);
				cout << "+-----+";
				setCursorPosition(8 * j + 3, 5 * i + 3);
				cout << "|     |";
				setCursorPosition(8 * j + 3, 5 * i + 4);
				cout << "|  " << game_board_array[j][i] << "  |";
				setCursorPosition(8 * j + 3, 5 * i + 5);
				cout << "|     |";
				setCursorPosition(8 * j + 3, 5 * i + 6);
				cout << "+-----+";
			}
		}
	}
}

//color the current cell that the player is on
void drawCurrentCell(int** game_board_array, Point current, Point previous, Point selected_points[2])
{
	Point point_1 = selected_points[0];
	Point point_2 = selected_points[1];

	if (game_board_array[previous.first][previous.second] == -1)
	{
		for (int i = 0; i < 5; i++)
		{
			setCursorPosition(8 * previous.first + 3, 5 * previous.second + 2 + i);
			cout << "       ";
		}
	}
	else if (previous != point_1 && previous != point_2)
	{
		setCursorPosition(8 * previous.first + 3, 5 * previous.second + 2);
		cout << "+-----+ ";
		setCursorPosition(8 * previous.first + 3, 5 * previous.second + 3);
		cout << "|     |";
		setCursorPosition(8 * previous.first + 3, 5 * previous.second + 4);
		cout << "|  " << game_board_array[previous.first][previous.second] << "  |";
		setCursorPosition(8 * previous.first + 3, 5 * previous.second + 5);
		cout << "|     |";
		setCursorPosition(8 * previous.first + 3, 5 * previous.second + 6);
		cout << "+-----+";
	}

	if (game_board_array[current.first][current.second] == -1)
	{
		for (int i = 0; i < 3; i++)
		{
			setCursorPosition(8 * current.first + 3, 5 * current.second + 3 + i);
			cout << " \xDB\xDB\xDB\xDB\xDB ";
			setCursorPosition(0, 0);
		}
	}
	else
	{
		setCursorPosition(8 * current.first + 3, 5 * current.second + 2);
		cout << "+-----+ ";
		setCursorPosition(8 * current.first + 3, 5 * current.second + 3);
		cout << "|\xDB\xDB\xDB\xDB\xDB|";
		setCursorPosition(8 * current.first + 3, 5 * current.second + 4);
		cout << "|\xDB\xDB" << game_board_array[current.first][current.second] << "\xDB\xDB|";
		setCursorPosition(8 * current.first + 3, 5 * current.second + 5);
		cout << "|\xDB\xDB\xDB\xDB\xDB|";
		setCursorPosition(8 * current.first + 3, 5 * current.second + 6);
		cout << "+-----+";
		setCursorPosition(0, 0);
	}
}

//color in any cell wanted with cords
void selectCell(int** game_board_array, Point point)
{
	int position_x = point.first;
	int position_y = point.second;

	setCursorPosition(8 * position_x + 3, 5 * position_y + 2);
	cout << "+-----+ ";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 3);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 4);
	cout << "|\xDB\xDB" << game_board_array[position_x][position_y] << "\xDB\xDB|";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 5);
	cout << "|\xDB\xDB\xDB\xDB\xDB|";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 6);
	cout << "+-----+";
	setCursorPosition(0, 0);
}

//remove color in any cell wanted with cords
void deselecteCell(int** game_board_array, Point point)
{
	int position_x = point.first;
	int position_y = point.second;

	setCursorPosition(8 * position_x + 3, 5 * position_y + 2);
	cout << "+-----+ ";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 3);
	cout << "|     |";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 4);
	if (game_board_array[position_x][position_y] != -1)
		cout << "|  " << game_board_array[position_x][position_y] << "  |";
	else
		cout << "|     |";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 5);
	cout << "|     |";
	setCursorPosition(8 * position_x + 3, 5 * position_y + 6);
	cout << "+-----+";
}

//debug function
void clearCell(Point point, int** game_board_array)
{
	game_board_array[point.first][point.second] = -1;
}