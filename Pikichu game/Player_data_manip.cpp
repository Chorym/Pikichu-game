#include <fstream>
#include <iostream>
#include <string>
#include "Player_data_manip.h"
#include "Rendering.h"

using std::string;

bool writingPlayerData(string file_name, PlayerData player_data[])
{
    std::ofstream file_writing(file_name, std::ios::binary);

    if (!file_writing)
    {
        system("cls");
        std::cout << "Can't open file / File missing!" << "\n";
        system("pause");
        return false;
    }
    
    int i = 0;
    while (player_data[i].name != "")
    {
        //write name
        file_writing.write(player_data[i].name.c_str(), player_data[i].name.size() + 1);

        //write record time
        for (int j = 0; j < 3; j++)
        {
            file_writing.write(reinterpret_cast<char*>(&player_data[i].record_time[j]), sizeof(int));
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
    while (!file_reading.eof())
    {
        //read name
        std::getline(file_reading, player_data[i].name, '\0');

        //read record time
        for (int j = 0; j < 3; j++)
        {
            file_reading.read(reinterpret_cast<char*>(&player_data[i].record_time[j]), sizeof(int));
        }

        i++;
    }

    file_reading.close();
    return true;
}

void savePlayerData(PlayerData player_data[], PlayerData &current_player)
{
    int i = 0;
    while (player_data[i].name != current_player.name)
    {
        i++;
    }

    player_data[i].record_time[0] = current_player.record_time[0];
    player_data[i].record_time[1] = current_player.record_time[1];
    player_data[i].record_time[2] = current_player.record_time[2];
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
}

void top5Time(PlayerData player_data[], PlayerData sorted[5], int difficulty)
{
    for (int i = 0; i < 5; i++)
    {
        int j = 0;
        int min_time = player_data[j].record_time[difficulty];
        int min_time_position = 0;
        while (player_data[j].name != "")
        {
            if (player_data[j].record_time[difficulty] < min_time)
            {
                for (int k = 0; k < i; k++)
                {
                    if (min_time == sorted[k].record_time[difficulty])
                    {
                        min_time = player_data[j].record_time[difficulty];
                        min_time_position = j;
                    }
                }
                if (i == 0)
                {
                    min_time = player_data[j].record_time[difficulty];
                    min_time_position = j;
                }
            }
            j++;
        }
        sorted[i] = player_data[min_time_position];
    }
}

