 #pragma once
#include "ConsoleLib.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Settings.h"
#include "fstream"
#include <filesystem>
#include "Sound.h"

using namespace std;

struct Hero {
	string frontLook;
	string leftLook;
	string rightLook;
	int width;
};
struct Sprites {
	int x;
	int y;
	Hero look;
};
void PlayGame();
void CreateMap();

//Graphics
void DrawBorder(); 
void MapCreator(Sprites[], const int, int, int , const char, int);
void ChangePos(string look, int *x, int *y, int width, int, int); // Change hero position
void ChangePos(string look, char spriteToChange,int *x, int *y, int width, int, int); // Change hero position and draw sprites
void ChangePos(const int ,const char, int*, int*, int, int , int, int ); // change position if no collisions
void ChangePos(const int countSign, const char spriteToChange, const char sprite, int* x, int* y, int width, int height, int, int);// change position if have collisions
void doubleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const int width, const int height, int* x , int* y, int xChanges, int yChanges);
void tripleChangePosition(char charFromArr, const char spriteToChange1, const char spriteToChange2, const char spriteToChange3, const int width, const int height, int* x, int* y, int xChanges, int yChanges);
bool FloorCollision(int, int, int, int);
bool RopeCollision(int, int, int, int);
bool LaderCollision(int, int, int, int);
bool PrizeCollision(int, int, int, int);
bool PrizeCollision(int, int); // width delete
void DrawSpace(int,int,int,int);
void DrawMap(Sprites[], Sprites[], Sprites[], Sprites[]);
void DeleteArray();
void PrizeCount(int*);
//Hero move
void Move();
void EnemyMove(Sprites, char*);
//Work with files
void WriteToFile(string);
void LoadFromFile(string);
void getFilesFromDir();