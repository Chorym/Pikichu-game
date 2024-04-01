#include <iostream>
#include <utility>
#include <chrono>
#include <ctime>
#include <future>
#include <thread>
#include "Rendering.h"
#include "Game_logic.h"

using std::make_pair;
using std::cout;

typedef std::pair<int, int> Point;

//needs referencing
void async_sleep_milliseconds(int time) 
{
	std::chrono::milliseconds duration(time);

	std::async(std::launch::async, [=]() {
		std::this_thread::sleep_for(duration);
		});
}

int currentSystemTime()
{
	auto now = std::chrono::system_clock::now();
	std::chrono::seconds seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	int current_time_seconds = seconds_since_epoch.count();
	return current_time_seconds;
}

bool pathfinding2Cells(Point selected_points[2], Point mid_points[2], int** game_board_array, int board_x, int board_y)
{
	Point start = selected_points[0];
	Point end = selected_points[1];
	Point empty = make_pair(-1, -1);

	int path_type;

	Point middle_1 = empty;
	Point middle_2 = empty;

	bool found_path = false;

	if (game_board_array[start.first][start.second] != game_board_array[end.first][end.second] || start == end)
	{
		found_path = false;
	}
	else if (isClearedLine(start, end, game_board_array))
	{
		found_path = true;
		path_type = 0;
	}
	else if (isLshapeLine(start, end, game_board_array, middle_1))
	{
		found_path = true;
		path_type = 1;
	}
	else if (isUShapeLine(start, end, game_board_array, board_x, board_y, middle_1, middle_2))
	{
		found_path = true;
		path_type = 2;
	}
	else if (isZShapeLine(start, end, game_board_array, board_x, board_y, middle_1, middle_2))
	{
		found_path = true;
		path_type = 3;
	}

	if (found_path)
	{
		game_board_array[start.first][start.second] = -1;
		game_board_array[end.first][end.second] = -1;
		mid_points[0] = middle_1;
		mid_points[1] = middle_2;
		return true;
	}
	else
	{
		return false;
	}
}

bool isObstructed(Point point, int** game_board_array)
{
	if (game_board_array[point.first][point.second] == -1) return false;
	else return true;
}

bool isClearedLine(Point start, Point end, int** game_board_array)
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

bool isLshapeLine(Point start, Point end, int** game_board_array, Point &middle)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	middle = make_pair(start.first + distance_x, start.second);

	if (!isObstructed(middle, game_board_array))
	{
		if (isClearedLine(start, middle, game_board_array) && isClearedLine(middle, end, game_board_array))
		{
			return true;
		}
	}

	middle = make_pair(start.first, start.second + distance_y);

	if (!isObstructed(middle, game_board_array))
	{
		if (isClearedLine(start, middle, game_board_array) && isClearedLine(middle, end, game_board_array))
		{
			return true;
		}
	}

	return false;
}

bool isUShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y, Point& middle_1, Point& middle_2)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int middle_path_x = 0;
	int middle_path_y = 0;

	middle_1 = make_pair(middle_path_x, start.second);
	middle_2 = make_pair(middle_path_x, end.second);

	for (int i = 0; i < board_x; i++)
	{
		//if the x value is in between the 2 x value of start and end, do nothing
		if (distance_x > 0)
		{
			if (i > start.first && i < end.first)
			{
				middle_1.first++;
				middle_2.first++;
				continue;
			}
		}
		else if (distance_x < 0)
		{
			if (i < start.first && i > end.first)
			{
				middle_1.first++;
				middle_2.first++;
				continue;
			}
		}

		//if the 2 middle point form a line and the 2 ends also form a line with Start and End, return true
		if (isClearedLine(middle_1, middle_2, game_board_array))
		{
			if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		middle_1.first++;
		middle_2.first++;
	}

	middle_1 = make_pair(start.first, middle_path_y);
	middle_2 = make_pair(end.first, middle_path_y);

	for (int i = 0; i < board_y; i++)
	{
		//if the y value is in between the 2 y value of start and end, do nothing
		if (distance_y > 0)
		{
			if (i >= start.second && i <= end.second)
			{
				middle_1.second++;
				middle_2.second++;
				continue;
			}
		}
		else
		{
			if (i <= start.second && i >= end.second)
			{
				middle_1.second++;
				middle_2.second++;
				continue;
			}
		}

		//if the 2 middle point form a line and the 2 ends also form a line with Start and End, return true
		if (isClearedLine(middle_1, middle_2, game_board_array))
		{
			if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
			{
				return true;
			}
		}
		middle_1.second++;
		middle_2.second++;
	}
	return false;
}

bool isZShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y, Point& middle_1, Point& middle_2)
{
	int distance_x = end.first - start.first;
	int distance_y = end.second - start.second;

	int direction_x = (distance_x != 0) ? distance_x / abs(distance_x) : 0;
	int direction_y = (distance_y != 0) ? distance_y / abs(distance_y) : 0;

	int middle_path_x = 0;
	int middle_path_y = 0;

	middle_path_x = start.first;
	middle_1 = make_pair(middle_path_x, start.second);
	middle_2 = make_pair(middle_path_x, end.second);

	//horizontal pathing
	if (direction_x > 0)
	{
		for (int i = start.first; i <= end.first; i++)
		{
			if (isClearedLine(middle_1, middle_2, game_board_array))
			{
				if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
				{
					return true;
				}
			}
			middle_1.first++;
			middle_2.first++;
		}
	}
	else if (direction_x < 0)
	{
		for (int i = start.first; i >= end.first; i--)
		{
			if (isClearedLine(middle_1, middle_2, game_board_array))
			{
				if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
				{
					return true;
				}
			}
			middle_1.first--;
			middle_2.first--;
		}
	}

	middle_path_y = start.second;
	middle_1 = make_pair(start.first, middle_path_y);
	middle_2 = make_pair(end.first, middle_path_y);

	//vertical pathing
	if (direction_y > 0)
	{
		for (int i = start.second; i <= end.second; i++)
		{
			if (isClearedLine(middle_1, middle_2, game_board_array))
			{
				if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
				{
					return true;
				}
			}
			middle_1.second++;
			middle_2.second++;
		}
	}
	else if (direction_y < 0)
	{
		for (int i = start.second; i >= end.second; i--)
		{
			if (isClearedLine(middle_1, middle_2, game_board_array))
			{
				if (isClearedLine(start, middle_1, game_board_array) && isClearedLine(middle_2, end, game_board_array) && !isObstructed(middle_1, game_board_array) && !isObstructed(middle_2, game_board_array))
				{
					return true;
				}
			}
			middle_1.second--;
			middle_2.second--;
		}
	}

	return false;
}

bool checkIfPossible(int** game_board_array, int board_x, int board_y)
{
	Point middle_1 = make_pair(-1, -1);
	Point middle_2 = make_pair(-1, -1);

	//Select start point
	for (int a = 0; a < board_x; a++)
	{
		for (int b = 0; b < board_y; b++)
		{
			Point start = make_pair(a, b);

			//Select end point ( != start )
			for (int c = 0; c < board_x; c++)
			{
				for (int d = 0; d < board_y; d++)
				{
					if (c == a && d == b) continue;
					Point end = make_pair(c, d);

					if (
						isClearedLine(start, end, game_board_array) ||
						isLshapeLine(start, end, game_board_array, middle_1) ||
						isUShapeLine(start, end, game_board_array, board_x, board_y, middle_1, middle_2) ||
						isZShapeLine(start, end, game_board_array, board_x, board_y, middle_1, middle_2)
						)
						return true;
				}
			}
		}
	}
	return false;
}
