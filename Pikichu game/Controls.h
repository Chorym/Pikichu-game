#pragma once
#include "Player_data_manip.h"

bool isPressing(int key);
void gameplayLoop(int board_x, int board_y, int difficulty, int** &game_board_array, bool &load_game, PlayerData &current_player, bool soundEnable);
bool menuInteraction(bool& light_mode, int& board_x, int& board_y, int& difficulty, bool &load_game, PlayerData &current_player, bool &soundEnable);