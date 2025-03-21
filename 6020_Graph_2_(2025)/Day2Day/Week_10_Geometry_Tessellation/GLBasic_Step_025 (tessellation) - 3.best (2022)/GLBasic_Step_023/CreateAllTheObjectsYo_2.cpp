#include "global.h"

#include "CGLColourHelper.h"

float getRandomFloat(float maxFloat)
{
	return ( static_cast<float>( rand() ) / static_cast<float>(RAND_MAX + 1) ) * maxFloat;
}

// Clear on all passes, except the one I want 
void SetDrawOnPass( CGameObject* pGO, unsigned int passNumber )
{
	// Don't draw on any passes...
	for ( unsigned int index = 0; index != MAXNUMBEROFDRAWPASSES; index++ )
	{	
		pGO->bDrawOnPass[index] = false;
	}
	//... except this one:
	pGO->bDrawOnPass[passNumber] = true;
	return;
}


void MakeOneRabbit(CGameObject* pGO, glm::vec3 position)
{
	std::string error;
	unsigned int bunnyID = 0;
	if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Basic Bunny", false, bunnyID, error ) )
	{
		::g_ErrorLog.PrintToLog( error );
	}
	CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByID( bunnyID );
	if ( pBunny != 0 )
	{
		pBunny->scale = 4.0f;
		pBunny->position = position;
		//pBunny->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
		pBunny->diffuse = CGLColourHelper::getInstance()->getRandomColourRGB();
		pBunny->ambient = pBunny->diffuse * 0.2f;
		pBunny->specular = pBunny->diffuse;

		pBunny->setOrientationFromEuler( glm::vec3( 0.0f, getRandomFloat( 2.0f * 3.14159f ), 0.0f ) );

		pBunny->friendlyName = "BugsBunny";

		// ****************
		SetDrawOnPass( pBunny, 2 );	// Drawn with the bunnies AFTER the stencil is set
		// ****************


		// 0 is highest res, 3 is lowest res
		CMeshType bunLOD[4];
		bunLOD[0].filename = "bun_zipper_xyz_Nxyz_res_0_69451_faces.ply";
		bunLOD[1].filename = "bun_zipper_xyz_Nxyz_res_1_16301_faces.ply";
		bunLOD[2].filename = "bun_zipper_xyz_Nxyz_res_2_1889_faces.ply";
		bunLOD[3].filename = "bun_zipper_xyz_Nxyz_res_3_948_faces.ply";

		std::string error;
		for ( int index = 0; index != 4; index++ )
		{
			::g_pModelTypeManger->GetModelInfoByFileName( bunLOD[index], error );

			pBunny->Cached_VBO_ID_LOD[index] = bunLOD[index].GL_VBO_ID;

			pBunny->LOD_NumberOfTriangles[index] = bunLOD[index].pPlyFile->GetNumberOfElements();
		}
		pBunny->bUseLOD = true;

	}//if ( pBunny != 0 )
	return;
}

void LotsOfRabbits(void)
{
	int bunnyCount = 0;
	for ( float x = -100.0f; x <= 101.0f; x += 5.0f )
	{
		for ( float z = -100.0f; z <= 101.0f; z += 5.0f )
		{
			CGameObject* pGO = NULL;
			MakeOneRabbit( pGO, glm::vec3( x, -4.0f, z ) );
			bunnyCount++;
		}
	}
	std::cout << "Made " << bunnyCount << " bunnies." << std::endl;
	return;
}

void CreateAllTheObjectsYo_2(void)
{
	// This whole part should really be placed into some kind of file loader thing
	// But I don't want to give you that...

	std::string error; 

//	LotsOfRabbits();

	{// STARTOF: scope for Room
		unsigned int roomID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Room_2_Bigger_Triangulated.ply", true, roomID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pRoom = ::g_pGameObjectManager->FindGameObjectByID( roomID );
		if ( pRoom != 0 )
		{
			//pRoom->scale = 10.0f / 4.0f;		// Room is 4x4 units
			pRoom->scale = 3.0f;		// Original models are 10x10 (-5 to 5 on each side)

			pRoom->position.y = -500.0f;		// Original room way below the scene

			pRoom->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pRoom->ambient = pRoom->diffuse * 0.2f;
			pRoom->specular = pRoom->diffuse;
			pRoom->bIsWireframe = false;
			//pRoom->bUseDebugColour = true;
			pRoom->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			// Set room invisible so it's not drawn usually (we'll set it during DrawRoom)
			pRoom->bIsVisible = false;
			pRoom->friendlyName = "Room";
		}//if ( pGround != 0 )
	}// ENDOF: scope for Room

	{// STARTOF: scope for Door
		unsigned int doorID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "SexyEVENThinnerDoorAndKnob_Centred.ply", true, doorID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pDoor = ::g_pGameObjectManager->FindGameObjectByID( doorID );
		if ( pDoor != 0 )
		{
			//pDoor->scale = 10.0f / 4.0f;		// Room is 4x4 units
			pDoor->scale = 3.0f;
			pDoor->position.y = -500.0f;		// Original room way below the scene

			// ****************
			SetDrawOnPass( pDoor, 1 );	// On draw on pass #1
			// ****************

			pDoor->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pDoor->ambient = pDoor->diffuse * 0.2f;
			pDoor->specular = pDoor->diffuse;
			pDoor->bIsWireframe = false;
			pDoor->bUseDebugColour = true;
			//pDoor->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			// Set door invisible so it's not drawn usually (we'll set it during DrawRoom)
			pDoor->bIsVisible = false;
			pDoor->friendlyName = "Door";
		}//if ( pGround != 0 )
	}// ENDOF: scope for Door


	{// STARTOF: scope for debug physics ball object
		unsigned int ballID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Isoshphere.ply", true, ballID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pBall = ::g_pGameObjectManager->FindGameObjectByID( ballID );
		if ( pBall != 0 )
		{
			pBall->scale = 0.5f;
			pBall->position.y = 6.0f;
			pBall->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pBall->ambient = pBall->diffuse * 0.2f;
			pBall->specular = pBall->diffuse;
			pBall->bIsWireframe = true;
			pBall->bUseDebugColour = true;
			pBall->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );

			pBall->friendlyName = "YellowDebugBall";
		}//if ( pGround != 0 )
	}// ENDOF: scope for debug physics ball object

	{// STARTOF: scope for "camera" proxy object
		unsigned int cameraID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Isoshphere.ply", true, cameraID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pCamera = ::g_pGameObjectManager->FindGameObjectByID( cameraID );
		if ( pCamera != 0 )
		{
			pCamera->scale = 0.5f;
			//pCamera->position.y = 6.0f;
			pCamera->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pCamera->ambient = pCamera->diffuse * 0.2f;
			pCamera->specular = pCamera->diffuse;
			pCamera->bIsWireframe = true;
			pCamera->bUseDebugColour = true;
			pCamera->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pCamera->setOrientationFromEuler( glm::vec3( 0.0f, glm::radians(180.0f), 0.0f ) );

			pCamera->friendlyName = "CameraProxy";
		}//if ( pGround != 0 )
	}// ENDOF: scope for debug physics ball object
	
	{// STARTOF: scope for debug physics ball object
		unsigned int skyboxID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Isoshphere.ply", true, skyboxID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pSkyBox = ::g_pGameObjectManager->FindGameObjectByID( skyboxID );
		if ( pSkyBox != 0 )
		{
			// notice the scale of the "skyball"
			pSkyBox->scale = 1000.0f;
			pSkyBox->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			pSkyBox->ambient = pSkyBox->diffuse * 0.2f;
			pSkyBox->specular = pSkyBox->diffuse;
			pSkyBox->bIsWireframe = false;
			pSkyBox->bUseDebugColour = false;
			pSkyBox->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );

			pSkyBox->bIsSkyBox = true;
			pSkyBox->friendlyName = "SkyBox";
			pSkyBox->textureName0 = "SpaceSkyBox";

		}//if ( pGround != 0 )
	}// ENDOF: scope for debug physics ball object

	{// STARTOF: scope for "ground" object
		unsigned int groundID = 0;
//		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Seafloor2_(flattened).ply", true, groundID, error ) )
//		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "CuriosityQR.ply", true, groundID, error ) )
//		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "CuriosityQR_only_surface.ply", true, groundID, error ) )
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "MeshLab_Terrain_01.ply", true, groundID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pGround = ::g_pGameObjectManager->FindGameObjectByID( groundID );
		if ( pGround != 0 )
		{
			pGround->scale = 100.0f;
			pGround->position.y = -6.0f;
			pGround->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
			pGround->ambient = pGround->diffuse * 0.2f;
			pGround->specular = pGround->diffuse;
			pGround->bIsWireframe = false;

//			pGround->textureName0 = "mt-ruapehu-and-mt-ngauruhoe.bmp";
//			pGround->textureName0 = "dried_mud_4012098 (2048x2048).bmp";
			pGround->textureName0 = "Green lush grass texture.bmp";
			//pGround->textureName0 = "";
//			pGround->textureName1 = "";	// No texture for unit #2

			pGround->friendlyName = "Ground";
		}//if ( pGround != 0 )
	}// ENDOF: scope for "ground" object

//{// STARTOF: scope for "ground" object
//	unsigned int groundID = 0;
//	if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "1x1_2Tri_Quad_2_Sided.ply", true, groundID, error ) )
//	{
//		::g_ErrorLog.PrintToLog( error );
//	}
//	CGameObject* pGround = ::g_pGameObjectManager->FindGameObjectByID( groundID );
//	if ( pGround != 0 )
//	{
//		pGround->scale = 100.0f;
//		//pGround->position.y = -5.0f;
//		pGround->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
//		pGround->ambient = pGround->diffuse * 0.2f;
//		pGround->specular = pGround->diffuse;
//		pGround->bIsWireframe = false;
//
//		pGround->textureName0 = "mt-ruapehu-and-mt-ngauruhoe.bmp";
//		//pGround->textureName0 = "";
//		pGround->textureName1 = "";	// No texture for unit #2
//
//		pGround->friendlyName = "GroundWithGrass";
//	}//if ( pGround != 0 )
//}// ENDOF: scope for "ground" object

	{// STARTOF: scope for "basic bunny"
		unsigned int bunnyID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Basic Bunny", false, bunnyID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByID( bunnyID );
		if ( pBunny != 0 )
		{
			pBunny->position.x = -2.0f;
			pBunny->position.y = 5.0f;
			pBunny->position.z = 2.5f;
			pBunny->scale = 2.0f;
			pBunny->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
			pBunny->ambient = pBunny->diffuse * 0.2f;
			pBunny->specular = pBunny->diffuse;

			pBunny->textureName0 = "Emma.bmp";
			//pBunny->textureName1 = "Brick_texture_-_Saint-Omer_(Pas-de-Calais)_-_06_1728 (1024x1024).bmp";
			pBunny->textureName1 = "Fence_Alpha_Mask.bmp";

			pBunny->alphaTransparency = 0.75f;

			pBunny->friendlyName = "BugsBunny";
		}//if ( pBunny != 0 )
	}//ENDOF: scope for "basic bunny"

	{// STARTOF: scope for "basic bunny"
		unsigned int bunnyID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Basic Bunny", false, bunnyID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByID( bunnyID );
		if ( pBunny != 0 )
		{
			pBunny->position.x = -4.0f;
			pBunny->position.y = 5.0f;
			pBunny->position.z = 2.5f;
			pBunny->scale = 40.0f;
			pBunny->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
			pBunny->ambient = pBunny->diffuse * 0.2f;
			pBunny->specular = pBunny->diffuse;
			pBunny->bIsWireframe = true;

			pBunny->textureName0 = "Brick_texture_-_Saint-Omer_(Pas-de-Calais)_-_06_1728 (1024x1024).bmp";
			//pBunny->textureName1 = "Brick_texture_-_Saint-Omer_(Pas-de-Calais)_-_06_1728 (1024x1024).bmp";
			pBunny->textureName1 = "";

			pBunny->alphaTransparency = 0.75f;

			pBunny->friendlyName = "BugsBunny";
		}//if ( pBunny != 0 )
	}//ENDOF: scope for "basic bunny"

	{// STARTOF: scope for "tie fighter"
		unsigned int tieID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Tie Fighter", false, tieID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pTie = ::g_pGameObjectManager->FindGameObjectByID( tieID );
		if ( pTie != 0 )
		{
			pTie->position.x = 3.0f;
			pTie->position.y = 5.0f;
			pTie->position.z = 0.0f;
			pTie->friendlyName = "DarthVader";
			pTie->scale = 2.0f;
			pTie->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
			pTie->specular = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_WHITE );
			pTie->ambient = pTie->diffuse * 0.2f; 
		}//if ( pBunny != 0 )
	}// ENDOF: scope for "tie fighter"

	{// STARTOF: scope for "mig fighter"
		unsigned int migID = 0;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "mig29_xyz.ply", true, migID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pMig = ::g_pGameObjectManager->FindGameObjectByID( migID );
		if ( pMig != 0 )
		{
			// Set the orientation
			// NEVER, NEVER, NEVER, NEVER do this with quaternions...
//			pMig->qOrientation.x = glm::radians( 45.0f );
//			pMig->qOrientation.y = glm::radians( 15.0f );
//			pMig->qOrientation.z = glm::radians( 0.0f );
			glm::vec3 initRotationEuler( 0.0f, 0.0f, 0.0f);
			pMig->setOrientationFromEuler( glm::radians(initRotationEuler) );


			pMig->position.x = 4.0f;
			pMig->position.y = 2.0f;
			pMig->position.z = 1.0f;
			pMig->friendlyName = "Vladimir";
			pMig->scale = 3.0f;
			pMig->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_GREEN );
			pMig->specular = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_GREEN );
			pMig->ambient = pMig->diffuse * 0.2f; 
		}//if ( pBunny != 0 )
	}// ENDOF: scope for "mig fighter"

	//unsigned int bunnyWithTieID;
	//if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Bunny with tie", false, bunnyWithTieID, error ) )
	//{
	//	::g_ErrorLog.PrintToLog( error );
	//}
	//CGameObject* pBunnyWithTie = ::g_pGameObjectManager->FindGameObjectByID( bunnyWithTieID );
	//pBunnyWithTie->position.x = 1.0f;
	//pBunnyWithTie->position.y = 1.0f;

	{// STARTOF: scope for "swarm of Cylons"
		unsigned int cylonID;
		if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Cylons, yikes!", false, cylonID, error ) )
		{
			::g_ErrorLog.PrintToLog( error );
		}
		CGameObject* pCylonSwarm = ::g_pGameObjectManager->FindGameObjectByID( cylonID );
		pCylonSwarm->position.y = 7.0f;
	}//ENDOF: scope for "swarm of Cylons"


	//{// STARTOF: scope for light0
	//	unsigned int lightID = 0;
	//	if ( ! ::g_pGameObjectManager->AddGameObjectToWorld( "Light0", false, lightID, error ) )
	//	{
	//		::g_ErrorLog.PrintToLog( error );
	//	}
	//}// ENDOF: scope for light0


	// For the mediator, change the colours of the objects

	//// Use the position of bug bunny as the point to test
	//CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "BugsBunny" );
	//pBunny->bUseDebugColour = true;
	//pBunny->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_GREEN );

	//CGameObject* pDarth = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "DarthVader" );
	//pDarth->bUseDebugColour = true;
	//pDarth->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_RED );




	return;
}
