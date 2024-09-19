#include "cPhysics.h"

#include <iostream>

void cPhysics::StepTick(double deltaTime)
{
	// Update the positions, etc. of the object
	for (unsigned int sphereIndex = 0; sphereIndex != this->vecSpheres.size(); sphereIndex++)
	{
		sSphere* pCurrentSphere = this->vecSpheres[sphereIndex];

		pCurrentSphere->physicInfo.position += (pCurrentSphere->physicInfo.velocity * (float)deltaTime);
		//pCurrentSphere->physicInfo.position.x += (pCurrentSphere->physicInfo.velocity.x * (float)deltaTime);
		//pCurrentSphere->physicInfo.position.y += (pCurrentSphere->physicInfo.velocity.y * (float)deltaTime);
		//pCurrentSphere->physicInfo.position.z += (pCurrentSphere->physicInfo.velocity.z * (float)deltaTime);
//		std::cout << pCurrentSphere->physicInfo.position.y << std::endl;

		// Update the position of the associated me
		pCurrentSphere->physicInfo.pAssociatedDrawingMeshInstance->positionXYZ
			= pCurrentSphere->physicInfo.position;
	}

	// Test for collisions
	this->m_CheckForCollisions(deltaTime);

	return;
}

void cPhysics::m_CheckForCollisions(double deltaTime)
{
	// For each sphere, test all the other spheres?



	// For each AABB, test all the other AABBs?


	// For each sphere, test all the AABBs
	for (unsigned int sphereIndex = 0; sphereIndex != this->vecSpheres.size(); sphereIndex++)
	{
		sSphere* pCurrentSphere = this->vecSpheres[sphereIndex];

		for (unsigned int AABBIndex = 0; AABBIndex != this->vecAABBs.size(); AABBIndex++)
		{
			sAABB* pCurrentAABB = this->vecAABBs[AABBIndex];

			if (this->bSphereAABBCollision(pCurrentSphere, pCurrentAABB))
			{
				// They collided! 
				// Oh no... what are we supposed to do now?? 

				// HACK:
				std::cout << "A sphere and AABB collided! Huzzah!" << std::endl;

			}//if (this->bSphereAABBCollision(
		}//for (unsigned int AABBIndex 
	}//for (unsigned int sphereIndex

	return;
}


bool cPhysics::bSphereAABBCollision(sSphere* pSphere, sAABB* pAABB)
{
	// Check if it HASN'T connected
	// Y axis first
	if ((pSphere->physicInfo.position.y - pSphere->radius) > (pAABB->centreXYZ.y + pAABB->extentsXYZ.y))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->physicInfo.position.y + pSphere->radius) < (pAABB->centreXYZ.y - pAABB->extentsXYZ.y))
	{
		// Isn't colliding
		return false;
	}

	// X axis
	if ((pSphere->physicInfo.position.x + pSphere->radius) < (pAABB->centreXYZ.x - pAABB->extentsXYZ.x))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->physicInfo.position.x - pSphere->radius) > (pAABB->centreXYZ.x + pAABB->extentsXYZ.x))
	{
		// Isn't colliding
		return false;
	}

	// Z axis
	if ((pSphere->physicInfo.position.z + pSphere->radius) < (pAABB->centreXYZ.z - pAABB->extentsXYZ.z))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->physicInfo.position.z - pSphere->radius) > (pAABB->centreXYZ.z + pAABB->extentsXYZ.z))
	{
		// Isn't colliding
		return false;
	}

	// Overlapping on ALL axes, so must be colliding

	return true;
}

bool cPhysics::bSphereSphereCollision(sSphere* pA, sSphere* pB)
{
	// TODO: 

	return false;
}

bool cPhysics::bAABB_ABBBCollision(sAABB* pA, sAABB* pB)
{
	// TODO: 

	return false;
}
