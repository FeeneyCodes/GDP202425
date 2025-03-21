#include "CGameObjectBuilder.h"
#include "CGLColourHelper.h"
#include <sstream>

// This is the ONLY method that need to "know" about how to create a CLight object.
#include "CLight.h"


bool CGameObjectBuilder::m_CreateALight( CGameObject* &pCreatedObject, unsigned int LightID, std::string &error )
{
	//pCreatedObject = new CGameObject();
	pCreatedObject = new CLight();

	CMeshType tempMesh;
	tempMesh.name = "Sphere";	// That the name we gave it
	if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
	{	// Oh no!!!! 
		//std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		return false;
	}

	pCreatedObject->scale = 0.1f * ( 1.0f / tempMesh.pPlyFile->getMaxExtent() );	//    meshTypes[BUNNY_ID].maxExtent;
	pCreatedObject->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pCreatedObject->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pCreatedObject->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

	pCreatedObject->bIsWireframe = true;	// Now it's wireframe...
	//pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
	pCreatedObject->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BLACK );
	pCreatedObject->ambient = pCreatedObject->diffuse * 0.2f;
	pCreatedObject->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
	pCreatedObject->bUseDebugColour = true;
	pCreatedObject->debugColour 
		= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_BLACK );

	std::stringstream ssName;
	ssName << "Light" << LightID;
	pCreatedObject->friendlyName = ssName.str();

	// Now create the internal spheres...
	{ // Sphere #1 (75%)
		CGameObject* pSphere75 = new CGameObject();

		CMeshType tempMesh;
		tempMesh.name = "Sphere";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
		{	// Oh no!!!! 
			//std::cout << "Can't find that model." << std::endl;
			// You should NEVER call this in actual code
			//	unless "all is completely lost"
			return false;
		}

		pSphere75->scale = 1.0f / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pSphere75->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pSphere75->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pSphere75->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

		pSphere75->bIsWireframe = true;	// Now it's wireframe...
		//pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
		pSphere75->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
		pSphere75->ambient = pCreatedObject->diffuse * 0.2f;
		pSphere75->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pSphere75->bUseDebugColour = true;
		pSphere75->debugColour 
			= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );

		pCreatedObject->vec_pChildObjects.push_back( pSphere75 );
	} // Sphere #2 (75%)

		// Now create the internal spheres...
	{ // Sphere #1 (50%)
		CGameObject* pSphere50 = new CGameObject();

		CMeshType tempMesh;
		tempMesh.name = "Sphere";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
		{	// Oh no!!!! 
			//std::cout << "Can't find that model." << std::endl;
			// You should NEVER call this in actual code
			//	unless "all is completely lost"
			return false;
		}

		pSphere50->scale = 1.0f / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pSphere50->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pSphere50->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pSphere50->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

		pSphere50->bIsWireframe = true;	// Now it's wireframe...
		//pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
		pSphere50->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
		pSphere50->ambient = pCreatedObject->diffuse * 0.2f;
		pSphere50->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pSphere50->bUseDebugColour = true;
		pSphere50->debugColour 
			= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );

		pCreatedObject->vec_pChildObjects.push_back( pSphere50 );
	} // Sphere #2 (50%)

			// Now create the internal spheres...
	{ // Sphere #3 (25%)
		CGameObject* pSphere25 = new CGameObject();

		CMeshType tempMesh;
		tempMesh.name = "Sphere";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
		{	// Oh no!!!! 
			//std::cout << "Can't find that model." << std::endl;
			// You should NEVER call this in actual code
			//	unless "all is completely lost"
			return false;
		}

		pSphere25->scale = 1.0f / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pSphere25->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pSphere25->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pSphere25->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

		pSphere25->bIsWireframe = true;	// Now it's wireframe...
		//pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
		pSphere25->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_LIME_GREEN );
		pSphere25->ambient = pCreatedObject->diffuse * 0.2f;
		pSphere25->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pSphere25->bUseDebugColour = true;
		pSphere25->debugColour 
			= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_LIME_GREEN );

		pCreatedObject->vec_pChildObjects.push_back( pSphere25 );
	} // Sphere #3 (25%)

	{ // Sphere #4 (1)
		CGameObject* pSphere1 = new CGameObject();

		CMeshType tempMesh;
		tempMesh.name = "Sphere";	// That the name we gave it
		if ( ! this->m_pModelTypeManager->GetModelInfoByName( tempMesh, error ) )
		{	// Oh no!!!! 
			//std::cout << "Can't find that model." << std::endl;
			// You should NEVER call this in actual code
			//	unless "all is completely lost"
			return false;
		}

		pSphere1->scale = 1.0f / tempMesh.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
		pSphere1->Cached_VBO_ID = tempMesh.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
		pSphere1->numberOfTriangles = tempMesh.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
		pSphere1->plyModelName = tempMesh.filename;					//"bun_zipper_res3_xyz.ply";

		pSphere1->bIsWireframe = true;	// Now it's wireframe...
		//pCreatedObject->bIsWireframe = false;	// Now it's wireframe...
		pSphere1->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_TAN );
		pSphere1->ambient = pCreatedObject->diffuse * 0.2f;
		pSphere1->specular = glm::vec3( 1.0f, 1.0f, 1.0f );
		pSphere1->bUseDebugColour = true;
		pSphere1->debugColour 
			= CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_TAN );

		pCreatedObject->vec_pChildObjects.push_back( pSphere1 );
	} // Sphere #3 (25%)
	return true;
}