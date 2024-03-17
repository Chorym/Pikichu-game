#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <Windows.h>

using std::string;
using std::cout;
using std::cin;

/*
Notes:

function name should be writen like this:
type functionName(){}
camel case

Variable should be:
type variable_name;
snake case
DO NOT abriviate, type out the full name of the variable (exp: head_pointer OR pointer_head, NO p_head)

Struct/Class should be:
Struct/Class Item(){};
one word, captital first letter

*/

void setCursorPosition(int x, int y)
{
	cout << "\x1b[" << y << ";" << x << "H";
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
	for (int i = 0; i < width * length; i+=2)
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

void printGameBoard(int** game_board_array, int length, int width)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = width - 1; j >= 0; j--)
		{
			for (int k = 0; k < j; k++) cout << "      ";
			cout << " ___ " << "\n";
			for (int k = 0; k < j; k++) cout << "      ";
			cout << "|   |" << "\n";
			for (int k = 0; k < j; k++) cout << "      ";
			cout << "| " << game_board_array[i][j] << " |" << "\n";
			for (int k = 0; k < j; k++) cout << "      ";
			cout << "|___|\x1b[3A" << "\r";
		}
		cout << "\n\n\n\n";
	}
}

//color the current cell that the player is on
void drawCurrentCell(int** game_board_array, int current_position_x, int current_position_y, int previous_position_x, int previous_position_y, int selected_cells[4])
{
	if ((previous_position_x != selected_cells[0] || 
		previous_position_y != selected_cells[1]) &&
		(previous_position_x != selected_cells[2] ||
		previous_position_y != selected_cells[3]))
	{
		setCursorPosition(previous_position_x * 6 + 1, previous_position_y * 4 + 1);
		cout << " ___ ";
		setCursorPosition(previous_position_x * 6 + 1, previous_position_y * 4 + 2);
		cout << "|   |";
		setCursorPosition(previous_position_x * 6 + 1, previous_position_y * 4 + 3);
		cout << "| " << game_board_array[previous_position_y][previous_position_x] << " |" << "\n";
		setCursorPosition(previous_position_x * 6 + 1, previous_position_y * 4 + 4);
		cout << "|___|";
	}

	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 1);
	cout << " ___ ";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 2);
	cout << "|\xDB\xDB\xDB|";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 3);
	cout << "|\xDB" << game_board_array[current_position_y][current_position_x] << "\xDB|" << "\n";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 4);
	cout << "|\xDB\xDB\xDB|";
}

//draw any cell wanted with cords
void drawSelectedCell(int** game_board_array, int position_x, int position_y)
{
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 1);
	cout << " ___ ";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 2);
	cout << "|\xDB\xDB\xDB|";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 3);
	cout << "|\xDB" << game_board_array[position_y][position_x] << "\xDB|" << "\n";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 4);
	cout << "|\xDB\xDB\xDB|";
}

//remove any cell wanted with cords
void removeSelectedCell(int** game_board_array, int position_x, int position_y)
{
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 1);
	cout << " ___ ";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 2);
	cout << "|   |";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 3);
	cout << "| " << game_board_array[position_y][position_x] << " |" << "\n";
	setCursorPosition(position_x * 6 + 1, position_y * 4 + 4);
	cout << "|___|";
}

//find if the 2 selected cells are connectable
void pathfinding2Cells()
{

}

void mainGameLoop(int board_length, int board_width)
{
	int** game_board_array = generateGameBoard(board_length, board_width);
	printGameBoard(game_board_array, board_length, board_width);

	bool run = true;
	int moving = false;

	bool key_pressed_W = false;
	bool key_pressed_A = false;
	bool key_pressed_S = false;
	bool key_pressed_D = false;
	bool key_pressed_E = false;
	bool key_pressed_Q = false;

	int current_position_x = 0;
	int current_position_y = 0;
	int previous_position_x = 0;
	int previous_position_y = 0;

	int selected_cells[] = { -1, -1, -1, -1 };
	drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_cells);

	while (run)
	{
		//move horizontally
		if (GetAsyncKeyState('D') & 0x8000 && !key_pressed_D)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_x++;
			if (current_position_x > board_width - 1) current_position_x = 0;
			moving = true;
			key_pressed_D = true;
		}
		if (!(GetAsyncKeyState('D') & 0x8000) && key_pressed_D) key_pressed_D = false;

		if (GetAsyncKeyState('A') & 0x8000 && !key_pressed_A)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_x--;
			if (current_position_x < 0) current_position_x = board_width - 1;
			moving = true;
			key_pressed_A = true;
		}
		if (!(GetAsyncKeyState('A') & 0x8000) && key_pressed_A) key_pressed_A = false;


		//move vertically
		if (GetAsyncKeyState('W') & 0x8000 && !key_pressed_W)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y--;
			if (current_position_y < 0) current_position_y = board_length - 1;
			moving = true;
			key_pressed_W = true;
		}
		if (!(GetAsyncKeyState('W') & 0x8000) && key_pressed_W) key_pressed_W = false;

		if (GetAsyncKeyState('S') & 0x8000 && !key_pressed_S)
		{
			previous_position_x = current_position_x;
			previous_position_y = current_position_y;
			current_position_y++;
			if (current_position_y > board_length - 1) current_position_y = 0;
			moving = true;
			key_pressed_S = true;
		}
		if (!(GetAsyncKeyState('S') & 0x8000) && key_pressed_S) key_pressed_S = false;


		//movement
		if (moving)
		{
			drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_cells);
			moving = false;
		}


		//selecting and drawing cells
		if (GetAsyncKeyState('E') & 0x8000 && !key_pressed_E)
		{
			if (selected_cells[0] == -1)
			{
				if (current_position_x != selected_cells[0] && current_position_y != selected_cells[1])
				{
					selected_cells[0] = current_position_x;
					selected_cells[1] = current_position_y;
					drawSelectedCell(game_board_array, current_position_x, current_position_y);
					key_pressed_E = true;
				}
			}
			else if (selected_cells[2] == -1)
			{
				if (current_position_x != selected_cells[2] && current_position_y != selected_cells[3])
				{
					selected_cells[2] = current_position_x;
					selected_cells[3] = current_position_y;
					drawSelectedCell(game_board_array, current_position_x, current_position_y);
					key_pressed_E = true;
				}
			}
		}
		if (!(GetAsyncKeyState('E') & 0x8000) && key_pressed_E) key_pressed_E = false;

		//canceling cells
		if (GetAsyncKeyState('Q') & 0x8000 && !key_pressed_Q)
		{
			if (current_position_x == selected_cells[0] && current_position_y == selected_cells[1])
			{
				selected_cells[0] = -1;
				selected_cells[1] = -1;
				removeSelectedCell(game_board_array, current_position_x, current_position_y);
				key_pressed_Q = true;
			}
			else if (current_position_x == selected_cells[2] && current_position_y == selected_cells[3])
			{
				selected_cells[2] = -1;
				selected_cells[3] = -1;
				removeSelectedCell(game_board_array, current_position_x, current_position_y);
				key_pressed_Q = true;
			}
		}
		if (!(GetAsyncKeyState('Q') & 0x8000) && key_pressed_Q) key_pressed_Q = false;


		//if 2 cells are selected
		


		//exit game
		if (GetAsyncKeyState('F') & 0x8000)
		{
			run = false;
		}
	}

	clear2DArray(game_board_array, board_length);
}

int main()
{
	srand(time(NULL));
	int length = 6;
	int width = 8;
	if (length * width % 2 != 0)
	{
		cout << "wrong dimensions" << "\n";
		return 0;
	}

	mainGameLoop(length, width);
	return 0;
}