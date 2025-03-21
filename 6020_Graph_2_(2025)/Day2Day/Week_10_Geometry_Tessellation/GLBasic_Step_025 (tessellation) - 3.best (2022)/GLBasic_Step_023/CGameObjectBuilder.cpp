#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"
#include <sstream>

CGameObjectBuilder::CGameObjectBuilder(	CModelTypeManager* pModelTypeManager )
{
	this->m_pModelTypeManager = pModelTypeManager;
	return;
}



		// bTreatTypeAsMeshName == true, then the "type" is simply the mesh name
// bTreatTypeAsMeshName == true, then the "type" is simply the mesh name
	// bTreatTypeAsMeshName == true, then the "type" is simply the mesh name
bool CGameObjectBuilder::CreateGameObject( 
	std::string type, CGameObject* &pCreatedObject, bool bTreatTypeAsMeshName, std::string &error, 
	float scale /*=1.0f*/, bool bTreatScaleAsBoundingBoxSize /*=false*/  ) 
{
	if ( bTreatTypeAsMeshName )
	{
		// Just create the model from the basic mesh
		return this->m_CreateBasicObjectFromMesh( type, pCreatedObject, scale, bTreatScaleAsBoundingBoxSize, error );
	}

	// Or we want to create something more complex...
	if ( type == "Basic Bunny" )
	{
		return this->m_CreateBasicBunny( pCreatedObject, error );
	}
	else if ( type == "Bunny with tie" )
	{
		return this->m_CreateBunnyWithTieFighter( pCreatedObject, error );
	}
	else if ( type == "Tie Fighter" )
	{
		return this->m_CreateTieFighter( pCreatedObject, error );
	}
	else if ( type == "Cylons, yikes!" )
	{
		this->CreateSwamOfCylons( pCreatedObject );
		// Note that we can call anything we want, even methods that are completely different from the ones above
		return true;
	}
	// See if it's a light. See that this is a more complex parameter
	// We can pass "LightXX" to create a "light" object with the "XX" being the number
	if ( type.length() >= 5 )
	{	// Get first five character
		if ( type.substr( 0, 5 ) == "Light" )
		{	// It's a light
			std::stringstream ssLightID;
			ssLightID << type.substr( 5, type.length() - 5 );
			unsigned int lightID;
			ssLightID >> lightID;
			return this->m_CreateALight( pCreatedObject, lightID, error );
		}
	}// if ( type.length() >= 5 )


	// What are you talking about...?
	return false;
}

bool CGameObjectBuilder::m_CreateBasicObjectFromMesh( std::string meshName, CGameObject* &pCreatedObject, float scale, bool bTreatScaleAsBoundingBoxSize, std::string &error )
{
	//CGameObject* pBunny = new CGameObject();
	pCreatedObject = new CGameObject();

	CMeshType tempMesh;
	tempMesh.filename = meshName;	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByFileName( tempMesh, error ) )
	{	// Oh no!!!! 
		//std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		return false;
	}

	pCreatedObject->scale = scale;	
	// Scale it based on a bounding box?
	if ( bTreatScaleAsBoundingBoxSize )
	{
		pCreatedObject->scale = scale / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	}

	pCreatedObject->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pCreatedObject->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pCreatedObject->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

	pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
	//pBunny->PickARandomColour();
	pCreatedObject->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BROWN );
	pCreatedObject->ambient = pCreatedObject->diffuse * 0.2f;
	pCreatedObject->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
	pCreatedObject->friendlyName = "UNKNOWN: Created from mesh file name";
	//g_vec_pTheObjects.push_back( pBunny );

	return true;
}
