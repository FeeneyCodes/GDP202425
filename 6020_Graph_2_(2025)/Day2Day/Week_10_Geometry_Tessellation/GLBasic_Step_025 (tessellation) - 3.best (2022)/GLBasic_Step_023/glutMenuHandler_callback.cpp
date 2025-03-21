#include "global.h"
#include <iostream>

// glutBitmapCharacter

//int glutCreateMenu(void (*func)(int value));
void glutMenuHandler_callback(int value)
{
	switch (value) 
	{
		case 1: // "Draw camera target ball", 0
			std::cout << "Rooms are drawn wireframe" << std::endl;
			::g_bDrawRoomsAsWireframe = true;
			::g_bDrawRooms = true;
			break;
		case 2:
			std::cout << "Rooms are drawn solid" << std::endl;
			::g_bDrawRoomsAsWireframe = false;
			::g_bDrawRooms = true;
			break;
		case 3:
			std::cout << "Rooms are not being drawn" << std::endl;
			::g_bDrawRooms = false;
			break;
		case 4:
			std::cout << "Drawing camera target ball" << std::endl;
			::g_bDrawCameraTargetBall = true;
			break;
		case 5:
			std::cout << "Hiding camera target ball" << std::endl;
			::g_bDrawCameraTargetBall = false;
			break;
		default:
			std::cout << "Selected something I didn't expect" << std::endl;
			break;
	};

	return;
}

