#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"

bool CGameObjectBuilder::m_CreateBunnyWithTieFighter( CGameObject* &pCreatedObject, std::string &error )
{
	CGameObject* pBunny = new CGameObject();
	pBunny = new CGameObject();
	{
		// Add some objects to the vector....

		CMeshType tempMeshBunny;
		tempMeshBunny.name = "bunny";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMeshBunny, error ) )
		{	// Oh no!!!! 
			return false;
		}

		pBunny->scale = 1.0f / tempMeshBunny.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pBunny->Cached_VBO_ID = tempMeshBunny.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pBunny->numberOfTriangles = tempMeshBunny.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pBunny->plyModelName = tempMeshBunny.filename;					//"bun_zipper_res3_xyz.ply";

		pBunny->bIsWireframe = false;	// Now it's wireframe...
		//pBunny->PickARandomColour();
		pBunny->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BROWN );
		pBunny->ambient = pBunny->diffuse * 0.2f;
		pBunny->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pBunny->friendlyName = "Bugs";
		//g_vec_pTheObjects.push_back( pBunny );
	}


	CMeshType tempMeshTie;
	tempMeshTie.name = "tie";	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMeshTie, error ) )
	{	// Oh no!!!! 
		delete pBunny;
		return false;
	}	
	{
		CGameObject* pTie = new CGameObject();
		pTie = new CGameObject();


		pTie->scale = 0.5f / tempMeshTie.pPlyFile->getMaxExtent();		// meshTypes[TIE_FIGHTER_ID].maxExtent;
		pTie->Cached_VBO_ID = tempMeshTie.GL_VBO_ID;						//  meshTypes[TIE_FIGHTER_ID].VBO_ID;
		pTie->numberOfTriangles = tempMeshTie.pPlyFile->GetNumberOfElements();	// meshTypes[TIE_FIGHTER_ID].numberOfTriangles;
		pTie->plyModelName = tempMeshTie.filename;						//"tie.ply";
	
		pTie->position.x = -0.5f;
		//pTie->PickARandomColour();
		pTie->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_RED );
		pTie->ambient = pTie->diffuse * 0.2f;
		pTie->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pTie->shininess = 1.0f;
		pTie->bIsWireframe = true;
		pTie->friendlyName = "Tie#1";
		//g_vec_pTheObjects.push_back( pTie );
		pBunny->vec_pChildObjects.push_back( pTie );
	}

	pCreatedObject = pBunny;

	return true;
}
