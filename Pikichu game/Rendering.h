#pragma once
#include <utility>

typedef std::pair<int, int> Point;

void setCursorPosition(int x, int y);

//menu
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option);
void printMainMenu(int current_option, int previous_option, bool change_option);
void printGameplayPresetScreen(int current_option, int previous_option, int difficulty, int time, int size, bool change_option);
void printGameplayFrame(int board_x, int board_y);

//gameplay
void clear2DArray(int** array, int board_x);
int** generateGameBoard(int board_x, int board_y);
void drawGameBoard(int** game_board_array, int board_x, int board_y);
void drawCurrentCell(int** game_board_array, Point current, Point previous, Point selected_points[2]);
void selectCell(int** game_board_array, Point point);
void deselecteCell(int** game_board_array, Point point);

//debug
void clearCell(Point point, int** game_board_array);