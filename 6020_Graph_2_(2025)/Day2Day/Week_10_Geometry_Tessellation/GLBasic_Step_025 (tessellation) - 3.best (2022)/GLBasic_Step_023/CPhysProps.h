#ifndef _CPhysProps_HG_
#define _CPhysProps_HG_

#include <glm\glm.hpp>

// These are some of the physical properties of the object
// the ones that are only really needed by the Physics updater thingy

class CAABB
{
public:
	CAABB() {};
	~CAABB() {}
	glm::vec3 minXYZ;
	glm::vec3 maxXYZ;
};

class CPhysProps		// for "Physical Properties"
{
public:
	// Render doesn't need to be able to update these
	CPhysProps() : bInfiniteMass(false), GameObjectID(0) {};
	glm::vec3 position;  // Both render and physics need this...
	glm::vec3 positionLast;		// Previous location a "moment" ago
	glm::vec3 velocity;			// velocity_X, velocity_Y, velocity_Z     
	glm::vec3 accel;		// accel_X, accel_Y, accel_Z;
	bool bInfiniteMass;			// If this is infinite, then the physics integrator ignores the updates on this
	unsigned int GameObjectID;	// To be able to match up to the game objects
};

#endif

