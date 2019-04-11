#include "CreateMap.h"
Sprites block[COUNT_OF_BLOCKS];
Sprites rope[COUNT_OF_ROPES];
Sprites lader[COUNT_OF_LADERS];
Sprites prize[COUNT_OF_PRIZE];
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
	char input = 0;
	int tmpX = INDENT_SIDE + 2;
	int tmpY = HEIGHT + INDENT_TOP - 7 - shift;

	ChangePos(countSign, sprite, &tmpX, &tmpY, width, height, 0, 0);
	for (int i = countSign; i > 0; input = _getwch())
	{
		// left
		if (input == 75 && tmpX > INDENT_SIDE + 2) 
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
		else if (input == 77 && tmpX + width < WIDTH - 1)
		{
			if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY)&& LaderCollision(width, height, tmpX - width, tmpY))
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
			else if (LaderCollision(width, height, tmpX - 1, tmpY - LADER_WIDTH)&& sprite == PRIZE)
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
		else if (input == 72 && tmpY > INDENT_TOP + 6 ) 
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
		else if ((input == 80 && tmpY < HEIGHT - 2 && sprite != ROPE) || (input == 80 && tmpY < HEIGHT - 4 && sprite == ROPE)) 
		{
			if (FloorCollision(width, height, tmpX - width, tmpY) && RopeCollision(width, height, tmpX - width, tmpY) && LaderCollision(width, height, tmpX - width, tmpY))
			{
				tripleChangePosition(sprite, FULL_SIZE_BLOCK, ROPE, LADER ,width, height, &tmpX, &tmpY, 0, 6);
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
		else if (input == 13 ) 
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
					arr[countSign - i].look = sprite;
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
					arr[countSign - i].look = sprite;
					i -= 1;
					if((tmpX == INDENT_SIDE + 2)) tmpX -= tmpX - INDENT_SIDE - 2 - width;
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
			else if (tmpX + width + width < WIDTH ) {
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
				arr[countSign - i].look = sprite;
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
				arr[countSign - i].look = sprite;
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
		else if (input == 27) 
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
			else if (FloorCollision(width, height, tmpX , tmpY))
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
			else if (LaderCollision(width, height, tmpX , tmpY))
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
			else if (RopeCollision(width, height, tmpX , tmpY) && sprite == LADER)
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
			else if (LaderCollision(width, height, tmpX , tmpY - LADER_WIDTH))
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
			else if (PrizeCollision(width, height, tmpX, tmpY) )
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
}
void ChangePos(const int countSign, const char sprite, int* x, int* y, int width, int height ,int xChanges, int yChanges)
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
void ChangePos(const int countSign, const char spriteToChange ,const char sprite, int* x, int* y, int width, int height, int xChanges, int yChanges)
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
void doubleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const int width, const int height, int *x, int *y, int xChanges,int yChanges)
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
bool FloorCollision(int width ,int height,int x, int y)
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
				if ((x + width == rope[i].x && y + j  == rope[i].y ) )
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
		for (int j = 0; j < height; j++)
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