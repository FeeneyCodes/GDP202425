// taken from: http://openglbook.com/the-book.html 
// Comments are from Michael

#include "global.h"
//#define WINDOW_TITLE_PREFIX "Chapter 4"
#include <iostream>		// Added
#include <sstream>		// Added

// Added on May 12th
#include <fstream>
#include <vector>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "CGameObjectBuilder.h"
#include "CModelTypeManager.h"

#include "CPhysicsWorld.h"
#include "CGLColourHelper.h"


int main(int argc, char* argv[])
{
	//glm::vec3 theRGB( 0.0f, 64.0f/255.0f, 0.0f );
	//glm::vec3 theHSL = CGLColourHelper::getInstance()->getHSLfromRGB( theRGB );
	//glm::vec3 theRGBAgain = CGLColourHelper::getInstance()->getRBGfromHSL( theHSL );
	//glm::vec3 RGBComp = CGLColourHelper::getInstance()->getComplimentaryRGB( theRGB );
	//std::cout << "RGB:      " << theRGB.r << ", " << theRGB.g << ", " << theRGB.b << std::endl;
	//std::cout << "HSL:      " << (theHSL.x * 360.0f) << ", " << theHSL.y << ", " << theHSL.z << std::endl;
	//std::cout << "RGB:      " << theRGBAgain.r << ", " << theRGBAgain.g << ", " << theRGBAgain.b << std::endl;
	//std::cout << "RGB (comp): " << RGBComp.r*255 << ", " << RGBComp.g *255<< ", " << RGBComp.b*255 << std::endl;
	//
	//return 0;


	CPhysicsWorld testWorld;
	// Test triangle (right angle with "vertical" side to left)
	glm::vec3 PointA( 0.0f, 0.0f, 0.0f );
	glm::vec3 PointB( 0.0f, 5.0f, 0.0f );
	glm::vec3 PointC( 5.0f, 0.0f, 0.0f );
	glm::vec3 TestPoint( -3.0f, 2.5f, 0.0f );

	glm::vec3 closestPoint = 
		testWorld.ClosestPtPointTriangle( TestPoint, PointA, PointB, PointC );

	std::cout << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << std::endl;

	// Light test
	//CLightDescription testLight;
	//testLight.SetToDefaultWhite();			// 0.1, 0.1, 0.1

	//for ( float dist = 0.0f; dist <= 100.0f; dist += 10.0f )
	//{
	//	std::cout << "Dist = " << dist << ", atten = " << testLight.calcDiffuseFromAttenByDistance(dist) << std::endl;
	//}

	//std::cout << "100% light level is at " << testLight.calcApproxDistFromAtten( 1.0f ) << std::endl;
	//std::cout << "75% light level is at " << testLight.calcApproxDistFromAtten( 0.75f ) << std::endl;
	//std::cout << "50% light level is at " << testLight.calcApproxDistFromAtten( 0.5f ) << std::endl;
	//std::cout << "25% light level is at " << testLight.calcApproxDistFromAtten( 0.25f ) << std::endl;
	//std::cout << "10% light level is at " << testLight.calcApproxDistFromAtten( 0.10f ) << std::endl;
	//std::cout << "1% light level is at " << testLight.calcApproxDistFromAtten( 0.01f ) << std::endl;
	//std::cout << "0.1% light level is at " << testLight.calcApproxDistFromAtten( 0.001f ) << std::endl;
	//std::cout << "0.1% light level is at " << testLight.calcApproxDistFromAtten( 0.001f ) << std::endl;


	::g_ErrorLog.OpenOrChangeLogFile( "RunLog" );
	::g_ErrorLog.DeleteOldLogFiles();
	::g_ErrorLog.SetAutoCRLF(true);
	::g_ErrorLog.SetForceFlush(true);
	::g_ErrorLog.SetWriteToLogFile(true);
	::g_ErrorLog.SetWriteToCout(true);
	::g_ErrorLog.SetAutoStripPathFromFileNames(true);
	::g_ErrorLog.PrintToLog( "Application starting..." );


	if ( ! Initialize(argc, argv) )
	{
		//std::cout << "Something went wrong. Sorry it didn't work out." << std::endl;
		::g_ErrorLog.PrintToLog( "Initialize() failed. I'm outta here.", __LINE__, __FILE__ );
		return -1;
	}

	// This loads models from files and places them into buffers
	//CModelTypeManager* pModelTypeManger = new CModelTypeManager();
	::g_pModelTypeManger = new CModelTypeManager();
	::g_pModelTypeManger->SetBaseFilePath( "assets/models/" );

	CMeshLoadParams loadParamDontScale;
	CMeshLoadParams loadParamScaleToUnitCube;
	loadParamScaleToUnitCube.bScaleOnLoad = true;
	loadParamScaleToUnitCube.bScaleToCube = true;
	loadParamScaleToUnitCube.fScaleOnLoadValue = 1.0f;
	loadParamScaleToUnitCube.bCalcNormalsIfNotPresent = true;

	// Load these models:
	std::vector< CMeshType > vecMeshesToLoad;
	vecMeshesToLoad.push_back( CMeshType( "bunny", "bun_zipper_xyz_Nxyz_res_0_69451_faces.ply", loadParamScaleToUnitCube ) );
//	vecMeshesToLoad.push_back( CMeshType( "bunny", "bun_zipper_res3_xyz.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "tie", "tie.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "mig", "mig29_xyz.ply", loadParamScaleToUnitCube ) );
	//vecMeshesToLoad.push_back( CMeshType( "seafloor", "Seafloor2.ply" ) );
	vecMeshesToLoad.push_back( CMeshType( "seafloor", "Seafloor2_(flattened).ply", loadParamDontScale ) );
	vecMeshesToLoad.push_back( CMeshType( "Bessy", "cow.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "Sphere", "Isoshphere.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "SphereNormals", "Isoshphere_xyz_nxyz.ply", loadParamScaleToUnitCube ) );
//	vecMeshesToLoad.push_back( CMeshType( "Room", "Room2.ply" ) );
	vecMeshesToLoad.push_back( CMeshType( "Room", "Room_2_Bigger_Triangulated.ply", loadParamDontScale ) );
//	vecMeshesToLoad.push_back( CMeshType( "Door", "SexyDoorAndKnob_Centred.ply" ) );
//	vecMeshesToLoad.push_back( CMeshType( "Door", "SexyThinnerDoorAndKnob_Centred.ply", loadParamDontScale ) );
	vecMeshesToLoad.push_back( CMeshType( "Door", "SexyEVENThinnerDoorAndKnob_Centred.ply", loadParamDontScale ) );

	// Load all the resolutions of bunnies
	vecMeshesToLoad.push_back( CMeshType( "bunny_res_3", "bun_zipper_xyz_Nxyz_res_3_948_faces.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "bunny_res_2", "bun_zipper_xyz_Nxyz_res_2_1889_faces.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "bunny_res_1", "bun_zipper_xyz_Nxyz_res_1_16301_faces.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "bunny_res_0", "bun_zipper_xyz_Nxyz_res_0_69451_faces.ply", loadParamScaleToUnitCube ) );

	vecMeshesToLoad.push_back( CMeshType( "1x1_2Tri_Quad_2_Sided", "1x1_2Tri_Quad_2_Sided.ply", loadParamScaleToUnitCube ) );

//	vecMeshesToLoad.push_back( CMeshType( "CuriosityQR", "CuriosityQR.ply", loadParamScaleToUnitCube ) );
//	vecMeshesToLoad.push_back( CMeshType( "CuriosityQR", "CuriosityQR_only_surface.ply", loadParamScaleToUnitCube ) );
	vecMeshesToLoad.push_back( CMeshType( "MeshLab_Terrain_01", "MeshLab_Terrain_01.ply", loadParamScaleToUnitCube ) );

	std::string error;
	if ( ! ::g_pModelTypeManger->LoadModelTypesFromFile( vecMeshesToLoad, error ) )
	{
		::g_ErrorLog.PrintToLog( error, __LINE__, __FILE__ );
		exit(-1);
	}

	// This knows how to create specific types of objects 
	// (or collections of parent-clild objects)
	// It needs the ModelTypeManager to create these objects
	CGameObjectBuilder* pGameObjectBuilder = new CGameObjectBuilder(::g_pModelTypeManger);

	// Now the game object manager (our "world") 
	// This handles creating objects, adding them to the world and intercommunication between obkects
	::g_pGameObjectManager = new CGameObjectManager( pGameObjectBuilder );
  

	// ****************************************************
	// Our old method that "knew" about the global vector of game objects
	// (it new too much, and had to be killed)
	//CreateAllTheObjectsYo();
	// ****************************************************
	CreateAllTheObjectsYo_2();

//std::cout << "About to generate the maze...";
//// Generate the maze
	::g_pMasterRoom = new CRoom(30.0f);
	::g_pMasterRoom->position.y = 0.0f;
////::g_pMasterRoom->percentChanceOfRoomWidth_0_to_100 = 30;
//::GenerateMaze( ::g_pMasterRoom, 5 );
//{
//	std::vector< CRoom* > vec_pRooms;
//	::g_pMasterRoom->GetListOfRooms( vec_pRooms );
//	std::cout << "Generated " << vec_pRooms.size() << " rooms" << std::endl;
//}
//
//std::cout << "...done" << std::endl;




	// **********************************************
	// Set up the GLUT menu
	int RoomsSubmenu = glutCreateMenu( glutMenuHandler_callback );
	glutAddMenuEntry( "Draw wireframe", 1 );
	glutAddMenuEntry( "Draw solid", 2 );
	glutAddMenuEntry( "Hide Rooms", 3 );

	int CameraSubmenu = glutCreateMenu( glutMenuHandler_callback );
	glutAddMenuEntry( "Draw target ball", 4 );
	glutAddMenuEntry( "Hide target ball", 5 );

	int MainMenu = glutCreateMenu( glutMenuHandler_callback );
	glutAddSubMenu( "Camera:", CameraSubmenu );
	glutAddSubMenu( "Rooms:", RoomsSubmenu );

	glutAttachMenu(GLUT_MIDDLE_BUTTON);




  // Set the camera:
  // (I just moved the camera around until things "looked good", then put a breakpoint in the Render and read these numbers)
  //::g_cameraEyeX = 5.1f;
  //::g_cameraEyeY = 5.2f;
  //::g_cameraEyeZ = 15.4f;
  ::g_cameraEyeX = 9.0f;
  ::g_cameraEyeY = 10.0f;
  ::g_cameraEyeZ = 10.0f;

	// *****************************************************************
	// Load some textures, yo
	::g_pTheTextureManager = new CTextureManager();
	::g_pTheTextureManager->setBasePath( "assets/textures/" );

	if ( ! ::g_pTheTextureManager->Create2DTextureFromBMPFile( "mt-ruapehu-and-mt-ngauruhoe.bmp", true ) )
	{
		//std::cout << "Didn't load the texture" << std::endl;
		::g_ErrorLog.PrintToLog( "Didn't load the texture.", __LINE__, __FILE__ );
	}

//	if ( ! ::g_pTheTextureManager->Create2DTextureFromBMPFile( "Emma.bmp", true ) )
	if ( ! ::g_pTheTextureManager->Create2DTextureFromBMPFile( "Green lush grass texture.bmp", true ) )
	{
		//std::cout << "Didn't load the texture" << std::endl;
		::g_ErrorLog.PrintToLog( "Didn't load the texture.", __LINE__, __FILE__ );
	}

	if ( ! ::g_pTheTextureManager->Create2DTextureFromBMPFile( "dried_mud_4012098 (2048x2048).bmp", true ) )
	{
		//std::cout << "Didn't load the texture" << std::endl;
		::g_ErrorLog.PrintToLog( "Didn't load the texture.", __LINE__, __FILE__ );
	}
	// *****************************************************************

	::g_pTheTextureManager->setBasePath( "assets/textures/SkyBoxes_by_Michael" );
	if ( !g_pTheTextureManager->CreateCubeTextureFromBMPFiles( "SpaceSkyBox", 
		                                                     "MyFirstSpaceBox_right1_posX.bmp", "MyFirstSpaceBox_left2_negX.bmp", 
															 "MyFirstSpaceBox_top3_posY.bmp", "MyFirstSpaceBox_bottom4_negY.bmp",
															 "MyFirstSpaceBox_front5_posZ.bmp", "MyFirstSpaceBox_back6_negZ.bmp", 
															 true, true ) )
	{
		std::cout << "Didn't load the sky box texture(s):" << std::endl;
		std::cout << ::g_pTheTextureManager->getLastError() << std::endl;
	}
	//ExitOnGLError("Skymap didn't load.");


	::g_pTheTextureManager->UpdateTextureBindings();
	// Print out what's bound to what
	GLenum texUnit = 0;
	::g_pTheTextureManager->GetTexUnitFromName( "mt-ruapehu-and-mt-ngauruhoe.bmp", texUnit );
	std::cout << "mt-ruapehu-and-mt-ngauruhoe.bmp bound to " << texUnit << " or unit: " << texUnit - GL_TEXTURE0 << std::endl;

	::g_pTheTextureManager->GetTexUnitFromName( "Green lush grass texture.bmp", texUnit );
	std::cout << "Green lush grass texture.bmp bound to " << texUnit << " or unit: " << texUnit - GL_TEXTURE0 << std::endl;

	::g_pTheTextureManager->GetTexUnitFromName( "dried_mud_4012098 (2048x2048).bmp", texUnit );
	std::cout << "dried_mud_4012098 (2048x2048).bmp bound to " << texUnit << " or unit: " << texUnit - GL_TEXTURE0 << std::endl;

	::g_pTheTextureManager->GetTexUnitFromName( "SpaceSkyBox", texUnit );
	std::cout << "SpaceSkyBox bound to " << texUnit << " or unit: " << texUnit - GL_TEXTURE0 << std::endl;


	::g_pGLPrintf = new CGLPrintf( ::g_pModelTypeManger, ::g_pGameObjectManager );
	::g_pGLPrintf->SetBaseDirectory( "font" );
	CGLPrintf::sLoadOptions loadOptions;
	loadOptions.bInterpretScaleAsBoundingBox = false;
	loadOptions.bScaleFontOnLoad = false;
	loadOptions.scaleOnLoad = 1.0f;
	if ( ! ::g_pGLPrintf->LoadCharacterSet( "blender_default", "blender_default", loadOptions, error ) )
	{
		std::cout << error << std::endl;
	}
	::g_pGLPrintf->SelectCurrentFont( "blender_default" );
	::g_pGLPrintf->SetSpaceCharacterSize( "blender_default", CGLPrintf::SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH );
	::g_pGLPrintf->setFontRenderScale( "blender_default", 1.0f );
	::g_pGLPrintf->SetCharacterSpacingMode( "blender_default", CGLPrintf::SPACE_BETWEEN_CHARACTERS_IS_FIXED, 0.0f );


	::g_pIOTimer = new CHRTimer();
	::g_pIOTimer->Reset();
	::g_pIOTimer->Start();

	::g_pTheMouse = new CMouseState();

	// Set the camera proxy object (the camera follows this)
	CGameObject* pCameraProxy = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "CameraProxy" );
	pCameraProxy->position.x = 9.0f;
	pCameraProxy->position.y = 10.0f;
	pCameraProxy->position.z = 60.0f;


	glutMainLoop();

	::g_ErrorLog.PrintToLog( "Exiting application. Bye now." );
  
	exit(EXIT_SUCCESS);
	return 0;
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);


	unsigned int g_screenWidth = Width;
	unsigned int g_screenHeight = Height;

	matProjection= glm::perspective( 
						glm::radians(45.0f),	// FOV
						// 16:9, 4:3, 16:10
						static_cast<float>(g_screenWidth) / static_cast<float>(g_screenHeight),	
						0.1f,		// Near plane
						10000.f);		// Far plane



	::g_pTheShaderManager->UseShaderProgram( "simpleShader", true );
 	//ExitOnGLError("ERROR: Could not use the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not use the shader program", __LINE__, __FILE__, ::g_ErrorLog );


	glUniformMatrix4fv( g_UniformLocation_ProjectionMatrix, 1, 
						GL_FALSE, glm::value_ptr(matProjection) );
	//::g_pTheShaderManager->SetUniformMatrix4fv( "simpleShader", "ProjectionMatrix", 1, GL_FALSE,
	//	                                        glm::value_ptr(matProjection) );
 	//ExitOnGLError("ERROR: Could not use the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not use the shader program", __LINE__, __FILE__, ::g_ErrorLog );

	glUseProgram(0);
 	//ExitOnGLError("ERROR: Could not use the shader program");
	//COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not use the shader program", __LINE__, __FILE__, ::g_ErrorLog );

	return;
}




void ShutErDown(void)
{

	::g_pTheShaderManager->ShutDown();

	//ExitOnGLError("ERROR: Could not destroy the shaders");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not destroy the shaders", __LINE__, __FILE__, ::g_ErrorLog );

	::g_pGameObjectManager->ShutDown();

	//// Go through the objects and delete them
	//for ( std::vector< CGameObject* >::iterator itChild = ::g_vec_pTheObjects.begin();
	//		itChild != ::g_vec_pTheObjects.end(); itChild++ )
	//{
	//	// Pointer not zero (0)?
	//	CGameObject* pTempChildObject = (*itChild);
	//	if ( pTempChildObject != 0 )
	//	{
	//		// Recursively delete all children's children (and so on)
	//		pTempChildObject->DeleteChildren();
	//		// Now delete this child
	//		delete pTempChildObject;
	//	}
	//}
	//// Get rid of the objects
	//::g_vec_pTheObjects.clear();

	if ( ::g_pTheTextureManager != 0 )
	{
		::g_pTheTextureManager->ShutDown();
		delete ::g_pTheTextureManager;
		::g_pTheTextureManager = 0;
	}

	delete ::g_pIOTimer;
	delete ::g_pTheMouse;

	::g_pGLPrintf->ShutDown();
	delete ::g_pGLPrintf;

	// TODO: Go through all the buffers and delete them
	//glDeleteBuffers(2, &BufferIds[1]);
	//glDeleteVertexArrays(1, &BufferIds[0]);
	//ExitOnGLError("ERROR: Could not destroy the buffer objects");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not destroy the buffer objects", __LINE__, __FILE__, ::g_ErrorLog );

	return;
}

