#include "global.h"

#include <iostream> 
// Note that the meshTypes, etc., now have to be declared in the Utils.h
// (Utils.h has really become something like a "global.h" file)


void CreateAllTheObjectsYo(void)
{
	// Add some objects to the vector....
	CGameObject* pBunny = new CGameObject();

	CMeshType tempMeshBunny;
	tempMeshBunny.name = "bunny";	// That the name we gave it
	std::string error;
	if ( ! ::g_pTheMeshManager->GetModelInfoByName( tempMeshBunny, error ) )
	{	// Oh no!!!! 
		std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		exit(-1);	
	}

	pBunny->scale = 1.0f / tempMeshBunny.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	pBunny->Cached_VBO_ID = tempMeshBunny.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pBunny->numberOfTriangles = tempMeshBunny.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pBunny->plyModelName = tempMeshBunny.filename;					//"bun_zipper_res3_xyz.ply";

	pBunny->bIsWireframe = false;	// Now it's wireframe...
	//pBunny->PickARandomColour();
	pBunny->diffuse.x = 1.0f;
	pBunny->diffuse.y = 0.5f;
	pBunny->diffuse.z = 0.0f;
	pBunny->friendlyName = "Bugs";
	g_vec_pTheObjects.push_back( pBunny );



	//CGameObject* pTie1 = new CGameObject();
	CGameObject* pTie = new CGameObject();
	CMeshType tempMeshTie;
	tempMeshTie.name = "tie";	// That the name we gave it
	if ( ! ::g_pTheMeshManager->GetModelInfoByName( tempMeshTie, error ) )
	{	// Oh no!!!! 
		std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		exit(-1);	
	}

	pTie->scale = 0.5f / tempMeshTie.pPlyFile->getMaxExtent();		// meshTypes[TIE_FIGHTER_ID].maxExtent;
	pTie->Cached_VBO_ID =       tempMeshTie.GL_VBO_ID;						//  meshTypes[TIE_FIGHTER_ID].VBO_ID;
	pTie->numberOfTriangles = tempMeshTie.pPlyFile->GetNumberOfElements();	// meshTypes[TIE_FIGHTER_ID].numberOfTriangles;
	pTie->plyModelName = tempMeshTie.filename;						//"tie.ply";
	
	pTie->position.x = -0.5f;
	pTie->diffuse = CGL
	pTie->bIsWireframe = true;
	pTie->ID = "Tie#1";
	//g_vec_pTheObjects.push_back( pTie1 );
	pBunny->vec_pChildObjects.push_back( pTie );


	CGameObject* pTie1 = new CGameObject();
	pTie1->scale = 1.0f / tempMeshTie.pPlyFile->getMaxExtent();		// meshTypes[TIE_FIGHTER_ID].maxExtent;
	pTie1->Cached_VBO_ID =       tempMeshTie.GL_VBO_ID;						//  meshTypes[TIE_FIGHTER_ID].VBO_ID;
	pTie1->numberOfTriangles = tempMeshTie.pPlyFile->GetNumberOfElements();	// meshTypes[TIE_FIGHTER_ID].numberOfTriangles;
	pTie->plyModelName = tempMeshTie.filename;						//"tie.ply";

	pTie1->position.z = 1.0f;
	pTie1->PickARandomColour();
	//pTie1->red = 0.0f;
	//pTie1->green = 1.0f;
	//pTie1->blue = 0.0f;
	pTie1->bIsWireframe = false;
	pTie1->ID = "Tie#2";
	//g_vec_pTheObjects.push_back( pTie11 );
	//pBunny->vec_pChildObjects.push_back( pTie1 );
	pTie->vec_pChildObjects.push_back( pTie1 );


	CGameObject* pMig = new CGameObject();
	CMeshType tempMeshMig;
	tempMeshMig.name = "mig";	// That the name we gave it
	if ( ! ::g_pTheMeshManager->GetModelInfoByName( tempMeshMig, error ) )
	{	// Oh no!!!! 
		std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		exit(-1);	
	}

	pMig->position.x = +1.0f;
	pMig->scale = 1.0f / tempMeshMig.pPlyFile->getMaxExtent();		// meshTypes[MIG_ID].maxExtent;
	pMig->Cached_VBO_ID =       tempMeshMig.GL_VBO_ID;						// meshTypes[MIG_ID].VBO_ID;
	pMig->numberOfTriangles = tempMeshMig.pPlyFile->GetNumberOfElements();	// meshTypes[MIG_ID].numberOfTriangles;
	pMig->PickARandomColour();
	pMig->ID = "Mig";
	g_vec_pTheObjects.push_back( pMig );



	// Also the seafloor
	CGameObject* pSeaFloor = new CGameObject();

	CMeshType tempMeshSeaFloor;
	tempMeshSeaFloor.name = "seafloor";	// That the name we gave it
	if ( ! ::g_pTheMeshManager->GetModelInfoByName( tempMeshSeaFloor, error ) )
	{	// Oh no!!!! 
		std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		exit(-1);	
	}

	//pSeaFloor->scale = 1.0f / tempMeshSeaFloor.plyFile.getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	pSeaFloor->scale = 1.0f;
	pSeaFloor->position.y = -5.0f;
	pSeaFloor->position.z = -20.0f;

	pSeaFloor->Cached_VBO_ID = tempMeshSeaFloor.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pSeaFloor->numberOfTriangles = tempMeshSeaFloor.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pSeaFloor->plyModelName = tempMeshSeaFloor.filename;					//"bun_zipper_res3_xyz.ply";

	pSeaFloor->bIsWireframe = false;	// Now it's wireframe...
	pSeaFloor->ID = "Seafloor";
	//pSeaFloor->scale *= 20.0f;
	//pSeaFloor->position.z = -5.0f;
	//pSeaFloor->position.y = -1.0f;
	pSeaFloor->PickARandomColour();
	pSeaFloor->shininess = 100.0f;
	pSeaFloor->specular.r = pSeaFloor->specular.g = pSeaFloor->specular.g = 1.0f;
	g_vec_pTheObjects.push_back( pSeaFloor );

	// Add a cow...
	CGameObject* pCow = new CGameObject();

	CMeshType tempMeshCow;
	tempMeshCow.name = "Bessy";	// That the name we gave it
	if ( ! ::g_pTheMeshManager->GetModelInfoByName( tempMeshCow, error ) )
	{	// Oh no!!!! 
		std::cout << "Can't find that model." << std::endl;
		// You should NEVER call this in actual code
		//	unless "all is completely lost"
		exit(-1);	
	}

	pCow->scale = 1.0f / tempMeshCow.pPlyFile->getMaxExtent();	//    meshTypes[BUNNY_ID].maxExtent;
	pCow->Cached_VBO_ID = tempMeshCow.GL_VBO_ID;						//      meshTypes[BUNNY_ID].VBO_ID;
	pCow->numberOfTriangles = tempMeshCow.pPlyFile->GetNumberOfElements();	//meshTypes[BUNNY_ID].numberOfTriangles;
	pCow->plyModelName = tempMeshCow.filename;					//"bun_zipper_res3_xyz.ply";

	pCow->bIsWireframe = false;	// Now it's wireframe...
	pCow->ID = "Bessy, the big cow";
	pCow->PickARandomColour();
	//pCow->specular.r = 0.0f;
	//pCow->specular.g = 0.0f;
	//pCow->specular.b = 0.0f;
	pCow->shininess = 10.0f;
	g_vec_pTheObjects.push_back( pCow );




	CGameObject* pLight = new CGameObject();
	CMeshType tempMeshSphere;
	tempMeshSphere.name = "Sphere";
	::g_pTheMeshManager->GetModelInfoByName( tempMeshSphere, error );
	pLight->scale = 0.1f / tempMeshSphere.pPlyFile->getMaxExtent();
	pLight->Cached_VBO_ID = tempMeshSphere.GL_VBO_ID;
	pLight->numberOfTriangles = tempMeshSphere.pPlyFile->GetNumberOfElements();
	pLight->plyModelName = tempMeshSphere.filename;
	pLight->bIsWireframe = true;
	pLight->diffuse = glm::vec3( 1.0f, 1.0f, 1.0f );
	pLight->ambient = glm::vec3( 0.2f, 0.2f, 0.2f );
	pLight->bIsWireframe = true;
	pLight->debugColour = glm::vec3( 255.0f/255.0f, 105.0f/255.0f, 180.0f/255.0f );		// Hot pink, apparently
	pLight->bUseDebugColour = true;
	pLight->ID = "Light00";
	g_vec_pTheObjects.push_back( pLight );


	return;
}
