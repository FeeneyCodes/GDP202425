#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"

bool CGameObjectBuilder::m_CreateBasicBunny( CGameObject* &pCreatedObject, std::string &error )
{
	//CGameObject* pBunny = new CGameObject();
	pCreatedObject = new CGameObject();

	CMeshType tempMeshBunny;
	tempMeshBunny.name = "bunny";	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMeshBunny, error ) )
	{	// Oh no!!!! 
		//std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		return false;
	}

	pCreatedObject->scale = 1.0f / tempMeshBunny.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	pCreatedObject->Cached_VBO_ID = tempMeshBunny.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pCreatedObject->numberOfTriangles = tempMeshBunny.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pCreatedObject->plyModelName = tempMeshBunny.filename;					//"bun_zipper_res3_xyz.ply";

	pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
	//pBunny->PickARandomColour();
	pCreatedObject->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BROWN );
	pCreatedObject->ambient = pCreatedObject->diffuse * 0.2f;
	pCreatedObject->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
	pCreatedObject->friendlyName = "Bugs";
	//g_vec_pTheObjects.push_back( pBunny );

	return true;
}


	