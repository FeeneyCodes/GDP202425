#ifndef _IPhysObject_HG_
#define _IPhysObject_HG_

#include "CPhysProps.h"

// This is the CGameObject interface that the "physics" updater can "see"

class IPhysObject
{
public:
	virtual ~IPhysObject() {};			// Make a virtual destructor on any interface (prevents memory leak)
	// Note the virtual and the "= 0". If ALL of these 
	// methods have this, then it's a "pure virtual" or 
	// "interface class"
	virtual void SetPhysProps( CPhysProps &PhysProps ) = 0;
	virtual CPhysProps GetPhysProps( void ) = 0;
};

#endif

