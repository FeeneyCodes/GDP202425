#ifndef _CRoom_HG_
#define _CRoom_HG_

#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>

#include <vector>


class CRoom
{
public:
	CRoom(float roomWidth) : 
		pRoom_XNeg(NULL), pRoom_XPos(NULL), 
		pRoom_ZPos(NULL), pRoom_ZNeg(NULL)
	{
		this->colour = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		this->m_roomWidth = roomWidth;
		this->bIsXNegRoom_Parent = false;
		this->bIsXPosRoom_Parent = false;
		this->bIsZPosRoom_Parent = false;
		this->bIsZNegRoom_Parent = false;
		this->m_RoomID = CRoom::m_nextRoomID;	CRoom::m_nextRoomID++;
	};
	glm::vec3 position;			// xyz  Hey there!!! 
	glm::vec4 colour;

	unsigned int getRoomID(void)	{ return this->m_RoomID; }

	float getRoomWidth(void) { return this->m_roomWidth; }

	static const int DEFAULT_PERCENT_CHANCE_OF_ROOM_RATE = 30;
	static int percentChanceOfRoomWidth_0_to_100;// = DEFAULT_PERCENT_CHANCE_OF_ROOM_RATE;

	//                 North (+ve z)
	//               
	//                +-------------+
	//                |             |
	// West (-ve X)   |             |   East (+ve X)
	//                |             |
	//                +-------------+
	//               
	//                 South (-ve Z)

	// Assume that zero (NULL) means there's no room in that direction
	CRoom* pRoom_XNeg;		// West
	CRoom* pRoom_XPos;		// East
	CRoom* pRoom_ZPos;		// South
	CRoom* pRoom_ZNeg;		// North

	bool bIsXNegRoom_Parent;
	bool bIsXPosRoom_Parent;
	bool bIsZPosRoom_Parent;
	bool bIsZNegRoom_Parent;

	// Recursive function
	void GenerateChildren( CRoom* pParentRoom, int curDepth, const int maxDepth );

	void AddRoom_XNeg( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent = 0.0f );
	void AddRoom_XPos( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent = 0.0f );
	void AddRoom_ZNeg( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent = 0.0f );
	void AddRoom_ZPos( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent = 0.0f );

	void GetListOfRooms( std::vector< CRoom* > &vec_pRooms );

	enum enumDirection
	{
		ZPOS_NORTH_AWAY,
		XPOS_EAST_RIGHT,
		XNEG_WEST_LEFT,
		ZNEG_SOUTH_TOWARDS
	};
	// Will add rooms in whatever direction, as long as they aren't in the vector already
	void GetListOfRoomsInOneDirection( std::vector< CRoom* > &vec_pRooms, enumDirection direction );
private:
	CRoom() {};
	float m_roomWidth;

	unsigned int m_RoomID;
	static unsigned int m_nextRoomID;

	bool m_bIsRoomAlreadyPresentInVector( CRoom* pRoom, std::vector< CRoom* > &vec_pRooms );
};

// Implementation is in GenerateMaze.cpp
void GenerateMaze( CRoom* pStartingRoom, int maxDepth );

#endif