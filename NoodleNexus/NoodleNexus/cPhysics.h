#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>
// 
#include "sMesh.h"

class cPhysics
{
public:

	// Info for the physics movement, etc.
	struct sPhysInfo
	{
		sPhysInfo()
		{
			this->position = glm::vec3(0.0f);
			this->acceleration = glm::vec3(0.0f);
			this->velocity = glm::vec3(0.0f);
		}		
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		bool bDoesntMove;	// i.e. doesn't move

		// The drawing mesh that's connected to this physics object
		sMesh* pAssociatedDrawingMeshInstance = NULL;

		// Maybe other things, too
//		float mass;
//		glm::vec3 orientation;
	};

	// Types of primatives
	struct sSphere 
	{
		sSphere() 
		{
			this->centre = glm::vec3(0.0f);
			this->radius = 0.0f;
		}
		glm::vec3 centre;
		float radius;
		sPhysInfo physicInfo;
		unsigned int uniqueID;
		//unsigned int matchingMeshID;
	};

	struct sAABB		// Axis Aligned Bounding Box
	{
		glm::vec3 centreXYZ;
		glm::vec3 extentsXYZ;	// height, width, depth
		// Calculate the other stuff
		// TODO:
		glm::vec3 getMinXYZ(void);
		glm::vec3 getMaxYYZ(void);
		glm::vec3 getHalfExtent(void);	// Distance from centre on that axis
		//
		sPhysInfo physicInfo;
	};

	// Other types soon, likely

	std::vector<sSphere*> vecSpheres;
	std::vector<sAABB*> vecAABBs;

//	std::vector<sPhysicObject*> vecAllTheObjects;

	// Called every time we want a collision detection step
	void StepTick(double deltaTime);

	// Check to see if they collided. 
	// We likely need other information, like where, when, etc.
	bool bSphereAABBCollision(sSphere* pSphere, sAABB* pAABB);
	bool bSphereSphereCollision(sSphere* pA, sSphere* pB);
	bool bAABB_ABBBCollision(sAABB* pA, sAABB* pB);

private:
	void m_CheckForCollisions(double deltaTime);
};
