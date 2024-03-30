#include <iostream>

struct Cell
{
	int value = -1;
	Cell* up = nullptr;
	Cell* down = nullptr;
	Cell* left = nullptr;
	Cell* right = nullptr;
};

Cell* createCell()
{
	Cell* new_cell = new Cell;
	return new_cell;
}

void linkCell(Cell* current_cell, Cell* next_cell, int direction)
{
	switch (direction)
	{
	case 0:
		current_cell->up = next_cell; break;
	case 1:
		current_cell->down = next_cell; break;
	case 2:
		current_cell->left = next_cell; break;
	case 3:
		current_cell->right = next_cell; break;
	}
}


