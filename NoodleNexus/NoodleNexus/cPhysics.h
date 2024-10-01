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
			this->bDoesntMove = false;
		}		
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		// If true, then we skip the integration step
		bool bDoesntMove;	// i.e. doesn't move
		// TODO: 
//		float mass;
//		float inverseMass;		// Usually this is what we keep

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
			this->pPhysicInfo = new sPhysInfo();
		}
		~sSphere()
		{
			delete this->pPhysicInfo;
		}
		glm::vec3 centre;
		float radius;
		sPhysInfo* pPhysicInfo = NULL;
//		unsigned int uniqueID;
		//unsigned int matchingMeshID;
	};

	struct sAABB		// Axis Aligned Bounding Box
	{
		sAABB()
		{
			this->centreXYZ = glm::vec3(0.0f);
			this->minXYZ = glm::vec3(0.0f);
			this->maxXYZ = glm::vec3(0.0f);
			this->pPhysicInfo = new sPhysInfo();
		}
		~sAABB()
		{
			delete this->pPhysicInfo;
		}
		glm::vec3 centreXYZ;
		glm::vec3 minXYZ;
		glm::vec3 maxXYZ;

		// Calculate the other stuff
		// TODO:
		glm::vec3 getExtentsXYZ(void);	//	glm::vec3 extentsXYZ;	// height, width, depth

//		glm::vec3 getMinXYZ(void);
//		glm::vec3 getMaxYYZ(void);
//		glm::vec3 getHalfExtent(void);	// Distance from centre on that axis
		//
		sPhysInfo* pPhysicInfo = NULL;
	
		//		unsigned int uniqueID;
	};

	// Other types soon, likely
	// struct sPlane
	// struct sCapsule
	// etc.


	std::vector<sSphere*> vecSpheres;
	std::vector<sAABB*> vecAABBs;

//	std::vector<sPhysicObject*> vecAllTheObjects;
//	std::vector< sPhysInfo* > vec_pPhysInfos;

	// Called every time we want a collision detection step
	void StepTick(double deltaTime);

	// Check to see if they collided. 
	// We likely need other information, like where, when, etc.
	bool bSphereAABBCollision(sSphere* pSphere, sAABB* pAABB);
	bool bSphereSphereCollision(sSphere* pA, sSphere* pB);
	bool bAABB_ABBBCollision(sAABB* pA, sAABB* pB);


	// Could do this... like a callback or event 
	// This is 100% OK to do this
//	void SphereAABBCollided(sSphere* pSphere, sAABB* pAABB);

	// Here's a list of all the event that happened in the last step
	// 
	// These represent a collision "event" 
	struct sCollision_SphereAABB
	{
		double timeOfCollision;

		sSphere* pTheSphere;
		sAABB* pTheAABB;
		glm::vec3 collisionWorldPoint;
		float nearestDistance;
		glm::vec3 sphereVelocity;	glm::vec3 spherePosition;	
		// velocity will also give direction
		// glm::vec3 sphereDirection;

		glm::vec3 AABB_Velocity;	glm::vec3 AABB_Position;	
		// velocity will also give direction
		// glm::vec3 sphereDirection;
	};
	std::vector<sCollision_SphereAABB> vec_SphereAABB_Collisions;

	struct sCollision_SphereSphere
	{
		double timeOfCollision;

		sSphere* pSpheres[2];
		glm::vec3 collisionWorldPoint;
		glm::vec3 velocities[2];	
		glm::vec3 psition[2];	
		// velocity will also give direction
		// glm::vec3 sphereDirection;
	};
	std::vector<sCollision_SphereAABB> vec_SphereSphere_Collisions;

private:
	void m_CheckForCollisions(double deltaTime);

};
