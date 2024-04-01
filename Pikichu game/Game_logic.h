#pragma once
#include <utility>
#include <thread>

typedef std::pair<int, int> Point;
void async_sleep_milliseconds(int time);
int currentSystemTime();
bool pathfinding2Cells(Point selected_points[2], Point mid_points[2], int** game_board_array, int board_x, int board_y);
bool isObstructed(Point point, int** game_board_array);
bool isClearedLine(Point start, Point end, int** game_board_array);
bool isLshapeLine(Point start, Point end, int** game_board_array, Point& middle_a);
bool isUShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y, Point& middle_a, Point& middle_b);
bool isZShapeLine(Point start, Point end, int** game_board_array, int board_x, int board_y, Point& middle_a, Point& middle_b);
bool checkIfPossible(int** game_board_array, int board_x, int board_y);