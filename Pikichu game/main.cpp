#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <Windows.h>

#include <fstream>

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

void drawGameBoard(int** game_board_array, int length, int width)
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
			if(game_board_array[i][j] != -1)
				cout << "| " << game_board_array[i][j] << " |" << "\n";
			else
				cout << "|   |" << "\n";
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
		if(game_board_array[previous_position_y][previous_position_x] != -1)
			cout << "| " << game_board_array[previous_position_y][previous_position_x] << " |" << "\n";
		else 
			cout << "|   |" << "\n";
		setCursorPosition(previous_position_x * 6 + 1, previous_position_y * 4 + 4);
		cout << "|___|";
	}
	
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 1);
	cout << " ___ ";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 2);
	cout << "|\xDB\xDB\xDB|";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 3);
	if (game_board_array[current_position_y][current_position_x] != -1)
		cout << "|\xDB" << game_board_array[current_position_y][current_position_x] << "\xDB|" << "\n";
	else
		cout << "|\xDB\xDB\xDB|" << "\n";
	setCursorPosition(current_position_x * 6 + 1, current_position_y * 4 + 4);
	cout << "|\xDB\xDB\xDB|";
}

//select any cell wanted with cords
void selectCell(int** game_board_array, int position_x, int position_y)
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

//deselect any cell wanted with cords
void deselecteCell(int** game_board_array, int position_x, int position_y)
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
void pathfinding2Cells(int selected_cells[4], int** game_board_array)
{
	//debugging
	std::fstream fin;
	fin.open("debug.txt");
	//

	//distance and direction to go

	if (game_board_array[selected_cells[1]][selected_cells[0]] != game_board_array[selected_cells[3]][selected_cells[2]])
	{
		selected_cells[0] = -1;
		selected_cells[1] = -1;
		selected_cells[2] = -1;
		selected_cells[3] = -1;
		return;
	}

	int shortest_distance_x = selected_cells[2] - selected_cells[0];
	int shortest_distance_y = selected_cells[3] - selected_cells[1];
	int x_direction = 0;
	int y_direction = 0;

	int traverse_x = selected_cells[0];
	int traverse_y = selected_cells[1];

	if(shortest_distance_x != 0)
		x_direction = shortest_distance_x / abs(shortest_distance_x);
	if(shortest_distance_y != 0)
		y_direction = shortest_distance_y / abs(shortest_distance_y);

	//if 2 cell are next to each other
	if ((abs(shortest_distance_x) == 1 && abs(shortest_distance_y == 0)) || (abs(shortest_distance_x) == 0 && abs(shortest_distance_y == 1)))
	{
		game_board_array[selected_cells[1]][selected_cells[0]] = -1;
		game_board_array[selected_cells[3]][selected_cells[2]] = -1;
	}
	//if 2 cell are connected by a vertical line
	else if (abs(shortest_distance_x == 0) && abs(shortest_distance_y != 0))
	{
		while (traverse_y != selected_cells[3])
		{
			traverse_y += y_direction;
			if (game_board_array[traverse_y][traverse_x] != -1 && traverse_y != selected_cells[3]) break;
			if (traverse_y == selected_cells[3])
			{
				game_board_array[selected_cells[1]][selected_cells[0]] = -1;
				game_board_array[selected_cells[3]][selected_cells[2]] = -1;
				break;
			}
		}
	}
	//if 2 cells are connected by a horizontal line
	else if (abs(shortest_distance_x != 0) && abs(shortest_distance_y == 0))
	{
		while (traverse_x != selected_cells[2])
		{
			traverse_x += x_direction;
			if (game_board_array[traverse_y][traverse_x] != -1 && traverse_x != selected_cells[2]) break;
			if (traverse_x == selected_cells[2])
			{
				game_board_array[selected_cells[1]][selected_cells[0]] = -1;
				game_board_array[selected_cells[3]][selected_cells[2]] = -1;
				break;
			}
		}
	}
	else
	{
		bool is_L_shape_path = false;
		bool is_U_shape_path = false;
		bool is_Z_shape_path = false;

		//if 2 cells are connected by an L-shape line
		while (!is_L_shape_path)
		{
			bool vertical_axis_cleared = false;
			bool horizontal_axis_cleared = false;

			//move horizontally first
			while (traverse_x != selected_cells[2])
			{
				traverse_x += x_direction;
				if (game_board_array[traverse_y][traverse_x] != -1)
				{
					traverse_x = selected_cells[0];
					break;
				}
				if (traverse_x == selected_cells[2])
				{
					horizontal_axis_cleared = true;
					break;
				}
			}
			//if fail, move vertically
			while (traverse_y != selected_cells[3] && !horizontal_axis_cleared)
			{
				traverse_y += y_direction;
				if (game_board_array[traverse_y][traverse_x] != -1) break;
				if (traverse_y == selected_cells[3])
				{
					vertical_axis_cleared = true;
					break;
				}
			}

			if (!horizontal_axis_cleared && !vertical_axis_cleared)
			{
				break; //cant find L path
			}

			//if the cleared axis is vertical, move horizontal
			if (vertical_axis_cleared)
			{
				while (traverse_x != selected_cells[2])
				{
					traverse_x += x_direction;
					if (game_board_array[traverse_y][traverse_x] != -1 && traverse_x != selected_cells[2]) break;
					if (traverse_x == selected_cells[2])
					{
						game_board_array[selected_cells[1]][selected_cells[0]] = -1;
						game_board_array[selected_cells[3]][selected_cells[2]] = -1;
						is_L_shape_path = true;
						break;
					}
				}
			}
			//vice versa
			else
			{
				while (traverse_y != selected_cells[3])
				{
					traverse_y += y_direction;
					if (game_board_array[traverse_y][traverse_x] != -1 && traverse_x != selected_cells[2]) break;
					if (traverse_y == selected_cells[3])
					{
						game_board_array[selected_cells[1]][selected_cells[0]] = -1;
						game_board_array[selected_cells[3]][selected_cells[2]] = -1;
						is_L_shape_path = true;
						break;
					}
				}
			}
		}

		//if 2 cells are connected by a U-shape line
		while (!is_U_shape_path)
		{
			break;
		}


		//if 2 cells are connected by a Z-shape line
		while (!is_Z_shape_path)
		{
			break;
		}
	}
	
	//debugging
	fin.close();
	//
	
	//reset cells 
	selected_cells[0] = -1;
	selected_cells[1] = -1;
	selected_cells[2] = -1;
	selected_cells[3] = -1;
}

void mainGameLoop(int board_length, int board_width)
{
	int** game_board_array = generateGameBoard(board_length, board_width);
	drawGameBoard(game_board_array, board_length, board_width);

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

	//selected_cells array hold the x:y value for 2 points that the player choose to connect
	//0:1 is x:y of the first point
	//2:3 is x:y of the second point
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
			if (game_board_array[current_position_y][current_position_x] != -1)
			{
				if (selected_cells[0] == -1 && current_position_x != -1)
				{
					if (current_position_x != selected_cells[0] && current_position_y != selected_cells[1])
					{
						selected_cells[0] = current_position_x;
						selected_cells[1] = current_position_y;
						selectCell(game_board_array, current_position_x, current_position_y);
						key_pressed_E = true;
					}
				}
				else if (selected_cells[2] == -1 && current_position_x != -1)
				{
					if (current_position_x != selected_cells[2] && current_position_y != selected_cells[3])
					{
						selected_cells[2] = current_position_x;
						selected_cells[3] = current_position_y;
						selectCell(game_board_array, current_position_x, current_position_y);
						key_pressed_E = true;
					}
				}
			}
		}
		if (!(GetAsyncKeyState('E') & 0x8000) && key_pressed_E) key_pressed_E = false;

		//canceling cells
		if (GetAsyncKeyState('Q') & 0x8000 && !key_pressed_Q)
		{
			if (current_position_x == selected_cells[0] && current_position_y == selected_cells[1] && current_position_x != -1)
			{
				selected_cells[0] = -1;
				selected_cells[1] = -1;
				deselecteCell(game_board_array, current_position_x, current_position_y);
				key_pressed_Q = true;
			}
			else if (current_position_x == selected_cells[2] && current_position_y == selected_cells[3] && current_position_x != -1)
			{
				selected_cells[2] = -1;
				selected_cells[3] = -1;
				deselecteCell(game_board_array, current_position_x, current_position_y);
				key_pressed_Q = true;
			}
		}
		if (!(GetAsyncKeyState('Q') & 0x8000) && key_pressed_Q) key_pressed_Q = false;


		//if 2 cells are selected
		if (selected_cells[0] != -1 && selected_cells[2] != -1)
		{
			pathfinding2Cells(selected_cells, game_board_array);
			setCursorPosition(0, 0);
			drawGameBoard(game_board_array, board_length, board_width);
			drawCurrentCell(game_board_array, current_position_x, current_position_y, previous_position_x, previous_position_y, selected_cells);
		}


		//exit game
		if (GetAsyncKeyState('F') & 0x8000)
		{
			setCursorPosition(0, 30);
			run = false;
		}
	}

	clear2DArray(game_board_array, board_length);
}

int main()
{
	/*debug
	std::fstream fin;
	fin.open("debug.txt");
	*/

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