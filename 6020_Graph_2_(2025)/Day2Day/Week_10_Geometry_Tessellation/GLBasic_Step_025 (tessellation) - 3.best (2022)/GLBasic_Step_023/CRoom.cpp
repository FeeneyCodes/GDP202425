#include "CRoom.h"
#include "CGLColourHelper.h"

int randChance( int min, int max )
{
	int randNum = rand()%(max-min + 1) + min;
	return randNum;
}

/*static*/ unsigned int CRoom::m_nextRoomID = 0;


void CRoom::GetListOfRooms( std::vector< CRoom* > &vec_pRooms )
{
	// Am I already in this list?
	if ( this->m_bIsRoomAlreadyPresentInVector( this, vec_pRooms ) )
	{	// Already added
		return;
	}

	// Add itself to the vector
	vec_pRooms.push_back( this );

	// Do I have children?  If so, add them, and call recursively
	
	if ( (this->pRoom_XNeg != NULL) && ( !this->bIsXNegRoom_Parent ) )
	{ 
		//vec_pRooms.push_back ( this->pRoom_XNeg );
		this->pRoom_XNeg->GetListOfRooms( vec_pRooms );
	}

	if ( (this->pRoom_XPos != NULL) && ( !this->bIsXPosRoom_Parent ) )
	{ 
		//vec_pRooms.push_back ( this->pRoom_XPos );
		this->pRoom_XPos->GetListOfRooms( vec_pRooms );
	}
	if ( (this->pRoom_ZPos != NULL) && ( !this->bIsZPosRoom_Parent ) )
	{ 
		//vec_pRooms.push_back ( this->pRoom_ZPos );
		this->pRoom_ZPos->GetListOfRooms( vec_pRooms );
	}
	if ( (this->pRoom_ZNeg != NULL) && ( !this->bIsZNegRoom_Parent ) )
	{ 
		//vec_pRooms.push_back ( this->pRoom_ZNeg );
		this->pRoom_ZNeg->GetListOfRooms( vec_pRooms );
	}
	return;
}

	//enum enumDirection
	//{
	//	ZPOS_NORTH_AWAY,
	//	XPOS_EAST_RIGHT,
	//	XNEG_WEST_LEFT,
	//	ZNEG_SOUTH_TOWARDS
	//};
	//// Will add rooms in whatever direction, as long as they aren't in the vector already
void CRoom::GetListOfRoomsInOneDirection( std::vector< CRoom* > &vec_pRooms, enumDirection direction )
{
	// TODO: Add amazing code here
	// Add self???
	// Only call child rooms in that direction


	return;
}


bool CRoom::m_bIsRoomAlreadyPresentInVector( CRoom* pRoom, std::vector< CRoom* > &vec_pRooms )
{
	for ( int index = 0; index != vec_pRooms.size(); index++ )
	{
		if ( vec_pRooms[index] == pRoom )
		{	// Yes, it's already there
			return true;
		}
	}
	// Didn't find a match
	return false;
}


void CRoom::AddRoom_XNeg( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent /*=0.0f*/ )
{
	this->pRoom_XNeg = new CRoom( pParentRoom->getRoomWidth() );
	this->pRoom_XNeg->position = this->position;
	this->pRoom_XNeg->position.x -= roomWidth;
	// Adjust the y position relative to parent (to show depth)
	this->pRoom_XNeg->position.y = pParentRoom->position.y + yOffsetFromParent;
	// Parent room is XPos (this is XNeg to parent)
	this->pRoom_XNeg->pRoom_XPos = pParentRoom;
	this->pRoom_XNeg->bIsXPosRoom_Parent = true;
	return;
}

void CRoom::AddRoom_XPos( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent /*=0.0f*/ )
{
	this->pRoom_XPos = new CRoom( pParentRoom->getRoomWidth() );
	this->pRoom_XPos->position = this->position;
	this->pRoom_XPos->position.x += roomWidth;
	// Adjust the y position relative to parent (to show depth)
	this->pRoom_XPos->position.y = pParentRoom->position.y + yOffsetFromParent;
	// Parent room is XNeg (this is XPos to parent)
	this->pRoom_XPos->pRoom_XNeg = pParentRoom;
	this->pRoom_XPos->bIsXNegRoom_Parent = true;
	return;
}

void CRoom::AddRoom_ZNeg( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent /*=0.0f*/ )
{
	this->pRoom_ZNeg = new CRoom( pParentRoom->getRoomWidth() );
	this->pRoom_ZNeg->position = this->position;
	this->pRoom_ZNeg->position.z -= roomWidth;
	// Adjust the y position relative to parent (to show depth)
	this->pRoom_ZNeg->position.y = pParentRoom->position.y + yOffsetFromParent;
	// Parent room is ZPos (this is ZNeg to parent)
	this->pRoom_ZNeg->pRoom_ZPos = pParentRoom;
	this->pRoom_ZNeg->bIsZPosRoom_Parent = true;
	return;
}


void CRoom::AddRoom_ZPos( CRoom* pParentRoom, float roomWidth, float yOffsetFromParent /*=0.0f*/ )
{
	this->pRoom_ZPos = new CRoom( pParentRoom->getRoomWidth() );
	this->pRoom_ZPos->position = this->position;
	this->pRoom_ZPos->position.z += roomWidth;
	// Adjust the y position relative to parent (to show depth)
	this->pRoom_ZPos->position.y = pParentRoom->position.y + yOffsetFromParent;
	// Parent room is ZNeg (this is ZPos to parent)
	this->pRoom_ZPos->pRoom_ZNeg = pParentRoom;
	this->pRoom_ZPos->bIsZNegRoom_Parent = true;
	return;
}

/*static*/ int CRoom::percentChanceOfRoomWidth_0_to_100 = CRoom::DEFAULT_PERCENT_CHANCE_OF_ROOM_RATE;

// Recursive function
void CRoom::GenerateChildren( CRoom* pParentRoom, int curDepth, const int maxDepth )
{
	// Have we gone too far (in the recursive call)?
	if ( curDepth > maxDepth )	
	{	// YES!!! Spin the top!!!!!! (inception joke)
		return;
	}

//	const int CHANCEOFROOM = 3;
//	const float ROOMWIDTH = 10.0f;
	// Randomly decide to create each of the four child rooms
	
	// We need to also check if there is already a room (i.e. the parent room)

	if ( this->pRoom_XNeg == NULL )	// No parent room already
	{
		if ( randChance( 0, 100 ) > CRoom::percentChanceOfRoomWidth_0_to_100 )
		{
			//this->pRoom_XNeg = new CRoom();
			//this->pRoom_XNeg->position = this->position;
			//this->pRoom_XNeg->position.x -= ROOMWIDTH;
			this->AddRoom_XNeg( this, this->m_roomWidth, 0.0f );
			this->pRoom_XNeg->colour = glm::vec4( CGLColourHelper::getInstance()->getRandomColourRGB(), 1.0f );
			this->pRoom_XNeg->GenerateChildren( this, curDepth + 1, maxDepth );
		}
	}//if ( this->pRoom_XNeg == NULL )

	if ( this->pRoom_XPos == NULL )// No parent room already
	{
		if ( randChance( 0, 100 ) > CRoom::percentChanceOfRoomWidth_0_to_100 )
		{
			//this->pRoom_XPos = new CRoom();
			//this->pRoom_XPos->position = this->position;
			//this->pRoom_XPos->position.x += ROOMWIDTH;
			this->AddRoom_XPos( this, this->m_roomWidth, 0.0f );
			this->pRoom_XPos->colour = glm::vec4( CGLColourHelper::getInstance()->getRandomColourRGB(), 1.0f );
			this->pRoom_XPos->GenerateChildren( this, curDepth + 1, maxDepth );
		}
	}//if ( this->pRoom_XPos == NULL )

	if ( this->pRoom_ZPos == NULL )// No parent room already
	{
		if ( randChance( 0, 100 ) > CRoom::percentChanceOfRoomWidth_0_to_100 )
		{
			//this->pRoom_ZPos = new CRoom();
			//this->pRoom_ZPos->position = this->position;
			//this->pRoom_ZPos->position.z += ROOMWIDTH;
			this->AddRoom_ZPos( this, this->m_roomWidth, 0.0f );
			this->pRoom_ZPos->colour = glm::vec4( CGLColourHelper::getInstance()->getRandomColourRGB(), 1.0f );
			this->pRoom_ZPos->GenerateChildren( this, curDepth + 1, maxDepth );
		}
	}// if ( this->pRoom_ZPos == NULL )

	if ( this->pRoom_ZNeg == NULL )// No parent room already
	{
		if ( randChance( 0, 100 ) > CRoom::percentChanceOfRoomWidth_0_to_100 )
		{
			//this->pRoom_ZNeg = new CRoom();
			//this->pRoom_ZNeg->position = this->position;
			//this->pRoom_ZNeg->position.z -= ROOMWIDTH;
			this->AddRoom_ZNeg( this, this->m_roomWidth, 0.0f );
			this->pRoom_ZNeg->colour = glm::vec4( CGLColourHelper::getInstance()->getRandomColourRGB(), 1.0f );
			this->pRoom_ZNeg->GenerateChildren( this, curDepth + 1, maxDepth );
		}
	}//if ( this->pRoom_ZNeg == NULL )

	return;
}
