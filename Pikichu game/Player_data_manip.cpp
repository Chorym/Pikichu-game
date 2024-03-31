#include <fstream>
#include <iostream>
#include <string>

using std::string;

struct PlayerData
{
	string name = "";

    //saves the best time of each difficulty
    int record_time[3] = { -1, -1, -1 };

    //
    int previous_game = 0;
    int board_x = -1;
    int board_y = -1;

    //
    int previous_game_time = -1;
    int previous_game_cell_amount = -1;

    //used to load a board or to pass value to previous_game_board_state[12][12] to save values
    int** previous_board_pointer = nullptr;
};

bool writingPlayerData(string file_name, PlayerData player_data[])
{
    std::ofstream file_writing(file_name, std::ios::binary);

    if (!file_writing)
    {
        std::cout << "Can't open file / File missing!" << "\n";
        system("pause");
        return false;
    }

    int i = 0;
    while (player_data[i].name == "")
    {
        //write name
        size_t string_length = player_data[i].name.size();
        file_writing.write(reinterpret_cast<const char*>(&string_length), sizeof(string_length));
        file_writing.write(player_data[i].name.c_str(), string_length);

        //write record time
        for (int j = 0; j < 3; ++j)
        {
            file_writing.write(reinterpret_cast<const char*>(&player_data[i].record_time[j]), sizeof(player_data[i].record_time[j]));
        }

        //write previous game 
        file_writing.write(reinterpret_cast<const char*>(&player_data[i].previous_game), sizeof(player_data[i].previous_game));
        if (player_data[i].previous_game == false)
        {
            continue; //theres nothing to save, continue onto the next player data set
        }

        //write board x and board y
        file_writing.write(reinterpret_cast<const char*>(&player_data[i].board_x), sizeof(player_data[i].board_x));
        file_writing.write(reinterpret_cast<const char*>(&player_data[i].board_y), sizeof(player_data[i].board_y));

        //write the board values
        for (int x = 0; x < player_data[i].board_x; x++)
        {
            for (int y = 0; y < player_data[i].board_y; y++)
            {
                file_writing.write(reinterpret_cast<const char*>(&player_data[i].previous_board_pointer[x][y]), sizeof(int));
            }
        }

        i++;
    }

    file_writing.close();
    return true;
}

bool readingPlayerData(string file_name, PlayerData player_data[])
{
    std::ifstream file_reading(file_name, std::ios::binary);

    if (!file_reading)
    {
        std::cerr << "Can't open file / File missing!" << "\n";
        return false;
    }

    int i = 0;
    while (file_reading.peek() != EOF)
    {
        //read name
        std::getline(file_reading, player_data[i].name, '\0');

        //read record time
        file_reading.read(reinterpret_cast<char*>(&player_data[i].record_time), sizeof(player_data[i].record_time));

        //read previous game 
        file_reading.read(reinterpret_cast<char*>(&player_data[i].previous_game), sizeof(player_data[i].previous_game));

        if (player_data[i].previous_game == false)
        {
            continue; //there is no game to load, continue onto the next player data set
        }

        //read board x and board y
        file_reading.read(reinterpret_cast<char*>(&player_data[i].board_x), sizeof(player_data[i].board_x));
        file_reading.read(reinterpret_cast<char*>(&player_data[i].board_y), sizeof(player_data[i].board_y));

        //allocate memory for game board array
        player_data[i].previous_board_pointer = new int* [player_data[i].board_x];
        for (int x = 0; x < player_data[i].board_x; x++)
        {
            player_data[i].previous_board_pointer[x] = new int[player_data[i].board_y];
        }

        //read the board values
        for (int x = 0; x < player_data[i].board_x; x++)
        {
            for (int y = 0; y < player_data[i].board_y; y++)
            {
                file_reading.read(reinterpret_cast<char*>(&player_data[i].previous_board_pointer[x][y]), sizeof(int));
            }
        }

        i++;
    }

    file_reading.close();
    return true;
}

void savePlayerData(PlayerData player_data[], PlayerData current_player)
{
    int i = 0;
    while (player_data[i].name != current_player.name)
    {
        i++;
    }

    player_data[i].record_time[0] = current_player.record_time[0];
    player_data[i].record_time[1] = current_player.record_time[1];
    player_data[i].record_time[2] = current_player.record_time[2];

    player_data[i].board_x = current_player.board_x;
    player_data[i].board_y = current_player.board_y;

    player_data[i].previous_board_pointer = current_player.previous_board_pointer;
}

void loadPlayerData(PlayerData player_data[], PlayerData& current_player, string name)
{
    int i = 0;
    while (player_data[i].name != name)
    {
        i++;
    }

    current_player.name = name;
    current_player.record_time[0] = player_data[i].record_time[0];
    current_player.record_time[1] = player_data[i].record_time[1];
    current_player.record_time[2] = player_data[i].record_time[2];

    current_player.board_x = player_data[i].board_x;
    current_player.board_y = player_data[i].board_y;

    current_player.previous_board_pointer = player_data[i].previous_board_pointer;
}


