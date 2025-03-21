#ifndef _CGameObject_HG_
#define _CGameObject_HG_

#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>		// For the quaternions
#include <string>
#include <vector>
#include <queue>

#include "CNameValuePair.h"

#include "IPhysObject.h"	// For the access to things that will update the positions, etc.

#include "IMediator.h"		// Interface for callback

static const unsigned int MAXNUMBEROFDRAWPASSES = 5;

class CGameObject : public IPhysObject
{
public:
	CGameObject();
	virtual ~CGameObject() {};

	void SetMediator( IMediator* pMyMediator );
	
	// From the IPhysObject interface
	virtual void SetPhysProps( CPhysProps &PhysProps );
	virtual CPhysProps GetPhysProps( void );

	// One method to rule them all!!!
	virtual void ReceiveMessage( CNameValuePair NVPair );


	// TODO: Init the min, max, et.c
	glm::vec3 position;
	// Z is "forward", X is "right", Y is "up"
	void updatePositionBasedOnOrientation( glm::vec3 posAdjust, float deltaTime );

	// Z is forward
	glm::vec3 getTarget( glm::vec3 forwardVector );

	// These are Euler angles... 
//	glm::vec3 preRotation;		// aka "rotation"

	// Add sexy quaternions. All the sexy people are doing it... 
	glm::quat qOrientation;		// 
	// Set overwrites the orientation value
	void setOrientationFromEuler( glm::vec3 EulerXYZ );
	// Adjust, well, adjusts it
	void adjustOrientationFromEuler( glm::vec3 EulerXYZ_Adjust );
	void adjustOrientationFromEuler( glm::vec3 EulerXYZ_Adjust, float deltaTime );

	// For now, we are going to COMPLETELY IGNORE THIS
	// (Don't use it at all...)
	glm::vec3 postRotation;		// "Orbiting" another object

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;		// 0 to 1
	float shininess;		// 100

	// Used when there is only one game object (like with text), but we're drawing it many times
	void pushRenderingState(void);
	// Ignores call if nothing on stack
	void popRenderingState(void);


	// Added:
	float alphaTransparency;

	// Added:
	bool bIsSkyBox;

	glm::vec3 debugColour;
	bool bUseDebugColour;	// idea is that when this is true, the debugColour is used without lighthing or texturing


	// Scale to a 1x1x1:
	// scale = 1.0f / maxExtent;
	float scale;
	// These are going to be used for scaling the model
	//float minX, minY, maxX, maxY, minZ, maxZ;
	//float extentX, extentY, extentZ, maxExtent;

	std::string textureName0;
	std::string textureName1;

	unsigned int numberOfTriangles;

	bool bIsVisible;
	bool bIsWireframe;	

	// This was added for the stencil buffer demo. 
	// On render, the "pass number" is used. If this is true, the object is drawn
	bool bDrawOnPass[MAXNUMBEROFDRAWPASSES]; 

	bool bIsALight;
	unsigned int LightID;

	std::string plyModelName;
	GLuint Cached_VBO_ID;				// This is for speed (maybe) so we don't have to "look up" the mesh... dangerous?? likley.


	// This is our LOD model
	GLuint Cached_VBO_ID_LOD[4];		
	unsigned int LOD_NumberOfTriangles[4];
	bool bUseLOD;
	

	unsigned int GetID(void);
	std::string friendlyName;			// For humans to read (as ID is 'meaningless' unsigned int)

	// Our "child" objects
	// We are using pointer, not because they are 
	//	"cool" and "all the sexy people use them", but
	//	because the compiler can't instantiate stack 
	//	variables with contained types.
	std::vector< CGameObject* > vec_pChildObjects;
	virtual void DeleteChildren(void);


	std::string zz_DEBUG_getPositionAsString(void);
	std::string zz_DEBUG_getOrientationAsString(bool bDegrees);

	//std::string textureName;
	//bool bHasTextures;

protected:
	unsigned int m_UniqueID;
	static unsigned int m_NextID;

	CPhysProps m_PhysicalProps;

	IMediator* m_pMyMediator;

	// bInfiniteMass
	//glm::vec3 position;  
	//glm::vec3 positionLast;		
	//glm::vec3 velocity;			   
	//glm::vec3 accel;		
	//bool bInfiniteMass;			

	struct sRenderState
	{
		glm::vec3 position;
		glm::quat oriention;
		bool bIsWireframe;
		glm::vec3 postRotation;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
		float alphaTransparency;
		glm::vec3 debugColour;
		bool bUseDebugColour;
		float scale;
		bool bIsVisible;
	};
	std::queue< sRenderState > m_stackRenderState;

};

#endif
