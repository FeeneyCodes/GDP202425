// GenerateMaze.cpp

#include "CRoom.h"

void GenerateMaze( CRoom* pStartingRoom, int maxDepth )
{

	pStartingRoom->colour = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
	
	// Call rooms to generate new rooms
	int curDepth = 0;		// 

	pStartingRoom->GenerateChildren( pStartingRoom, curDepth, maxDepth );


	return;
}