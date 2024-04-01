#pragma once
#include <iostream>
#include <string>
#include <fstream>

using std::string;

struct PlayerData
{
    string name = "";

    //saves the best time of each difficulty
    int record_time[3] = { -1, -1, -1 };

    //only used during run time to load game, wont be saved
    //
    int previous_game = 0;
    int board_x = -1;
    int board_y = -1;

    //
    int previous_game_time = -1;
    int previous_game_cell_amount = -1;

    //
    int** previous_board_pointer = nullptr;
};

bool writingPlayerData(string file_name, PlayerData player_data[]);
bool readingPlayerData(string file_name, PlayerData player_data[]);
void loadPlayerData(PlayerData player_data[], PlayerData& current_player, string name);
void savePlayerData(PlayerData player_data[], PlayerData &current_player);
void top5Time(PlayerData player_data[], PlayerData sorted[5], int difficulty);