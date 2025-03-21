#include "CPhysicsWorld.h"
#include <algorithm>

void CPhysicsWorld::AddPhysicalObjects( std::vector< IPhysObject* > &vecPhysicsObjects )
{
	// TODO
	return;
}

void CPhysicsWorld::AddPhysicalObject( IPhysObject* &PhysicsObject )
{
	// Might want to check to see if this object is already in the simulation?
	// TODO
	return;
}

void CPhysicsWorld::GetPhysicalObjects( std::vector< IPhysObject* > &vecPhysicsObjects )
{
	vecPhysicsObjects.clear();
	// You could use a loop here, too (this is from the algorithm library, and it calls push_back on a vector) 
	std::copy( this->m_vecPhysicsObjects.begin(), this->m_vecPhysicsObjects.end(), vecPhysicsObjects.begin() );

	return;
}

void CPhysicsWorld::ClearAllObjects(void)
{
	for ( unsigned int index = 0; index != this->m_vecPhysicsObjects.size(); index++ )
	{
		delete this->m_vecPhysicsObjects[index];
	}
	this->m_vecPhysicsObjects.clear();
	return;
}

void CPhysicsWorld::IntegrationStep( float deltaTime )
{
	//for ( int index = 0; index != ::g_p_vecGameObjects.size(); index++ )
	for ( int index = 0; index != this->m_vecPhysicsObjects.size(); index++ )
	{
		//CGameObject* pCurObject = ::g_p_vecGameObjects[index];
		IPhysObject* pCurObject = this->m_vecPhysicsObjects[index];

		CPhysProps tempProps  = pCurObject->GetPhysProps();

		// What's the change in velocity in this step in time
		glm::vec3 deltaVelocity;
		//deltaVelocity.x = pCurObject->accel.x * deltaTime;
		//deltaVelocity.y = pCurObject->accel.y * deltaTime;
		//deltaVelocity.z = pCurObject->accel.z * deltaTime;
		deltaVelocity.x = tempProps.accel.x * deltaTime;
		deltaVelocity.y = tempProps.accel.y * deltaTime;
		deltaVelocity.z = tempProps.accel.z * deltaTime;

		//pCurObject->velocity.x += deltaVelocity.x;
		//pCurObject->velocity.y += deltaVelocity.y;
		//pCurObject->velocity.z += deltaVelocity.z;
		tempProps.velocity.x += deltaVelocity.x;
		tempProps.velocity.y += deltaVelocity.y;
		tempProps.velocity.z += deltaVelocity.z;


		// Move it "forward" based on the velocity
		glm::vec3 deltaDistance;
		//distance.x = pCurObject->velocity.x * deltaTime;
		//distance.y = pCurObject->velocity.y * deltaTime;
		//distance.z = pCurObject->velocity.z * deltaTime;
		deltaDistance.x = tempProps.velocity.x * deltaTime;
		deltaDistance.y = tempProps.velocity.y * deltaTime;
		deltaDistance.z = tempProps.velocity.z * deltaTime;

		// Update position from distance
		//pCurObject->position.x += distance.x;
		//pCurObject->position.y += distance.y;
		//pCurObject->position.z += distance.z;
		tempProps.position.x += deltaDistance.x;
		tempProps.position.y += deltaDistance.y;
		tempProps.position.z += deltaDistance.z;

		// What if the bunny hits the "ground" (-4.0f is where the "ground" is)
		//if ( pCurObject->position.y <= -4.0f )
		//{
		//	pCurObject->velocity.y = -( pCurObject->velocity.y * 0.90f );
		//	//pCurObject->accel.y = 0.0f;
		//}
		if ( tempProps.position.y <= -4.0f )
		{
			tempProps.velocity.y = -( tempProps.velocity.y * 0.90f );
			//pCurObject->accel.y = 0.0f;
		}

		// Now pass these updated physical properties back into the object
		pCurObject->SetPhysProps( tempProps );
	}
	return;
}

//Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
glm::vec3 CPhysicsWorld::ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c, bool &bIsAboveTriangle)
{
	bIsAboveTriangle = false;

    // Check if P in vertex region outside A
    glm::vec3 ab = b - a;		// Vector ab = b - a;
    glm::vec3 ac = c - a;		// Vector ac = c - a;
    glm::vec3 ap = p - a;		// Vector ap = p - a;
    float d1 = glm::dot(ab, ap);		// Dot(ab, ap); 
    float d2 = glm::dot(ac, ap);		// Dot(ac, ap);
    if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)

    // Check if P in vertex region outside B
    glm::vec3 bp = p - b;				//Vector bp = p - b;
    float d3 = glm::dot(ab, bp);		//Dot(ab, bp);
    float d4 = glm::dot(ac, bp);		//Dot(ac, bp);
    if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)

    // Check if P in edge region of AB, if so return projection of P onto AB
    float vc = d1*d4 - d3*d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
        float v = d1 / (d1 - d3);
        return a + v * ab; // barycentric coordinates (1-v,v,0)
    }

    // Check if P in vertex region outside C
    glm::vec3 cp = p - c;		// Vector cp = p - c;
    float d5 = glm::dot(ab, cp);			// Dot(ab, cp);
    float d6 = glm::dot(ac, cp);			// Dot(ac, cp);
    if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)

    // Check if P in edge region of AC, if so return projection of P onto AC
    float vb = d5*d2 - d1*d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
        float w = d2 / (d2 - d6);
        return a + w * ac; // barycentric coordinates (1-w,0,w)
    }

    // Check if P in edge region of BC, if so return projection of P onto BC
    float va = d3*d6 - d5*d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
        float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        return b + w * (c - b); // barycentric coordinates (0,1-w,w)
    }

    // P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	bIsAboveTriangle = true;
    float denom = 1.0f / (va + vb + vc);
    float v = vb * denom;
    float w = vc * denom;
    return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f - v - w
}

// Same as above, but will also indicate if the point is "above" the triangle 
glm::vec3 CPhysicsWorld::ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	bool bIsAboveTriangle = false;
	return this->ClosestPtPointTriangle( p, a, b, c, bIsAboveTriangle );
}

