#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"

void CGameObjectBuilder::CreateSwamOfCylons( CGameObject* &pCreatedObject )
{
	std::string error;

	CGameObject* pCow = new CGameObject();
	pCow = new CGameObject();
	{
		// Add some objects to the vector....

		CMeshType tempMeshCow;
		tempMeshCow.name = "Bessy";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMeshCow, error ) )
		{	// Oh no!!!! 
			return;
		}

		pCow->scale = 1.0f / tempMeshCow.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pCow->Cached_VBO_ID = tempMeshCow.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pCow->numberOfTriangles = tempMeshCow.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pCow->plyModelName = tempMeshCow.filename;					//"bun_zipper_res3_xyz.ply";

		pCow->bIsWireframe = false;	// Now it's wireframe...
		//pBunny->PickARandomColour();
		pCow->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BROWN );
		pCow->ambient = pCow->diffuse * 0.2f;
		pCow->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pCow->friendlyName = "Super Cow";
		pCow->scale = 3.0f;
		//g_vec_pTheObjects.push_back( pBunny );
	}


	CMeshType tempMeshTie;
	tempMeshTie.name = "mig";	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMeshTie, error ) )
	{	// Oh no!!!! 
		//delete pBunny;
		return;
	}	
	{
		CGameObject* pTie = new CGameObject();
		pTie = new CGameObject();


		pTie->scale = 0.5f / tempMeshTie.pPlyFile->getMaxExtent();		// meshTypes[TIE_FIGHTER_ID].maxExtent;
		pTie->Cached_VBO_ID = tempMeshTie.GL_VBO_ID;						//  meshTypes[TIE_FIGHTER_ID].VBO_ID;
		pTie->numberOfTriangles = tempMeshTie.pPlyFile->GetNumberOfElements();	// meshTypes[TIE_FIGHTER_ID].numberOfTriangles;
		pTie->plyModelName = tempMeshTie.filename;						//"tie.ply";
	
		pTie->position.y = +2.0f;
		//pTie->PickARandomColour();
		pTie->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_RED );
		pTie->ambient = pTie->diffuse * 0.2f;
		pTie->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pTie->shininess = 1.0f;
		pTie->bIsWireframe = true;
		pTie->friendlyName = "Tie#1";
		pTie->scale = 2.0f;
		//g_vec_pTheObjects.push_back( pTie );
		pCow->vec_pChildObjects.push_back( pTie );
	}

	pCreatedObject = pCow;

	return ;
}