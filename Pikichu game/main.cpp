#include <iostream>
#include <string>

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

int generateCells()
{
	int cell1 = rand() % 10;
	return cell1;
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

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			game_board_array_pointer[i][j] = generateCells();
		}
	}
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

	//control
	cout << "\n\n\n\n";
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << game_board_array[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	srand(time(NULL));
	int length = 5;
	int width = 8;
	int** game_board_array = generateGameBoard(length, width);

	printGameBoard(game_board_array, length, width);

	clear2DArray(game_board_array, length);
	return 0;
}