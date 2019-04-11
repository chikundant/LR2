#include "FirstMap.h"
namespace fs = std::experimental::filesystem;

using namespace std;

Sprites block[COUNT_OF_BLOCKS];
Sprites rope[COUNT_OF_ROPES];
Sprites lader[COUNT_OF_LADERS];
Sprites prize[COUNT_OF_PRIZE];
Sprites enemy[COUNT_OF_ENEMY];

const string MAP1 = "DefaultMaps/Map1";
const string MAP2 = "DefaultMaps/Map2";
const string MAP3 = "DefaultMaps/Map3";

void PlayGame()
{
	HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE); // дескриптор окна для работы с мышкой
	SetConsoleMode(h_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // установка режима использования мышки
	INPUT_RECORD all_events[256]; // здесь хранятся все события, произошедшие в консоли
	DWORD read_enevt; // переменная, в которую запишется количество произошедших событий
	DrawBorder();
	char input = 0;

	while (true)
	{
		GotoXY(MENU_INDENT, INDENT_TOP + 1);
		cout << "PLAY";
		GotoXY(MENU_INDENT, INDENT_TOP + 3);
		cout << "CREATE";
		GotoXY(MENU_INDENT, INDENT_TOP + 5);
		cout << "LOAD";
		GotoXY(MENU_INDENT, INDENT_TOP + 7);
		cout << "EXIT          ";
		ReadConsoleInput(h_in, all_events, 256, &read_enevt); // получить все события, произошедшие в консоли
		for (int i = 0; i < read_enevt; i++)
		{
			// пройтись по всем событиям
			if (all_events[i].EventType == MOUSE_EVENT)
			{ // если произошло событие мышки
				for (int k = 0; k < 16; k++)
				{
					// Item 1
					if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
						all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
						all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 1 &&
						all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						DrawSpace(0, INDENT_SIDE - 2, 0, 50);
						Move();
					}
					// Item 2
					else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT + 2 &&
						all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 6) &&
						all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 3 &&
						all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						DeleteArray();
						GotoXY(MENU_INDENT, INDENT_TOP + 9);
						cout << "Write map name" << endl;
						DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
						ShowCursor(true);
						string *name = new string;
						GotoXY(MENU_INDENT, INDENT_TOP + 10);
						cin >> *name;
						ShowCursor(false);
						GotoXY(INDENT_SIDE / 2 + WIDTH / 2, INDENT_TOP / 2);
						cout << *name;
						DrawSpace(0, INDENT_SIDE - 2, 0, 50);
						CreateMap();
						WriteToFile(*name);
						delete name;
						continue;
					}
					// Item 3
					else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
						all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
						all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 5 &&
						all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						GotoXY(MENU_INDENT, INDENT_TOP + 1);
						cout << "MAP1  ";
						GotoXY(MENU_INDENT, INDENT_TOP + 3);
						cout << "MAP2  ";
						GotoXY(MENU_INDENT, INDENT_TOP + 5);
						cout << "MAP3  ";
						GotoXY(MENU_INDENT, INDENT_TOP + 7);
						cout << "USER MAP   ";
						ReadConsoleInput(h_in, all_events, 256, &read_enevt); // получить все события, произошедшие в консоли
						bool backToMainMenu = false;
						while (!backToMainMenu)
						{
							//check for click
							if (_kbhit())
							{
								break;
							}
							ReadConsoleInput(h_in, all_events, 256, &read_enevt);// получить все события, произошедшие в консоли
							for (int i = 0; i < read_enevt; i++)
							{
								// пройтись по всем событиям
								if (all_events[i].EventType == MOUSE_EVENT)
								{ // если произошло событие мышки
									for (int k = 0; k < 16; k++)
									{
										// Item 1
										if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
											all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
											all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 1 &&
											all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											DeleteArray();
											DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
											LoadFromFile(MAP1);
											DrawMap(block, rope, lader, prize);
											backToMainMenu = true;
											ReadConsoleInput(h_in, all_events, 256, &read_enevt + 100); // +100 because i need change cursor position to avoid continuation of the program 
											break;
										}
										// Item 2
										else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
											all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
											all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 3 &&
											all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											DeleteArray();
											DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
											LoadFromFile(MAP2);
											DrawMap(block, rope, lader, prize);
											backToMainMenu = true;
											ReadConsoleInput(h_in, all_events, 256, &read_enevt + 100); // +100 because i need change cursor position to avoid continuation of the program 
											break;
										}
										// Item 3
										else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
											all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
											all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 5 &&
											all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											DeleteArray();
											DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
											LoadFromFile(MAP3);
											DrawMap(block, rope, lader, prize);
											backToMainMenu = true;
											ReadConsoleInput(h_in, all_events, 256, &read_enevt + 100); // +100 because i need change cursor position to avoid continuation of the program 
											break;
										}
										// Item 4
										else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
											all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
											all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 7 &&
											all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
										{
											DeleteArray();
											getFilesFromDir();
											string *str = new string;
											string *tmpStr = new string;
											*str += "UserMaps/";
											cout << "\n\n   Write map name\n\n\n   ";
											cin >> *tmpStr;
											*str += *tmpStr;
											LoadFromFile(*str);
											DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
											DrawMap(block, rope, lader, prize);
											backToMainMenu = true;
											ReadConsoleInput(h_in, all_events, 256, &read_enevt + 100); // +100 because i need change cursor position to avoid continuation of the program 
											break;
										}

									}
								}
							}
						}
					}
					// Item 4
					else if ((all_events[i].Event.MouseEvent.dwMousePosition.X >= MENU_INDENT &&
						all_events[i].Event.MouseEvent.dwMousePosition.X < MENU_INDENT + 4) &&
						all_events[i].Event.MouseEvent.dwMousePosition.Y == INDENT_TOP + 7 &&
						all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						exit(0);
					}
				}
			}
		}

	}
	for (int i = 0; i < read_enevt; i++)
	{
		
		GotoXY(MENU_INDENT, INDENT_TOP + 1);
		cout << "PLAY";
		GotoXY(MENU_INDENT, INDENT_TOP + 3);
		cout << "CREATE";
		GotoXY(MENU_INDENT, INDENT_TOP + 5);
		cout << "LOAD";
		GotoXY(MENU_INDENT, INDENT_TOP + 7);
		cout << "EXIT";

		if (input == 50)
		{
			DeleteArray();
			GotoXY(MENU_INDENT, INDENT_TOP + 9);
			cout << "Write map name" << endl;
			DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
			ShowCursor(true);
			string *name = new string;
			GotoXY(MENU_INDENT, INDENT_TOP + 10);
			cin >> *name;
			ShowCursor(false);
			GotoXY(INDENT_SIDE / 2 + WIDTH / 2, INDENT_TOP / 2);
			cout << *name;
			DrawSpace(0, INDENT_SIDE - 2, 0, 50);
			CreateMap();
			WriteToFile(*name);
			delete name;
			continue;
		}
		else if (input == 51)
		{
			GotoXY(MENU_INDENT, INDENT_TOP + 1);
			cout << "MAP1  ";
			GotoXY(MENU_INDENT, INDENT_TOP + 3);
			cout << "MAP2  ";
			GotoXY(MENU_INDENT, INDENT_TOP + 5);
			cout << "MAP3  ";
			GotoXY(MENU_INDENT, INDENT_TOP + 7);
			cout << "USER MAP  ";
			for (char input = 0; input != 27; input = _getwch())
			{
				if (input == 49)
				{
					DeleteArray();
					DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
					LoadFromFile(MAP1);
					DrawMap(block, rope, lader, prize);
					break;
				}
				else if (input == 50)
				{
					DeleteArray();
					DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
					LoadFromFile(MAP2);
					DrawMap(block, rope, lader, prize);
					break;
				}
				else if (input == 51)
				{
					DeleteArray();
					DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
					LoadFromFile(MAP3);
					DrawMap(block, rope, lader, prize);
					break;
				}
				else if (input == 52)
				{
					DeleteArray();
					getFilesFromDir();
					string *str = new string;
					string *tmpStr = new string;
					*str += "UserMaps/";
					cout << "\n\n   Write map name\n\n\n   ";
					cin >> *tmpStr;
					*str += *tmpStr;
					LoadFromFile(*str);
					DrawSpace(INDENT_SIDE + 2, WIDTH - INDENT_SIDE - 3, INDENT_TOP + 1, HEIGHT - 2);
					DrawMap(block, rope, lader, prize);
					break;
				}
			}
			DrawSpace(0, INDENT_SIDE - 2, 0, 50);
		}
		else if (input == 52) exit(0);
	}
}

void CreateMap()
{
	MapCreator(block, COUNT_OF_BLOCKS, BLOCK_WIDTH, 1, FULL_SIZE_BLOCK, 0);
	MapCreator(rope, COUNT_OF_ROPES, ROPE_WIDTH, 1, ROPE, 2);
	MapCreator(lader, COUNT_OF_LADERS, LADER_WIDTH, LADER_HEIGHT, LADER, 0);
	MapCreator(prize, COUNT_OF_PRIZE, 1, 1, PRIZE, 1);
}

//Graphics
void DrawBorder()
{
	for (int i = 0; i < HEIGHT + INDENT_TOP; i++)
	{
		if (i >= INDENT_TOP)
		{
			for (int j = 0; j < WIDTH + INDENT_SIDE; j++)
			{
				if (j < WIDTH && j > INDENT_SIDE && (i == INDENT_TOP || i == HEIGHT + INDENT_TOP - 1)) cout << FULL_SIZE_BLOCK;
				else if (j == INDENT_SIDE || j == WIDTH || j == INDENT_SIDE + 1 || j == WIDTH - 1) cout << FULL_SIZE_BLOCK;
				//else if (((i  - INDENT_TOP) % 6 == 0) && j < WIDTH && j > INDENT_SIDE)cout << FULL_SIZE_BLOCK;
				else cout << " ";
			}
		}
		else cout << " ";
		cout << endl;
	}
}

void MapCreator(Sprites arr[], const int countSign, const int width, const int height, const char sprite, int shift)
{
	char* input = new char;
	*input = 0;
	int tmpX = INDENT_SIDE + 2;
	int tmpY = HEIGHT + INDENT_TOP - 7 - shift;
	ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, 0, 0);
	for (int i = countSign; i > 0; *input = _getwch())
	{
		// left
		if (*input == 75 && tmpX > INDENT_SIDE + 2)
		{
			if (FloorCollision(width, height, tmpX - 1, tmpY) && RopeCollision(width, height, tmpX - 1, tmpY) && LaderCollision(width, height, tmpX - 1, tmpY))
			{
				tripleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, LADER, width, height, &tmpX, &tmpY, -1, 0);
			}
			else if (FloorCollision(width, height, tmpX - 1, tmpY) && RopeCollision(width, height, tmpX - 1, tmpY))
			{
				doubleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, width, height, &tmpX, &tmpY, -1, 0);
			}
			else if (FloorCollision(width, height, tmpX - 1, tmpY) && LaderCollision(width, height, tmpX - 1, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else if (FloorCollision(width, height, tmpX - 1, tmpY))
			{
				ChangePos(countSign, FULL_SIZE_BLOCK, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else if (LaderCollision(width, height, tmpX - 1, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else if (RopeCollision(width, height, tmpX - 1, tmpY))
			{
				ChangePos(countSign, ROPE, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else if (LaderCollision(width, height, tmpX - 1, tmpY - LADER_WIDTH) && sprite == PRIZE)
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else if (PrizeCollision(width, height, tmpX - 1, tmpY))
			{
				ChangePos(countSign, PRIZE, sprite, &tmpX, &tmpY, width, height, -1, 0);
			}
			else ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, -1, 0);
		}
		// rigth
		else if (*input == 77 && tmpX + width < WIDTH - 1)
		{
			if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				tripleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, LADER, width, height, &tmpX, &tmpY, 1, 0);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY))
			{
				doubleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, width, height, &tmpX, &tmpY, 1, 0);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && (LaderCollision(width, height, tmpX - width, tmpY)))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, FULL_SIZE_BLOCK, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else if (LaderCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else if (RopeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, ROPE, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else if (LaderCollision(width, height, tmpX - 1, tmpY - LADER_WIDTH) && sprite == PRIZE)
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else if (PrizeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, PRIZE, sprite, &tmpX, &tmpY, width, height, 1, 0);
			}
			else ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, 1, 0);
		}
		// up
		else if (*input == 72 && tmpY > INDENT_TOP + 6)
		{
			if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				tripleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, LADER, width, height, &tmpX, &tmpY, 0, -6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY))
			{
				doubleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, width, height, &tmpX, &tmpY, 0, -6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 0, -6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, FULL_SIZE_BLOCK, sprite, &tmpX, &tmpY, width, height, 0, -6);
			}
			else if (LaderCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 0, -6);
			}
			else if (RopeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, ROPE, sprite, &tmpX, &tmpY, width, height, 0, -6);
			}
			else if (PrizeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, PRIZE, sprite, &tmpX, &tmpY, width, height, 0, -6);
			}
			else ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, 0, -6);
		}
		// down
		else if ((*input == 80 && tmpY < HEIGHT - 3 && sprite != ROPE) || (*input == 80 && tmpY < HEIGHT - 4 && sprite == ROPE))
		{
			if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				tripleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, LADER, width, height, &tmpX, &tmpY, 0, 6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY))
			{
				doubleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, width, height, &tmpX, &tmpY, 0, 6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 0, 6);
			}
			else if (FloorCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, FULL_SIZE_BLOCK, sprite, &tmpX, &tmpY, width, height, 0, 6);
			}
			else if (LaderCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, LADER, sprite, &tmpX, &tmpY, width, height, 0, 6);
			}
			else if (RopeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, ROPE, sprite, &tmpX, &tmpY, width, height, 0, 6);
			}
			else if (PrizeCollision(width, height, tmpX - width, tmpY))
			{
				ChangePos(countSign, PRIZE, sprite, &tmpX, &tmpY, width, height, 0, 6);
			}
			else ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, 0, 6);
		}

		// Enter
		else if (*input == 13)
		{
			if (LaderCollision(width, height, tmpX - 1, tmpY - LADER_WIDTH) && sprite == PRIZE);
			//left move
			else if (
				FloorCollision(width, height, tmpX, tmpY) && !FloorCollision(width, height, tmpX - width, tmpY) ||
				LaderCollision(width, height, tmpX, tmpY) && !LaderCollision(width, height, tmpX - width, tmpY) ||
				RopeCollision(width, height, tmpX, tmpY) && !RopeCollision(width, height, tmpX - width, tmpY) ||
				PrizeCollision(width, height, tmpX, tmpY) && !PrizeCollision(width, height, tmpX - width, tmpY)
				)
			{
				if (tmpX - width > INDENT_SIDE + 2) {
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							SetColor(Black, White);
							GotoXY(tmpX + j, tmpY + i); cout << sprite;
						}
					}
					arr[countSign - i].x = tmpX;
					arr[countSign - i].y = tmpY;
					i -= 1;
					tmpX -= width;
					GotoXY(tmpX, tmpY);
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							SetColor(Red, White);
							GotoXY(tmpX + j, tmpY + i); cout << sprite;
						}
					}
				}
				else {
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							SetColor(Black, White);
							GotoXY(tmpX + j, tmpY + i); cout << sprite;
						}
					}
					arr[countSign - i].x = tmpX;
					arr[countSign - i].y = tmpY;
					i -= 1;
					if ((tmpX == INDENT_SIDE + 2)) tmpX -= tmpX - INDENT_SIDE - 2 - width;
					else tmpX -= tmpX - INDENT_SIDE - 2;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							SetColor(Red, White);
							GotoXY(tmpX + j, tmpY + i); cout << sprite;
						}
					}
				}
			}
			//right move
			else if (tmpX + width + width < WIDTH) {
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
				arr[countSign - i].x = tmpX;
				arr[countSign - i].y = tmpY;
				i -= 1;
				tmpX += width;
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Red, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
			}
			else {
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
				arr[countSign - i].x = tmpX;
				arr[countSign - i].y = tmpY;
				i -= 1;
				tmpX = (WIDTH - 1) + (WIDTH - 4 - tmpX - width * 2);
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Red, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
			}
		}

		// esc
		else if (*input == 27)
		{
			if (FloorCollision(width, height, tmpX, tmpY) && RopeCollision(width, height, tmpX, tmpY))
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
			}
			else if (FloorCollision(width, height, tmpX, tmpY))
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						GotoXY(tmpX + j, tmpY + i); cout << " ";
					}
				}
				for (int j = 0; j < width; j++)
				{
					SetColor(Black, White);
					GotoXY(tmpX + j, tmpY); cout << FULL_SIZE_BLOCK;
				}

			}
			else if (LaderCollision(width, height, tmpX, tmpY))
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << LADER;
					}
				}
			}
			else if (RopeCollision(width, height, tmpX, tmpY) && sprite == LADER)
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << " ";
					}
				}

				for (int j = 0; j < width; j++)
				{
					SetColor(Black, White);
					GotoXY(tmpX + j, tmpY + 4); cout << ROPE;
				}

			}
			else if (RopeCollision(width, height, tmpX, tmpY))
			{
				for (int j = 0; j < width; j++)
				{
					SetColor(Black, White);
					GotoXY(tmpX + j, tmpY); cout << ROPE;
				}
			}
			else if (LaderCollision(width, height, tmpX, tmpY - LADER_WIDTH) && sprite == PRIZE)
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << LADER;
					}
				}
			}
			else if (LaderCollision(width, height, tmpX, tmpY - LADER_WIDTH))
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
			}
			else if (PrizeCollision(width, height, tmpX, tmpY))
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << sprite;
					}
				}
			}
			else {
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						SetColor(Black, White);
						GotoXY(tmpX + j, tmpY + i); cout << " ";
					}
				}
			}
			break;
		}
	}
	delete input;
}

void ChangePos(string look, int* x, int* y, int width, int xChanges, int yChanges)
{
	GotoXY(*x, *y);
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y);
		cout << " ";
	}
	*x += xChanges;
	*y += yChanges;
	GotoXY(*x, *y);
	cout << look;
}

void ChangePos(string look, char spriteToChange, int *x, int *y, int width, int xChanges, int yChanges)
{
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y);
		cout << " ";
	}
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y);
		cout << spriteToChange;
	}
	*x += xChanges;
	*y += yChanges;
	GotoXY(*x, *y);
	cout << look;

}

void ChangePos(const int countSign, const char sprite, int* x, int* y, int width, int height, int xChanges, int yChanges)
{
	GotoXY(*x, *y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Black, White);
			cout << " ";
		}
	}
	*x += xChanges;
	*y += yChanges;
	GotoXY(*x, *y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			GotoXY(*x + j, *y + i);
			SetColor(Red, White);
			cout << sprite;
		}
	}
}

void ChangePos(const int countSign, const char spriteToChange, const char sprite, int* x, int* y, int width, int height, int xChanges, int yChanges)
{
	GotoXY(*x, *y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Black, White);
			cout << " ";
		}
	}
	GotoXY(*x, *y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (spriteToChange == LADER)
			{
				GotoXY(*x + j, *y + i);
				SetColor(Black, White);
				cout << spriteToChange;
			}
			else if (spriteToChange == ROPE && sprite == LADER) {
				GotoXY(*x + j, *y + 4);
				SetColor(Black, White);
				cout << spriteToChange;
			}

			else {
				GotoXY(*x + j, *y);
				SetColor(Black, White);
				cout << spriteToChange;
			}

		}
	}
	*x += xChanges;
	*y += yChanges;
	GotoXY(*x, *y);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Red, White);
			cout << sprite;
		}
	}
}

void doubleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const int width, const int height, int *x, int *y, int xChanges, int yChanges)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Black, White);
			cout << " ";
		}
	}
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y);
		SetColor(Black, White);
		cout << spriteToChange1;
	}
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y + 4);
		SetColor(Black, White);
		cout << spriteToChange2;
	}
	*x += xChanges;
	*y += yChanges;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Red, White);
			cout << charFromArr;
		}
	}
}

void tripleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const char spriteToChange3, const int width, const int height, int* x, int* y, int xChanges, int yChanges)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Black, White);
			cout << " ";
		}
	}
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y);
		SetColor(Black, White);
		cout << spriteToChange1;
	}
	for (int j = 0; j < width; j++)
	{
		GotoXY(*x + j, *y + 4);
		SetColor(Black, White);
		cout << spriteToChange2;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Black, White);
			cout << spriteToChange3;
		}
	}
	*x += xChanges;
	*y += yChanges;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			GotoXY(*x + j, *y + i);
			SetColor(Red, White);
			cout << charFromArr;
		}
	}
}

bool FloorCollision(int width, int height, int x, int y)
{
	for (int i = 0; i < COUNT_OF_BLOCKS; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < BLOCK_WIDTH; k++)
			{
				if ((x + width == block[i].x + k || y + height == block[i].y + j) && y == block[i].y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool RopeCollision(int width, int height, int x, int y)
{
	for (int i = 0; i < COUNT_OF_ROPES; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < ROPE_WIDTH; k++)
			{
				if ((x + width == rope[i].x && y + j == rope[i].y))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool LaderCollision(int width, int height, int x, int y)
{
	for (int i = 0; i < COUNT_OF_LADERS; i++)
	{
		for (int j = 0; j < LADER_HEIGHT; j++)
		{
			for (int k = 0; k < LADER_WIDTH; k++)
			{
				if ((x + width == lader[i].x + k && y + j == lader[i].y))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool PrizeCollision(int width, int height, int x, int y)
{
	for (int i = 0; i < COUNT_OF_PRIZE; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				if ((x + width == prize[i].x && y + j == prize[i].y))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void DrawSpace(int x1, int x2, int y1, int y2)
{
	for (int i = 0; i < y2; i++)
	{
		for (int j = 0; j < x2; j++)
		{
			GotoXY(j + x1, i + y1);
			cout << " ";
		}
	}
}

void DrawMap(Sprites block[], Sprites rope[], Sprites lader[], Sprites prize[])
{
	SetColor(Black, White);
	for (int i = 0; i < COUNT_OF_BLOCKS; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < BLOCK_WIDTH; k++)
			{
				if (block[i].x != 0)
				{
					GotoXY(block[i].x + k, block[i].y + j);
					cout << FULL_SIZE_BLOCK;
				}

			}
		}
	}
	for (int i = 0; i < COUNT_OF_ROPES; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < ROPE_WIDTH; k++)
			{
				if (rope[i].x != 0)
				{
					GotoXY(rope[i].x + k, rope[i].y + j);
					cout << ROPE;
				}
			}
		}
	}
	for (int i = 0; i < COUNT_OF_LADERS; i++)
	{
		for (int j = 0; j < LADER_HEIGHT; j++)
		{
			for (int k = 0; k < LADER_WIDTH; k++)
			{
				if (lader[i].x != 0)
				{
					GotoXY(lader[i].x + k, lader[i].y + j);
					cout << LADER;
				}
			}
		}
	}
	for (int i = 0; i < COUNT_OF_PRIZE; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < 1; k++)
			{
				if (prize[i].x != 0)
				{
					GotoXY(prize[i].x + k, prize[i].y + j);
					cout << PRIZE;
				}
			}
		}
	}
}


//Work with files

void WriteToFile(string name)
{
	ofstream Out;
	fs::create_directories("Maps/UserMaps");
	Out.open("Maps/UserMaps/" + name + ".txt");
	if (!Out.is_open())
	{
		cout << "ERROR!";
	}
	else
	{
		for (int i = 0; i < COUNT_OF_BLOCKS; i++)
		{
			Out << block[i].x << " ";
			Out << block[i].y << " ";
			if (i == COUNT_OF_BLOCKS - 1)
			{
				for (int i = 0; i < COUNT_OF_ROPES; i++)
				{
					Out << rope[i].x << " ";
					Out << rope[i].y << " ";
					if (i == COUNT_OF_ROPES - 1)
					{
						for (int i = 0; i < COUNT_OF_LADERS; i++)
						{
							Out << lader[i].x << " ";
							Out << lader[i].y << " ";
							if (i == COUNT_OF_LADERS - 1)
							{
								for (int i = 0; i < COUNT_OF_PRIZE; i++)
								{
									Out << prize[i].x << " ";
									Out << prize[i].y << " ";
								}
							}
						}
					}
				}
			}
		}
	}
	Out.close();
}

void LoadFromFile(string name)
{
	ifstream Out;
	Out.open("Maps/" + name + ".txt");
	if (!Out.is_open())
	{
		cout << endl << "\t  ERROR";
		Sleep(500);
	}
	else
	{
		for (int i = 0; i < COUNT_OF_BLOCKS; i++)
		{
			Out >> block[i].x;
			Out >> block[i].y;
			if (i == COUNT_OF_BLOCKS - 1)
			{
				for (int i = 0; i < COUNT_OF_ROPES; i++)
				{
					Out >> rope[i].x;
					Out >> rope[i].y;
					if (i == COUNT_OF_ROPES - 1)
					{
						for (int i = 0; i < COUNT_OF_LADERS; i++)
						{
							Out >> lader[i].x;
							Out >> lader[i].y;
							if (i == COUNT_OF_LADERS - 1)
							{
								for (int i = 0; i < COUNT_OF_PRIZE; i++)
								{
									Out >> prize[i].x;
									Out >> prize[i].y;
								}
							}
						}
					}
				}
			}
		}
	}
	Out.close();
}

void getFilesFromDir()
{
	for (const auto & entry : fs::directory_iterator("Maps/UserMaps"))
	{
		cout << "\n\n   " << entry.path() << endl;
	}
}

bool PrizeCollision(int x, int y)
{
	for (int i = 0; i < COUNT_OF_PRIZE; i++)
	{
		if ((x == prize[i].x && y == prize[i].y))
		{
			prize[i].x = 0;
			prize[i].y = 0;
			return true;
		}
	}
	return false;
}

void DeleteArray()
{
	for (int i = 0; i < COUNT_OF_LADERS; i++)
	{
		lader[i].x = 0;
		lader[i].y = 0;
	}
	for (int i = 0; i < COUNT_OF_BLOCKS; i++)
	{
		block[i].x = 0;
		block[i].y = 0;
	}
	for (int i = 0; i < COUNT_OF_ROPES; i++)
	{
		rope[i].x = 0;
		rope[i].y = 0;
	}
	for (int i = 0; i < COUNT_OF_PRIZE; i++)
	{
		prize[i].x = 0;
		prize[i].y = 0;
	}
	for (int i = 0; i < COUNT_OF_ENEMY; i++)
	{
		enemy[i].x = 0;
		enemy[i].y = 0;
	}
}

void EnemyMove(Sprites hero, char*enemyPosition)
{
	int moveCount = 0;
	for (int i = 0; i < COUNT_OF_ENEMY; i++)
	{
		moveCount = 0;
		SetColor(Black, White);

		//left
		if (enemy[i].x == hero.x && enemy[i].x > INDENT_SIDE + 2 && moveCount == 0)
		{
			*enemyPosition = 'l';
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 1))
			{
				if (FloorCollision(1, 1, enemy[i].x, enemy[i].y) && !LaderCollision(1, 1, enemy[i].x - enemy[i].look.width, enemy[i].y))
				{
					//GotoXY(hero.x - 1, hero.y);
					//cout << "s";
				}
				else ChangePos(enemy[i].look.leftLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x + 1, enemy[i].y)) && *enemyPosition == 'r')
			{
				ChangePos(enemy[i].look.rightLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x - 1, enemy[i].y)) && *enemyPosition == 'l')
			{
				ChangePos(enemy[i].look.leftLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else ChangePos(enemy[i].look.leftLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			moveCount = 1;
		}
		if (enemy[i].x > hero.x && enemy[i].x > INDENT_SIDE + 2 && moveCount == 0)
		{
			*enemyPosition = 'l';
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 1))
			{
				if (FloorCollision(1, 1, enemy[i].x, enemy[i].y) && !LaderCollision(1, 1, enemy[i].x - enemy[i].look.width, enemy[i].y))
				{
					//GotoXY(hero.x - 1, hero.y);
					//cout << "s";
				}
				else ChangePos(enemy[i].look.leftLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x + 1, enemy[i].y)) && *enemyPosition == 'r')
			{
				ChangePos(enemy[i].look.rightLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x - 1, enemy[i].y)) && *enemyPosition == 'l')
			{
				ChangePos(enemy[i].look.leftLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			}
			else ChangePos(enemy[i].look.leftLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, -1, 0);
			moveCount = 1;
		}
		// right
		else if (enemy[i].x < hero.x && enemy[i].y != hero.y && enemy[i].x < WIDTH - 1 && moveCount == 0)
		{
			*enemyPosition = 'r';
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - LADER_HEIGHT + 1))
			{
				if (FloorCollision(1, 1, enemy[i].x + enemy[i].look.width, enemy[i].y) && !LaderCollision(1, 1, enemy[i].x + 1, enemy[i].y))
				{
					//GotoXY(hero.x - 1, hero.y);
					//cout << "s";
				}
				else ChangePos(enemy[i].look.rightLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x + 1, enemy[i].y)) && *enemyPosition == 'r')
			{
				ChangePos(enemy[i].look.rightLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 1, 0);
			}
			else if ((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x - 1, enemy[i].y)) && *enemyPosition == 'l')
			{
				ChangePos(enemy[i].look.leftLook, PRIZE, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 1, 0);
			}
			else ChangePos(enemy[i].look.rightLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 1, 0);
			moveCount = 1;
		}
		// up
		if (enemy[i].y > hero.y && enemy[i].x != hero.x && enemy[i].y > INDENT_TOP + 5 && moveCount == 0)
		{
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - LADER_HEIGHT + 1))
			{

				if (*enemyPosition == 'l') {
					if (!LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 1))
					{

					}
					else {
						ChangePos(enemy[i].look.leftLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, -1);
					}
				}
				else if (*enemyPosition == 'r') {
					if (!LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 1))
					{

					}
					else {
						ChangePos(enemy[i].look.rightLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, -1);
					}
				}
			}
			moveCount = 1;
			//else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, -1);
		}
		// down
		if ((enemy[i].y < hero.y&& enemy[i].x != hero.x && enemy[i].y < HEIGHT + 2) && moveCount == 0)
		{
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y + 1) && !LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - LADER_HEIGHT + 1)) //(LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y + 1)
			{
				if (*enemyPosition == 'l') {
					if (!LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 2))
					{

					}
					else ChangePos(enemy[i].look.leftLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
				}
				else if (*enemyPosition == 'r') {
					if (!LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 2))
					{

					}
					else  ChangePos(enemy[i].look.rightLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
				}
			}
			if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - 4))
			{
				if (*enemyPosition == 'r') {
					if (!LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - LADER_HEIGHT + 1))
					{
					}
					else {
						ChangePos(enemy[i].look.rightLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
					}
				}
				if (*enemyPosition == 'l') {
					ChangePos(enemy[i].look.leftLook, LADER, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
				}
			}
			if ((RopeCollision(enemy[i].look.width, 1, enemy[i].x - 2, enemy[i].y - 2)) || (RopeCollision(enemy[i].look.width, 1, enemy[i].x - 1, enemy[i].y - 1)))
			{
				if (*enemyPosition == 'l') {
					if (!RopeCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - 1))
					{

					}
					else ChangePos(enemy[i].look.leftLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
				}
				else if (*enemyPosition == 'r') {
					if (!RopeCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width + 1, enemy[i].y - 1))
					{

					}
					else  ChangePos(enemy[i].look.rightLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
				}
				goto EnemyFall;
			}
			moveCount = 1;
		}
	EnemyFall:
		while (((!FloorCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y + 1) && *enemyPosition == 'r') || ((!FloorCollision(enemy[i].look.width, 1, enemy[i].x - 1, enemy[i].y + 1) && *enemyPosition == 'l'))) && enemy[i].y < HEIGHT + INDENT_TOP - 2)
		{
			if (((PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x + 1, enemy[i].y)) && *enemyPosition == 'r') || (PrizeCollision(enemy[i].x, enemy[i].y) || PrizeCollision(enemy[i].x - 1, enemy[i].y)) && *enemyPosition == 'l')
			{
				//change position
			}
			if ((RopeCollision(enemy[i].look.width, 1, enemy[i].x - 2, enemy[i].y - 1) && *enemyPosition == 'r') || (RopeCollision(enemy[i].look.width, 1, enemy[i].x - 1, enemy[i].y - 1) && *enemyPosition == 'l'))
			{
				if (RopeCollision(enemy[i].look.width, 1, enemy[i].x - 2, enemy[i].y - 1) && !RopeCollision(enemy[i].look.width, 1, enemy[i].x + 1, enemy[i].y - 1) && *enemyPosition == 'r')
				{
					GotoXY(enemy[i].x - 1, enemy[i].y - 1);
					cout << "_";
					break;
				}
				else if (RopeCollision(enemy[i].look.width, 1, enemy[i].x - 1, enemy[i].y - 1) && !RopeCollision(enemy[i].look.width, 1, enemy[i].x - 2, enemy[i].y - 1) && * enemyPosition == 'l')
				{
					GotoXY(enemy[i].x + 1, enemy[i].y - 1);
					cout << "_";
					break;
				}
				else {
					GotoXY(enemy[i].x, enemy[i].y - 1);
					cout << "_";
					GotoXY(enemy[i].x + 1, enemy[i].y - 1);
					cout << "_";
					break;
				}
			}
			else if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - enemy[i].look.width, enemy[i].y - 4))
			{
				break;
			}
			else if (LaderCollision(enemy[i].look.width, 1, enemy[i].x - 1, enemy[i].y - 4))
			{
				break;
			}
			else if (*enemyPosition == 'l')
			{
				Sleep(50);
				ChangePos(enemy[i].look.leftLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
			}
			else if (*enemyPosition == 'r')
			{
				Sleep(50);
				ChangePos(enemy[i].look.rightLook, &enemy[i].x, &enemy[i].y, enemy[i].look.width, 0, 1);
			}
		}
	}


}

void Move()
{
	CreateThread(0, 0, MainMusic, 0, 0, 0);

	for (int i = 0; i < COUNT_OF_ENEMY; i++)
	{
		//SetColor(Red, White);
		enemy[i].look.frontLook = (char)192;
		enemy[i].look.frontLook += (char)219;
		enemy[i].look.frontLook += (char)217;

		enemy[i].look.leftLook = "-";
		enemy[i].look.leftLook += (char)219;

		enemy[i].look.rightLook += (char)219;
		enemy[i].look.rightLook += "-";

		enemy[i].look.width = 2;

		enemy[i].x = INDENT_SIDE + 2 + i * 2;
		enemy[i].y = INDENT_TOP + 4;
	}
	enemy[0].x = INDENT_SIDE + 10;
	enemy[0].y = INDENT_TOP + 4;
	enemy[1].x = INDENT_SIDE + 100;
	enemy[1].y = INDENT_TOP + 4;
	for (int i = 0; i < COUNT_OF_ENEMY; i++)
	{
		//GotoXY(enemy[i].x, enemy[i].y);
		//cout << enemy[i].look.rightLook;
	}
	char *enemyPosition = new char;
	*enemyPosition = 'r';
	/////////////////////////////////////////////

	Sprites hero;
	hero.look.frontLook = (char)192;
	hero.look.frontLook += (char)219;
	hero.look.frontLook += (char)217;

	hero.look.leftLook = "-";
	hero.look.leftLook += (char)219;

	hero.look.rightLook += (char)219;
	hero.look.rightLook += "-";

	hero.look.width = 2;

	hero.x = INDENT_SIDE + 2;
	hero.y = INDENT_TOP + HEIGHT - 10;

	char *position = new char;
	char *input = new char;
	bool *win = new bool;
	int* countPrize = new int;
	*countPrize = 0;
	int *prizeOnMap = new int;
	*prizeOnMap = 0;
	PrizeCount(prizeOnMap);
	*win = false;
	GotoXY(hero.x, hero.y);
	cout << hero.look.rightLook;
	*position = 'r';
	for (; !*win;)
	{
		for (int i = 0; i < COUNT_OF_ENEMY; i++)
		{
			if (enemy[i].x == hero.x && enemy[i].y == hero.y)
			{
				CreateThread(0, 0, Lose, 0, 0, 0);
				return;
			}
		}
		if (_kbhit()) {
			*input = _getch();
			if (((PrizeCollision(hero.x, hero.y) || PrizeCollision(hero.x + 1, hero.y)) && *position == 'r') || (PrizeCollision(hero.x, hero.y) || PrizeCollision(hero.x - 1, hero.y)) && *position == 'l')
			{
				GotoXY(WIDTH + *countPrize + 2, INDENT_TOP + 2);
				cout << PRIZE;
				*countPrize += 1;
				CreateThread(0, 0, TakePrize, 0, 0, 0); // If prize is taken play sound
				if (*countPrize == *prizeOnMap)
				{
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							GotoXY(WIDTH - 1 + j, HEIGHT - 2 + i);
							cout << " ";
						}
					}
				}
			}
			// left
			if (*input == 75 && hero.x > INDENT_SIDE + 2)
			{
				*position = 'l';
				if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 1))
				{
					if (FloorCollision(1, 1, hero.x, hero.y) && !LaderCollision(1, 1, hero.x - hero.look.width, hero.y))
					{
						//GotoXY(hero.x - 1, hero.y);
						//cout << "s";
					}
					else ChangePos(hero.look.leftLook, LADER, &hero.x, &hero.y, hero.look.width, -1, 0);
				}
				else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, -1, 0);
			}
			// if won
			else if ((*input == 77 && *countPrize == *prizeOnMap) && hero.x + hero.look.width == WIDTH - 1 && hero.y > INDENT_TOP + HEIGHT - 5)
			{
				*position = 'r';
				if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - LADER_HEIGHT + 1))
				{
					if (FloorCollision(1, 1, hero.x + hero.look.width, hero.y) && !LaderCollision(1, 1, hero.x + 1, hero.y))
					{
						//GotoXY(hero.x - 1, hero.y);
						//cout << "s";
					}
					else ChangePos(hero.look.rightLook, LADER, &hero.x, &hero.y, hero.look.width, 1, 0);
				}
				else ChangePos(hero.look.rightLook, &hero.x, &hero.y, hero.look.width, 1, 0);
				return;

			}
			// right
			else if (*input == 77 && hero.x + hero.look.width < WIDTH - 1)
			{
				*position = 'r';
				if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - LADER_HEIGHT + 1))
				{
					if (FloorCollision(1, 1, hero.x + hero.look.width, hero.y) && !LaderCollision(1, 1, hero.x + 1, hero.y))
					{
						//GotoXY(hero.x - 1, hero.y);
						//cout << "s";
					}
					else ChangePos(hero.look.rightLook, LADER, &hero.x, &hero.y, hero.look.width, 1, 0);
				}
				else ChangePos(hero.look.rightLook, &hero.x, &hero.y, hero.look.width, 1, 0);

			}

			// up
			else if (*input == 72 && hero.y > INDENT_TOP + 5)
			{
				if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - LADER_HEIGHT + 1))
				{
					if (*position == 'l') {
						if (!LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 1))
						{

						}
						else {
							ChangePos(hero.look.leftLook, LADER, &hero.x, &hero.y, hero.look.width, 0, -1);
						}
					}
					else if (*position == 'r') {
						if (!LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 1))
						{

						}
						else {
							ChangePos(hero.look.rightLook, LADER, &hero.x, &hero.y, hero.look.width, 0, -1);
						}
					}
				}
				//else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, -1);
			}
			// down
			else if ((*input == 80 && hero.y < HEIGHT + 2))
			{
				if ((RopeCollision(hero.look.width, 1, hero.x - 2, hero.y - 2)) || (RopeCollision(hero.look.width, 1, hero.x - 1, hero.y - 1)))
				{
					if (*position == 'l') {
						if (!RopeCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - 1))
						{

						}
						else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, 1);
					}
					else if (*position == 'r') {
						if (!RopeCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - 1))
						{

						}
						else  ChangePos(hero.look.rightLook, &hero.x, &hero.y, hero.look.width, 0, 1);
					}
					goto Fall;
				}
				if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y + 1) && !LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - LADER_HEIGHT + 1)) //(LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y + 1)
				{
					if (*position == 'l') {
						if (!LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 2))
						{

						}
						else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, 1);
					}
					else if (*position == 'r') {
						if (!LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 2))
						{

						}
						else  ChangePos(hero.look.rightLook, &hero.x, &hero.y, hero.look.width, 0, 1);
					}
				}
				else if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - 4))
				{
					if (*position == 'r') {
						if (!LaderCollision(hero.look.width, 1, hero.x - hero.look.width + 1, hero.y - LADER_HEIGHT + 1))
						{
						}
						else {
							ChangePos(hero.look.rightLook, LADER, &hero.x, &hero.y, hero.look.width, 0, 1);
						}
					}
					if (*position == 'l') {
						ChangePos(hero.look.leftLook, LADER, &hero.x, &hero.y, hero.look.width, 0, 1);
					}
				}
				//else ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, 1);
			}
			// enter
			else if (*input == 13)
			{

			}
		Fall:
			while (((!FloorCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y + 1) && *position == 'r') || ((!FloorCollision(hero.look.width, 1, hero.x - 1, hero.y + 1) && *position == 'l'))) && hero.y < HEIGHT + INDENT_TOP - 2)
			{
				if (((PrizeCollision(hero.x, hero.y) || PrizeCollision(hero.x + 1, hero.y)) && *position == 'r') || (PrizeCollision(hero.x, hero.y) || PrizeCollision(hero.x - 1, hero.y)) && *position == 'l')
				{
					GotoXY(WIDTH + *countPrize + 2, INDENT_TOP + 2);
					cout << PRIZE;
					*countPrize += 1;
				}
				if ((RopeCollision(hero.look.width, 1, hero.x - 2, hero.y - 1) && *position == 'r') || (RopeCollision(hero.look.width, 1, hero.x - 1, hero.y - 1) && *position == 'l'))
				{
					if (RopeCollision(hero.look.width, 1, hero.x - 2, hero.y - 1) && !RopeCollision(hero.look.width, 1, hero.x + 1, hero.y - 1) && *position == 'r')
					{
						GotoXY(hero.x - 1, hero.y - 1);
						cout << "_";
						break;
					}
					else if (RopeCollision(hero.look.width, 1, hero.x - 1, hero.y - 1) && !RopeCollision(hero.look.width, 1, hero.x - 2, hero.y - 1) && * position == 'l')
					{
						GotoXY(hero.x + 1, hero.y - 1);
						cout << "_";
						break;
					}
					else {
						GotoXY(hero.x, hero.y - 1);
						cout << "_";
						GotoXY(hero.x + 1, hero.y - 1);
						cout << "_";
						break;
					}
				}
				else if (LaderCollision(hero.look.width, 1, hero.x - hero.look.width, hero.y - 4))
				{
					break;
				}
				else if (LaderCollision(hero.look.width, 1, hero.x - 1, hero.y - 4))
				{
					break;
				}
				else if (*position == 'l')
				{
					Sleep(50);
					ChangePos(hero.look.leftLook, &hero.x, &hero.y, hero.look.width, 0, 1);
				}
				else if (*position == 'r')
				{
					Sleep(50);
					ChangePos(hero.look.rightLook, &hero.x, &hero.y, hero.look.width, 0, 1);
				}
			}
		}
		else {
			Sleep(90);
			EnemyMove(hero, enemyPosition);
		}
	}
	//SetColor(Black, White);
	delete input, win, position, prizeOnMap;
	prizeOnMap = nullptr;
	win = nullptr;
	input = nullptr;
	position = nullptr;
}

void PrizeCount(int *count)
{
	for (int i = 0; i < COUNT_OF_PRIZE; i++)
	{
		if (prize[i].x != 0)
		{
			*count += 1;
		}
	}
}