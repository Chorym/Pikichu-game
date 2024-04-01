#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

using namespace std;

void chooseSound(bool soundEnable)
{
	if(soundEnable)
		PlaySound(TEXT("SFX\\choose.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void victorySound(bool soundEnable)
{
	if (soundEnable)
		PlaySound(TEXT("SFX\\victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void failSound(bool soundEnable)
{
	if (soundEnable)
		PlaySound(TEXT("SFX\\challenge failed.wav"), NULL, SND_FILENAME | SND_ASYNC);

}

void successMatchingSound(bool soundEnable)
{
	if (soundEnable)
		PlaySound(TEXT("SFX\\success matching.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void themeSound(bool soundEnable)
{
	if (soundEnable)
		PlaySound(TEXT("SFX\\theme.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void shuffleSound(bool soundEnable)
{
	if (soundEnable)
		PlaySound(TEXT("SFX\\shuffle.wav"), NULL, SND_FILENAME | SND_ASYNC);
}