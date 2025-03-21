#include "CGameObject.h"
#include "CGLColourHelper.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <sstream>

float pickRandZeroToOne(void)
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX - 1);
	return r;
}

//static 
unsigned int CGameObject::m_NextID = 300;		// 4,000,000,000;

CGameObject::CGameObject()
{

	this->m_UniqueID = CGameObject::m_NextID;
	CGameObject::m_NextID++;

	this->bIsWireframe = false;
	this->bIsVisible = true;
	this->bIsALight = false;
	this->LightID = INT_MAX;	// invalid number (we're really going to have 4 billion lights???)

	// If you are a pessimist (or realist)
	this->position = glm::vec3( 0.0f, 0.0f, 0.0f );
//	this->preRotation = glm::vec3( 0.0f, 0.0f, 0.0f );

	// in GLM, one of the constructors for the quaternion is a conversion 
	//	from Euler angles.... (handy!)
	// Our original rotation was 0.0f on all three axes
	glm::vec3 EulerRotationXYZ( 0.0f, 0.0f, 0.0f );
	this->qOrientation = glm::quat( EulerRotationXYZ );

	// What to set the original orientation to??? A mystery, this is (says Yoda)

	this->postRotation = glm::vec3( 0.0f, 0.0f, 0.0f );
	this->scale = 1.0f;
	
	this->diffuse = glm::vec3( 0.0f, 0.0f, 0.0f );	// unnecessary as vec3 constructor sets to all zeros
	this->ambient = glm::vec3( 0.0f, 0.0f, 0.0f );
	this->specular = glm::vec3( 0.0f, 0.0f, 0.0f );
	this->shininess = 1.0f;

	// Added
	this->alphaTransparency = 1.0f;		// 0.0 = fully transparent; 1.0 = fully opaque

	this->bIsSkyBox = false;

	this->debugColour = glm::vec3( 0.0f, 0.0f, 0.0f );	// black
	this->bUseDebugColour = false;

	this->Cached_VBO_ID = 0;

	this->m_pMyMediator = 0;	// Set to zero to start

	this->bUseLOD = false;

	// only draw on the 1st pass
	for ( unsigned int index = 0; index != MAXNUMBEROFDRAWPASSES; index++ )
	{
		this->bDrawOnPass[index] = false;
	}
	this->bDrawOnPass[0] = true;

	return;
}

//	glm::quat qOrientation;		// 
// Set overwrites the orientation value
void CGameObject::setOrientationFromEuler( glm::vec3 EulerXYZ )
{
	// Create an quaterion based on the Euler angles (in c'tor of quat)
	this->qOrientation = glm::quat( EulerXYZ );
	return;
}
// Adjust, well, adjusts it
void CGameObject::adjustOrientationFromEuler( glm::vec3 EulerXYZ_Adjust )
{
	// With Euler, you would do this.... 
	// (if you're being paid by the hour and liked to type a lot...)
//	glm::vec3 angleAnjust = EulerXYZ_Adjust;	
//	this->postRoationXYZ += angleAnjust;

	// "Combine" quaternions means "multiply" (just like matrix math)
	glm::quat qAdjust = glm::quat( EulerXYZ_Adjust );

	// Multiply with the original quaternion.
	// (NOTE: ORDER MATTERS, just like matrix math)
	this->qOrientation *= qAdjust;				// Really is: this->qOrientation = this->qOrientation * qAdjust;

	return;
}

void CGameObject::adjustOrientationFromEuler( glm::vec3 EulerXYZ_Adjust, float deltaTime )
{
	// "Combine" quaternions means "multiply" (just like matrix math)
	glm::quat qAdjust = glm::quat( EulerXYZ_Adjust );

	// But I want to LERP it (i.e. scale it based on the deltaTime, from 0.0f to whatever)
	// The idea is that the 2nd quaterion is applied in proportion to the deltaTime
	glm::quat qNoRotation = glm::quat( 1.0f, 0.0f, 0.0f, 0.0f );	// "Unit" quaternion
	glm::quat qAdjustThisFrame = glm::slerp( qNoRotation, qAdjust, deltaTime );

	this->qOrientation *= qAdjustThisFrame;

	// Or in one go... 
	//this->qOrientation = glm::slerp( this->qOrientation, qAdjust, deltaTime );

	return;
}

// Z is forward  0,0,1
glm::vec3 CGameObject::getTarget( glm::vec3 forwardVector )
{
	glm::vec4 posAdjust4 = glm::vec4( forwardVector, 1.0f );	// Because we're multiplying by a mat4

	glm::mat4 matOrientation = glm::toMat4( this->qOrientation );

	glm::vec4 posTarget = matOrientation * posAdjust4;

	posTarget += glm::vec4(this->position, 0.0f);

	return glm::vec3( posTarget );
}


// Z is "forward", X is "right", Y is "up"
void CGameObject::updatePositionBasedOnOrientation( glm::vec3 posAdjust, float deltaTime )
{
	// Take the rotation values, generate a matrix, then multiply 
	//	that something (the "direction" vector by that)

	// #include <glm/gtc/matrix_transform.hpp> 
	// In our case, +Z is "forward"   0,0,1
	// This is TOTAL MOVEMENT IN 1 SECOND
	glm::vec4 posAdjust4 = glm::vec4( posAdjust, 1.0f );	// Because we're multiplying by a mat4
	// NOW, it's the adjustment for this moment in time
	// This is really sort of a LERP (Linear Interpolation)
//	posAdjust4 *= deltaTime;			
	posAdjust4 = glm::mix( glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), posAdjust4, deltaTime );
	posAdjust4.w = 1.0f;	// The 4th value should always be 1.0f

	// calculate the matrix based on orientation 
	// #include <glm/gtx/quaternion.hpp>	
	glm::mat4 matOrientation = glm::toMat4( this->qOrientation );
//	glm::mat4 matOrientation = glm::rotate( glm::mat4(1.0f), glm::vec4(PI/2.0f, 0.0f, 0.0f) );

	glm::vec4 posAdjustByOrientatoin = matOrientation * posAdjust4;

	// Add that adjustment to position
	this->position += glm::vec3( posAdjustByOrientatoin );
	return;
}


void CGameObject::pushRenderingState(void)
{
	sRenderState curState;
	curState.position = this->position;
	curState.oriention = this->qOrientation;
	curState.bIsWireframe = this->bIsWireframe;
	curState.postRotation = this->postRotation;
	curState.ambient = this->ambient;
	curState.diffuse = this->diffuse;
	curState.specular = this->specular;
	curState.shininess = this->shininess;
	curState.alphaTransparency = this->alphaTransparency;
	curState.debugColour = this->debugColour;
	curState.bUseDebugColour = this->bUseDebugColour;
	curState.scale = this->scale;
	curState.bIsVisible = this->bIsVisible;

	this->m_stackRenderState.push( curState );
	return;
}

void CGameObject::popRenderingState(void)
{
	if ( ! this->m_stackRenderState.empty() )
	{
		sRenderState lastState = this->m_stackRenderState.front();
		
		this->position = lastState.position;
		this->qOrientation = lastState.oriention;
		this->bIsWireframe = lastState.bIsWireframe;
		this->postRotation = lastState.postRotation;
		this->ambient = lastState.ambient;
		this->diffuse = lastState.diffuse;
		this->specular = lastState.specular;
		this->shininess = lastState.shininess;
		this->alphaTransparency = lastState.alphaTransparency;
		this->debugColour = lastState.debugColour;
		this->bUseDebugColour = lastState.bUseDebugColour;
		this->scale = lastState.scale;
		this->bIsVisible = lastState.bIsVisible;
		this->m_stackRenderState.pop();
	}

	return;
}


void CGameObject::SetMediator( IMediator* pMyMediator )
{
	this->m_pMyMediator = pMyMediator;
	return;
}

unsigned int CGameObject::GetID(void)
{
	return this->m_UniqueID;
}

void CGameObject::SetPhysProps( CPhysProps &PhysProps )
{
	this->m_PhysicalProps = PhysProps;
	return;
}

CPhysProps CGameObject::GetPhysProps( void )
{
	return this->m_PhysicalProps;
}

void CGameObject::DeleteChildren(void)
{
	for ( std::vector< CGameObject* >::iterator itChild = this->vec_pChildObjects.begin();
		  itChild != this->vec_pChildObjects.end(); itChild++ )
	{
		// Pointer not zero (0)?
		CGameObject* pTempChildObject = (*itChild);
		if ( pTempChildObject != 0 )
		{
			// Recursively delete all children's children (and so on)
			pTempChildObject->DeleteChildren();
			// Now delete this child
			delete pTempChildObject;
		}
	}
	// There's a vector, but nothing in it
	this->vec_pChildObjects.clear();
	return;
}

// Message: 
// "Name" = "SendMessage"
// "Value" is the ID (friendly name) of target object

// One method to rule them all!!!
void CGameObject::ReceiveMessage( CNameValuePair NVPair )
{
	// Am I a bunny of this name?
	if ( this->friendlyName == "BugsBunny" )
	{
		if ( NVPair.name == "Send message to Darth!" )
		{
			// send a message to Darth Vader
			CNameValuePair messageToDarth;
			messageToDarth.name = "SendMessage";
			messageToDarth.sValue = "DarthVader";
			this->m_pMyMediator->SendMessageToMediator( messageToDarth );
		}//if ( NVPair.name == "Send message to Darth!" )
		else if ( NVPair.name == "FlyAway" )
		{
			this->debugColour = 
				CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_LIGHT_CORAL );
		}
	}//if ( this->friendlyName == "BugsBunny" )


	// Am I Darth Vader?
	if ( this->friendlyName == "DarthVader" )
	{
		// send a message to Darth Vader
		if ( NVPair.name == "FlyAway" )
		{	// Change colour
			this->debugColour 
				= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_FIRE_BRICK );

			// Send a message to the bunny, too
			CNameValuePair mesToBugs;
			mesToBugs.name = "SendMessage";
			mesToBugs.sValue = "BugsBunny";
			this->m_pMyMediator->SendMessageToMediator( mesToBugs );

		}//if ( NVPair.name = "FlyAway" )

	}//if ( this->friendlyName == "DarthVader" )	
	
	
	return;
}

std::string CGameObject::zz_DEBUG_getPositionAsString(void)
{
	std::stringstream ss;
	ss << this->position.x << ", " << this->position.y << ", " << this->position.z;
	return ss.str();
}

std::string CGameObject::zz_DEBUG_getOrientationAsString(bool bDegrees)
{
	glm::vec3 angles = glm::eulerAngles( this->qOrientation );
	if ( bDegrees )
	{
		angles = glm::degrees( angles );
	}
	std::stringstream ss;
	ss << angles.x << ", " << angles.y << ", " << angles.z;
	if ( bDegrees ) { ss << " (degrees)"; }
	else			{ ss << " (radians)"; }

	return ss.str();
}
