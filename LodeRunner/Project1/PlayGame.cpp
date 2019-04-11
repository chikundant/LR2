#include "CreateMap.h"
#include "CreateMap.cpp"
using namespace std;



void PlayGame()
{
	DrawBorder();
	MapCreator(block, COUNT_OF_BLOCKS, BLOCK_WIDTH, 1, FULL_SIZE_BLOCK, 0);
	MapCreator(rope, COUNT_OF_ROPES, ROPE_WIDTH, 1, ROPE, 2);
	MapCreator(lader, COUNT_OF_LADERS, LADER_WIDTH, LADER_HEIGHT, LADER, 0);
	MapCreator(prize, COUNT_OF_PRIZE, 1, 1, PRIZE, 1);

}
