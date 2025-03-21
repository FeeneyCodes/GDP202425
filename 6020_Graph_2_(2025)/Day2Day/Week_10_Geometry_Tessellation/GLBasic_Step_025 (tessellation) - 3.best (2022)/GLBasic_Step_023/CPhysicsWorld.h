#ifndef _CPhysicsWorld_HG_
#define _CPhysicsWorld_HG_

// This class could handle updating all the pysical representations of the objects. 

#include <vector>
#include "IPhysObject.h"

class CPhysicsWorld
{
public:
	void AddPhysicalObject( IPhysObject* &PhysicsObject );
	void AddPhysicalObjects( std::vector< IPhysObject* > &vecPhysicsObjects );
	void GetPhysicalObjects( std::vector< IPhysObject* > &vecPhysicsObjects );
	void ClearAllObjects(void);
	void IntegrationStep( float deltaTime );
	// Stolen from the Erison book
	//Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c);
	// Point is really a 3D point in space (x,y,z)
	glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
	// Same as above, but will also indicate if the point is "above" the triangle 
	glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c, bool &bIsAboveTriangle);

private:
	std::vector< IPhysObject* > m_vecPhysicsObjects;
};

#endif
