#include <iostream>

using std::cout;

//printing and updating the settings menu
void printSettingsMenu(int current_option, int previous_option, int volume, bool light_mode, bool change_option)
{
	if (change_option)
	{
		setCursorPosition(15, 2 * current_option + 3);
		cout << ">>>>";

		setCursorPosition(15, 2 * previous_option + 3);
		cout << "    ";

		setCursorPosition(30, 5);
		for (int i = 0; i < volume; i++)
			cout << "\xDB";
		for (int i = 0; i < 10 - volume; i++)
			cout << " ";
		cout << "> ";
		if (volume != 10)
			cout << 10 * volume << "% ";
		else
			cout << "100%";

		setCursorPosition(21, 7);
		if (light_mode == true)
			cout << "Light mode: On ";
		else
			cout << "Light mode: Off";
		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                     Settings                                    |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |       >>>>  Volume: <\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB>                                                |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |             Light mode: Off                                                     |     |" << "\n"; //6 
	cout << "|     |                                                                                 |     |" << "\n"; //7
	cout << "|     |                                                                                 |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |                           Return to previous menu....                           |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     | Move Up: W / Move Down: S / Move Left: A / Move Right: D / Confirm: E           |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//printing and updating the main menu
void printMainMenu(int current_option, int previous_option, bool change_option)
{
	if (change_option)
	{
		setCursorPosition(40, 2 * current_option + 3);
		cout << ">>";
		setCursorPosition(40 + 15, 2 * current_option + 3);
		cout << "<<";

		setCursorPosition(40, 2 * previous_option + 3);
		cout << "  ";
		setCursorPosition(40 + 15, 2 * previous_option + 3);
		cout << "  ";
		setCursorPosition(40 + 17, 2 * current_option + 3);


		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                             Untitled Matching Game                              |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |                                >>    Start    <<                                |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |                                   Leaderboard                                   |     |" << "\n"; //6
	cout << "|     |                                                                                 |     |" << "\n"; //7 
	cout << "|     |                                     Setting                                     |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |                                    Quit game                                    |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     | Move Up: W / Move Down: S / Confirm: E                                          |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}

//printing and updating the menu containing everything before the game starts
void printGameplayPresetScreen(int current_option, int previous_option, int difficulty, int time, int size, bool change_option)
{
	//difficulty: easy, normal, hard, custom
	//custom will not be logged into leaderboards
	//if choose custom, user can move cursor down to size and timer to change it themselves
	if (change_option)
	{
		setCursorPosition(15, 2 * current_option + 3);
		cout << ">>>>";

		setCursorPosition(15, 2 * previous_option + 3);
		cout << "    ";

		setCursorPosition(32, 4);
		switch (difficulty)
		{
		case 1:
			cout << "Easy  ";
			setCursorPosition(32, 6);
			cout << "4x6";
			setCursorPosition(32, 8);
			cout << "7 minutes";
			break;
		case 2:
			cout << "Normal";
			setCursorPosition(32, 6);
			cout << "6x8";
			setCursorPosition(32, 8);
			cout << "5 minutes";
			break;
		case 3:
			cout << "Hard  ";
			setCursorPosition(32, 6);
			cout << "8x10";
			setCursorPosition(32, 8);
			cout << "3 minutes";
			break;
		}
		return;
	}

	system("cls");
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //0
	cout << "|     |                                Pre-game settings                                |     |" << "\n"; //1
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //2
	cout << "|     |                                                                                 |     |" << "\n"; //3
	cout << "|     |        >>>> Difficulty: Normal                                                  |     |" << "\n"; //4
	cout << "|     |                                                                                 |     |" << "\n"; //5
	cout << "|     |             Size: 8x6                                                           |     |" << "\n"; //6
	cout << "|     |                                                                                 |     |" << "\n"; //7
	cout << "|     |             Time: 5 minutes                                                     |     |" << "\n"; //8
	cout << "|     |                                                                                 |     |" << "\n"; //9
	cout << "|     |             Return to main menu...                                              |     |" << "\n"; //10
	cout << "|     |                                                                                 |     |" << "\n"; //11
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //12
	cout << "|     |                                                                                 |     |" << "\n"; //13
	cout << "|-----|---------------------------------------------------------------------------------|-----|" << "\n"; //14
}