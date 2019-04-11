#include "Sound.h"

DWORD WINAPI MainMusic(void* p)
{
	PlaySound("sound/MainSound.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI MenuSound1(void* p)
{
	PlaySound("sound/1.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI MenuSound2(void* p)
{
	PlaySound("sound/2.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI MenuSound3(void* p)
{
	PlaySound("sound/3.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI MenuSound4(void* p)
{
	PlaySound("sound/4.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI MenuSound5(void* p)
{
	PlaySound("sound/5.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}
DWORD WINAPI Lose(void* p)
{
	PlaySound("sound/Lose.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}

DWORD WINAPI TakePrize(void* p)
{
	PlaySound("sound/TakePrize.wav", NULL, SND_NODEFAULT | SND_LOOP);
	return 0;
}