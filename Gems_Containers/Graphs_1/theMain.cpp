#include "cMazeMaker.h"
#include <vector>

struct sRoom_1
{
	sRoom_1* pUp = NULL;
	sRoom_1* pDown = NULL;
	sRoom_1* pLeft = NULL;
	sRoom_1* pRight = NULL;
	unsigned int rowNum = 0;
	unsigned int colNum = 0;
};

struct sRoom_2
{
	std::vector<sRoom_2*> vec_pConnectedRooms;
	unsigned int rowNum = 0;
	unsigned int colNum = 0;
};

struct sRoom_3
{
	enum eDirections { UP /*=0*/, DOWN, LEFT, RIGHT };
	sRoom_3* pRooms[4];
};


int main_MAZE()
{

	cMazeMaker myMaze;
	myMaze.GenerateMaze(10, 10);

	myMaze.PrintMaze();

	// 
	sRoom_1* pEntrance = new sRoom_1();
	// Assuming I have a good node here

//	XXXXXXXXX
//	X   X   X
//	X XXX X X
//	X     X
//	X XX XXXX
//	X       X
//	XXXXXXX X
//	X       X
//	XXX XXXXX

	char TheMaze[10][10];

	return 0;
}