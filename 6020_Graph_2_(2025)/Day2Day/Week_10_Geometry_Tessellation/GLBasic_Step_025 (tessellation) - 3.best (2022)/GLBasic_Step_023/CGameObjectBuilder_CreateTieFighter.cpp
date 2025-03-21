#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"
#include <sstream>

bool CGameObjectBuilder::m_CreateTieFighter( CGameObject* &pCreatedObject, std::string &error )
{
	//CGameObject* pBunny = new CGameObject();
	pCreatedObject = new CGameObject();


	CMeshType tempMesh;
	tempMesh.name = "tie";	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
	{	// 
		return false;
	}

	pCreatedObject->scale = 1.0f / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	pCreatedObject->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pCreatedObject->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pCreatedObject->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

	pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
	//pBunny->PickARandomColour();
	pCreatedObject->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_GREEN );
	pCreatedObject->ambient = pCreatedObject->diffuse * 0.2f;
	pCreatedObject->specular = glm::vec3( 1.0f, 1.0f, 1.0f );

		// Create a name including the tie fighter ID
	std::stringstream ss;
	ss << "Tie" << pCreatedObject->GetID();

	pCreatedObject->friendlyName = ss.str();
	//g_vec_pTheObjects.push_back( pBunny );

	return true;
}
