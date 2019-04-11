 #pragma once
#include "ConsoleLib.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Settings.h"

using namespace std;

struct Sprites {
	int x;
	int y;
	char look;
};

void PlayGame();
void DrawBorder(); 
void MapCreator(Sprites[], const int, int, int , const char, int);
void ChangePos(const int ,const char,int*, int*, int, int , int, int ); // Draw empty elements
void ChangePos(const int countSign, const char spriteToChange, const char sprite, int* x, int* y, int width, int height, int, int);// Draw elements
void doubleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const int width, const int height, int* x , int* y, int xChanges, int yChanges);
void tripleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const char spriteToChange3, const int width, const int height, int* x, int* y, int xChanges, int yChanges);
bool FloorCollision(int, int, int, int);
bool RopeCollision(int, int, int, int);
bool LaderCollision(int, int, int, int);
bool PrizeCollision(int, int, int, int);
