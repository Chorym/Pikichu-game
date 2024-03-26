#pragma once
#include <utility>

typedef std::pair<int, int> Point;

int currentSystemTime();
bool pathfinding2Cells(Point selected_points[2], int** game_board_array, int board_x, int board_y);
bool isObstructed(Point point, int** game_board_array);
bool isClearedLine(Point start, Point end, int** game_board_array);
bool isLshapeLine(Point start, Point end, int** game_board_array);
bool isUShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y);
bool isZShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y);
