#include <iostream>
#include <Windows.h>
#include <random>
#include <utility>

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
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option, bool render)
{
	if (change_option)
	{
		setCursorPosition(14, 2 * current_option + 2);
		cout << ">>>>";

		setCursorPosition(14, 2 * previous_option + 2);
		cout << "    ";

		setCursorPosition(30, 4);
		for (int i = 0; i < volume; i++)
			cout << "\xDB";
		for (int i = 0; i < 10 - volume; i++)
			cout << " ";
		cout << "> ";
		if (volume != 10)
			cout << 10 * volume << "% ";
		else
			cout << "100%";

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
		cout << "|     |             Volume: <\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB> 100%                         | Up:   W                       |     |" << "\n";; //4
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

		setCursorPosition(30, 4);
		for (int i = 0; i < volume; i++)
			cout << "\xDB";
		for (int i = 0; i < 10 - volume; i++)
			cout << " ";
		cout << "> ";
		if (volume != 10)
			cout << 10 * volume << "% ";
		else
			cout << "100%";

		setCursorPosition(20, 6);
		if (light_mode == true)
			cout << "Light mode: On ";
		else
			cout << "Light mode: Off";
	}
}

//printing and updating the main menu
void printMainMenu(int current_option, int previous_option, bool change_option)
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
	cout << "|     |                          Leaderboard                          | Down:    S                    |     |" << "\n"; //6
	cout << "|     |                                                               | Confirm: E                    |     |" << "\n"; //7 
	cout << "|     |                            Setting                            |                               |     |" << "\n"; //8
	cout << "|     |                                                               |                               |     |" << "\n"; //9
	cout << "|     |                           Quit game                           |                               |     |" << "\n"; //10
	cout << "|     |                                                               |                               |     |" << "\n"; //11
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     |                                                                                               |     |" << "\n"; //13
	cout << "|-----|-----------------------------------------------------------------------------------------------|-----|" << "\n"; //14
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
	setCursorPosition(130, 4);
	cout << "Controls:";
	setCursorPosition(110, 6);
	cout << "Up:    W   |   Select:   E";
	setCursorPosition(110, 7);
	cout << "Left:  A   |   Deselect: Q";
	setCursorPosition(110, 8);
	cout << "Down:  S   |";
	setCursorPosition(110, 9);
	cout << "Right: D   |";

	setCursorPosition(110, 11);
	cout << "End game: F";
}

//
//gameplay related rendering
//

void clear2DArray(int** array, int board_x)
{
	for (int i = 0; i < board_x; i++)
	{
		delete[]array[i];
	}
	delete[]array;
}

int** generateGameBoard(int board_x, int board_y)
{
	int** game_board_array_pointer = nullptr;
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