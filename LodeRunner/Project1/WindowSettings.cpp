#include "WindowSettings.h"

using namespace std;

void ShowConsole()
{
	system("title LODE RUNNER");
	system("color F0"); //F0
	int screen_width = GetSystemMetrics(SM_CXSCREEN); // ��������� ���������� ������
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(GetConsoleWindow(), 0, 0, screen_width, screen_height, true);
	ShowCursor(false);
}