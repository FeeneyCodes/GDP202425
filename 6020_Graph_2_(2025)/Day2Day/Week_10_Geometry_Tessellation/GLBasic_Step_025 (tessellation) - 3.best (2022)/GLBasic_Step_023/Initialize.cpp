#include "global.h"

#include <iostream>
#include <sstream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// Shader manager stuff
// Note that this file (the cpp file) includes
//	the actual CGLShaderManger, NOT the interface
// (the header includes the interface class)
// This is because we are calling new here.
#include "CShaderManager/CGLShaderManager.h"

// These were moved here because the function was getting way to big
void SetUpTheLightingUniforms( GLuint shaderID );


bool Initialize(int argc, char* argv[])
{
	GLenum GlewInitResult;

	if (! InitWindow(argc, argv) )
	{
		return false;	// Error
	}// if (! InitWindow(argc, argv) )
  
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) 
	{
		//fprintf(
		//  stderr,
		//  "ERROR: %s\n",
		//  glewGetErrorString(GlewInitResult)
		//);
		std::cout << "ERROR: " << glewGetErrorString(GlewInitResult) << std::endl;
		exit(EXIT_FAILURE);
	}
  
	//fprintf(
	//  stdout,
	//  "INFO: OpenGL Version: %s\n",
	//  glGetString(GL_VERSION)
	//);
	std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glGetError();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//ExitOnGLError("ERROR: Could not set OpenGL depth testing options");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not set OpenGL depth testing options", __LINE__, __FILE__, ::g_ErrorLog );


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//ExitOnGLError("ERROR: Could not set OpenGL culling options");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not set OpenGL culling options", __LINE__, __FILE__, ::g_ErrorLog );

	//ModelMatrix = IDENTITY_MATRIX;
	//matModel = glm::mat4(1.0f);		// Sets to identity

	//ProjectionMatrix = IDENTITY_MATRIX;
	matProjection = glm::mat4(1.0f);	

	//ViewMatrix = IDENTITY_MATRIX;
	//TranslateMatrix(&ViewMatrix, 0, 0, -2);

	//matView = glm::mat4(1.0f);		// identity matrix
	//matView = glm::lookAt( glm::vec3(0.0f, 0.0f, -2.0f),	// Camera (aka "Eye")
		//				 glm::vec3(0.0f, 0.0f, 0.0f),	// At (aka "target")
		//				 glm::vec3(0.0f, 1.0f, 0.0f) );	// Up

	// Now that OpenGL is up and running...
	// Place the LoadShaders(), etc. that was in LoadMeshDataIntoBuffers here.
	// Why? So that it's only called one time.

	//LoadShaders();

	::g_pTheShaderManager = new CGLShaderManager();
	::g_pTheShaderManager->SetBaseFilePath( "assets/shaders/" );

	CShaderProgramDescription simpleLighting;
	simpleLighting.name = "simpleShader";
	//::g_pTheShaderManager->UseShaderProgram( "simpleShader" );

	simpleLighting.vShader.filename = "MultiLightsTextures.vertex.glsl";
	simpleLighting.vShader.name = "simpleVertex";	// We pick this
	simpleLighting.vShader.type = GLSHADERTYPES::VERTEX_SHADER;

	simpleLighting.fShader.filename = "MultiLightsTextures.fragment.glsl";
	simpleLighting.fShader.name = "pointFragment";
	simpleLighting.fShader.type = GLSHADERTYPES::FRAGMENT_SHADER;

	// Tess control...
	simpleLighting.tContShader.filename = "MultiLightsTextures.tessControl.glsl";
	simpleLighting.tContShader.name = "pointTessControl";
	simpleLighting.tContShader.type = GLSHADERTYPES::TESSELLATION_CONTROL_SHADER;

	// Tess eval...
	simpleLighting.tEvalShader.filename = "MultiLightsTextures.tessEval.glsl";
	simpleLighting.tEvalShader.name = "pointTessEval";
	simpleLighting.tEvalShader.type = GLSHADERTYPES::TESSELLATION_EVALUATION_SHADER;


	if ( ! g_pTheShaderManager->CreateShaderProgramFromFile( simpleLighting ) )
	{
		std::cout << "Something went wrong..." << std::endl;
		if ( ! simpleLighting.bIsOK )
		{
			std::cout << "--------------------------------------------------------" << std::endl;
			if ( simpleLighting.vShader.bIsOK )
			{
				std::cout << "Vertex shader " << simpleLighting.vShader.name << " is OK." << std::endl;
			}
			else
			{	// Print the errors from the vertex shader compile
				std::cout << "The vertex shader " << simpleLighting.vShader.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.vShader.vecShaderErrors.begin();
					  itErrors != simpleLighting.vShader.vecShaderErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.vShader.bIsOK )

			std::cout << "--------------------------------------------------------" << std::endl;
			if ( simpleLighting.fShader.bIsOK )
			{
				std::cout << "Fragment shader " << simpleLighting.fShader.name << " is OK." << std::endl;
			}
			else
			{
				std::cout << "The fragment shader " << simpleLighting.fShader.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.fShader.vecShaderErrors.begin();
					  itErrors != simpleLighting.fShader.vecShaderErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.fShader.bIsOK )

			std::cout << "--------------------------------------------------------" << std::endl;
			if ( simpleLighting.gShader.bIsOK )
			{
				std::cout << "Geometry shader " << simpleLighting.gShader.name << " is OK." << std::endl;
			}
			else
			{
				std::cout << "The geometry shader " << simpleLighting.gShader.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.gShader.vecShaderErrors.begin();
					  itErrors != simpleLighting.gShader.vecShaderErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.gShader.bIsOK )		}//if ( ! simpleLighting.bIsOK )

			std::cout << "--------------------------------------------------------" << std::endl;
			if ( simpleLighting.tContShader.bIsOK )
			{
				std::cout << "Tesselation Control shader " << simpleLighting.tContShader.name << " is OK." << std::endl;
			}
			else
			{
				std::cout << "The tessellation control shader " << simpleLighting.tContShader.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.tContShader.vecShaderErrors.begin();
					  itErrors != simpleLighting.tContShader.vecShaderErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.tContShader.bIsOK )		}//if ( ! simpleLighting.bIsOK )

			std::cout << "--------------------------------------------------------" << std::endl;
			if ( simpleLighting.tEvalShader.bIsOK )
			{
				std::cout << "Tesselation Evaluation shader " << simpleLighting.tEvalShader.name << " is OK." << std::endl;
			}
			else
			{
				std::cout << "The tessellation evaluation shader " << simpleLighting.tEvalShader.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.tEvalShader.vecShaderErrors.begin();
					  itErrors != simpleLighting.tEvalShader.vecShaderErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.tEvalShader.bIsOK )		}//if ( ! simpleLighting.bIsOK )

			// Now general errors (linker errors are here, too)
			std::cout << "--------------------------------------------------------" << std::endl;
			if ( ! simpleLighting.bIsOK )
			{
				std::cout << "General shader program (and linker) " << simpleLighting.name << "generated the following errors: " << std::endl;
				for ( std::vector< std::string >::iterator itErrors = simpleLighting.vecErrors.begin();
					  itErrors != simpleLighting.vecErrors.end(); itErrors++ )
				{
					std::cout << "\t" << *itErrors << std::endl;
				}
			}//if ( simpleLighting.tEvalShader.bIsOK )		}//if ( ! simpleLighting.bIsOK )


		}// if ( ! simpleLighting.bIsOK )

		// Force the cout to print to screen.
		std::cout.flush();
		return false;
	}//if ( ! g_pTheShaderManager->CreateShaderProgramFromFile( simpleLighting ) )
	else
	{
		std::cout << "The shaders compiled OK. Hazzah." << std::endl;
		std::cout.flush();
	}

	::g_pTheShaderManager->UseShaderProgram( "simpleShader" );

	// END OF COPY AND PASTE THINGY

	//ExitOnGLError("ERROR: Could not link the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not link the shader program", __LINE__, __FILE__, ::g_ErrorLog );



	//ModelMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], 
		//                          "ModelMatrix");
	::g_UniformLocation_ModelMatrix = 
		glGetUniformLocation( simpleLighting.ID, "ModelMatrix");

	::g_UniformLocation_ModelMatrixRotOnly = 
		glGetUniformLocation( simpleLighting.ID, "ModelMatrixRotOnly" );


	//ViewMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ViewMatrix");
	::g_UniformLocation_ViewMatrix = glGetUniformLocation(simpleLighting.ID, "ViewMatrix");

	//ProjectionMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ProjectionMatrix");
	::g_UniformLocation_ProjectionMatrix = glGetUniformLocation( simpleLighting.ID, "ProjectionMatrix");


	// Get the uniform locations for the materials of the object
	::g_UniformLocation_ambient = glGetUniformLocation( simpleLighting.ID,
											"myMaterialAmbient" );	
	::g_UniformLocation_diffuse = glGetUniformLocation( simpleLighting.ID,
											"myMaterialDiffuse" );		
	::g_UniformLocation_spec = glGetUniformLocation( simpleLighting.ID,
											"myMaterialSpecular" );		
	::g_UniformLocation_shininess = glGetUniformLocation( simpleLighting.ID,
											"myMaterialShininess" );	

	// The location of the camera (used for the specular calculation)
	::g_UniformLocation_eye = glGetUniformLocation( simpleLighting.ID, "eye" );	

	::g_UniformLocation_bUseDebugColour = glGetUniformLocation( simpleLighting.ID, "bUseDebugColour" );
	::g_UniformLocation_debugColour = glGetUniformLocation( simpleLighting.ID, "debugColour" );

	// Get the uniform locations for the texture variables...

	::g_UniformLocation_texture0 = glGetUniformLocation( simpleLighting.ID, "texture_0" );
	::g_UniformLocation_texture1 = glGetUniformLocation( simpleLighting.ID, "texture_1" );
	::g_UniformLocation_texture2 = glGetUniformLocation( simpleLighting.ID, "texture_2" );
	::g_UniformLocation_texture3 = glGetUniformLocation( simpleLighting.ID, "texture_3" );
	::g_UniformLocation_texture4 = glGetUniformLocation( simpleLighting.ID, "texture_4" );
	::g_UniformLocation_texture5 = glGetUniformLocation( simpleLighting.ID, "texture_5" );
	::g_UniformLocation_skybox = glGetUniformLocation( simpleLighting.ID, "skyMapTexture" );

	::g_UniformLocation_texture_HM_vert = glGetUniformLocation( simpleLighting.ID, "texture_HM_vert" );

	::g_UniformLocation_SelTex_0_ID = glGetUniformLocation( simpleLighting.ID, "SelTex_0_ID" );
	::g_UniformLocation_SelTex_1_ID = glGetUniformLocation( simpleLighting.ID, "SelTex_1_ID" );


	// Get the uniform location for the transparency uniform variable
	::g_UniformLocation_Alpha = glGetUniformLocation( simpleLighting.ID, "alphaValue" );

	::g_UniformLocation_bIsSkyBox = glGetUniformLocation( simpleLighting.ID, "bIsSkyMap" );


	// Note: Clearly, this copying and pasting all these values
	//	is a goofy thing to do (unless you have shares in keyboard
	//	companies and places that do carpal tunnel therapy...)
	// Stong Suggestion: Make some "manager" class that handles 
	//	all these settings and copies the information to the shader

	// This was moved into this function because it was getting very long...
	::SetUpTheLightingUniforms( simpleLighting.ID );

	for ( unsigned int index = 0; index != NUMBEROFLIGHTS; index++ )
	{
		::g_TheLights[index].SetToDefaultWhite();
		::g_TheLights[index].TurnOff();
	}

	// Place the lights in a (soft of) grid pattern
	// They are like this:
	//
	//   [1]@-8,-8       [2]@ 0,-8       [3]@+8,-8
	// 
	// 
	//   [4]@-8, 0       [0]@ 0, 0       [5]@+8, 0
	//                   [9]@ 0,+15      
	//
	//   [6]@-8,+8       [7]@ 0,+8       [8]@+8,+8
	// 
	float lightYOffset = 1.0f;		// 1.0f unit above the origin
	::g_TheLights[0].position = glm::vec3( 0.0f, lightYOffset, 0.0f );

	::g_TheLights[1].position = glm::vec3( -8.0, lightYOffset, -8.0f );
	::g_TheLights[2].position = glm::vec3(    0, lightYOffset, -8.0f );
	::g_TheLights[3].position = glm::vec3(  8.0, lightYOffset, -8.0f );

	::g_TheLights[4].position = glm::vec3( -8.0, lightYOffset,  0.0f );
	::g_TheLights[5].position = glm::vec3(  8.0, lightYOffset,  0.0f );

	::g_TheLights[6].position = glm::vec3( -8.0, lightYOffset,  8.0f );
	::g_TheLights[7].position = glm::vec3(    0, lightYOffset,  8.0f );
	::g_TheLights[8].position = glm::vec3(  8.0, lightYOffset,  8.0f );

	// #9 is at the xz-origin, just "far" above light #0 
	::g_TheLights[9].position = glm::vec3(  0.0, 15.0,  0.0f );

	::g_TheLights[5].SetToDefaultWhite();
	::g_TheLights[5].TurnOn();

	// Turn on light #0
	::g_TheLights[0].diffuse = glm::vec3( 1.0f, 1.0f, 1.0f );
	::g_TheLights[0].ambient = glm::vec3( 0.2f, 0.2f, 0.2f );
	::g_TheLights[0].specular = glm::vec3( 1.0f, 1.0f, 1.0f );
	::g_TheLights[0].attenConst = 0.0f;
	::g_TheLights[0].attenLinear = 0.1f;
	::g_TheLights[0].attenQuad = 0.01f;
	::g_TheLights[0].TurnOn();		// Also sets bIsEnabled = true;




	//if ( !CreateCube() ) 
	//{
		// return false;	// Error
	//}
	//::g_pTheMeshManager = new CModelTypeManager();
	//::g_pTheMeshManager->SetBaseFilePath( "assets/models/" );


	//CMeshType mt_bunny( "bunny", "bun_zipper_res3_xyz.ply" );
	//CMeshType mt_tieFighter( "tie", "tie.ply" );
	//CMeshType mt_mig( "mig", "mig29_xyz.ply" );
	//CMeshType mt_seafloor( "seafloor", "Seafloor2.ply" );
	////CMeshType mt_seafloor( "seafloor", "Terrain_001_(half_height)_vertUV.ply" );

	//CMeshType mt_Cow( "Bessy", "cow.ply" );
	//CMeshType mt_Sphere( "Sphere", "Isoshphere.ply" );
	//CMeshType mt_SphereNorm( "SphereNormals", "Isoshphere_xyz_nxyz.ply" );
	////CMeshType mt_kate( "kate", "KateUpton.ply" );



	//std::string error;
	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_bunny, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_tieFighter, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_mig, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_seafloor, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_Cow, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_Sphere, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//if ( !::g_pTheMeshManager->LoadModelTypeFromFile( mt_SphereNorm, error ) )
	//{
	//	std::cout << error << std::endl;
	//	std::cout.flush();
	//	return false;
	//}

	//LoadMeshDataIntoBuffers( g_vecBunnyVertices, g_vecBunnyTriangles,
		//                      VBO_IDs[BUNNY_ID],
		//				   vertexBuffer_IDs[BUNNY_ID], 
		//				   indexBuffer_IDs[BUNNY_ID] );
	//// Save the VBO ID inside the mesh type array (for the draw later)
	//meshTypes[BUNNY_ID].VBO_ID = VBO_IDs[BUNNY_ID];
	//LoadMeshDataIntoBuffers( g_vecTieVertices, g_vecTieTriangles,
		//                      VBO_IDs[TIE_FIGHTER_ID],
		//				   vertexBuffer_IDs[TIE_FIGHTER_ID], 
		//				   indexBuffer_IDs[TIE_FIGHTER_ID] );
	////
	//meshTypes[TIE_FIGHTER_ID].VBO_ID = VBO_IDs[TIE_FIGHTER_ID];
	//LoadMeshDataIntoBuffers( g_vecMigVertices, g_vecMigTriangles,
		//                      VBO_IDs[MIG_ID],
		//				   vertexBuffer_IDs[MIG_ID], 
		//				   indexBuffer_IDs[MIG_ID] );
	////
	//meshTypes[MIG_ID].VBO_ID = VBO_IDs[MIG_ID];

  return true;
}


// These were moved here because the function was getting way to big
void SetUpTheLightingUniforms( GLuint shaderID )
{

	//// ******************************************************************
	//// Light #0
	//::g_TheLights[0].ShadUnifLoc_position
	//	= glGetUniformLocation( shaderID, "myLights[0].position" );
	//
	//::g_TheLights[0].ShadUnifLoc_ambient
	//	= glGetUniformLocation( shaderID, "myLights[0].ambient" );
	//
	//::g_TheLights[0].ShadUnifLoc_diffuse
	//	= glGetUniformLocation( shaderID, "myLights[0].diffuse" );
	//
	//::g_TheLights[0].ShadUnifLoc_specular
	//	= glGetUniformLocation( shaderID, "myLights[0].specular" );
	//
	//::g_TheLights[0].ShadUnifLoc_attenConst
	//	= glGetUniformLocation( shaderID, "myLights[0].attenConst" );
	//
	//::g_TheLights[0].ShadUnifLoc_attenLinear
	//	= glGetUniformLocation( shaderID, "myLights[0].attenLinear" );
	//
	//::g_TheLights[0].ShadUnifLoc_attenQuad
	//	= glGetUniformLocation( shaderID, "myLights[0].attenQuad" );
	//// End of: Light #0
	//// ******************************************************************
	//
	//// And the rest of the uniforms need to be set, too..............
	//// (BWA-HA-HA!!!)
	
	for ( int index = 0; index != NUMBEROFLIGHTS; index++ )
	{
		std::stringstream ssLight;

		ssLight << "myLights[" << index << "].";

		::g_TheLights[index].UniformLocation_position
			= glGetUniformLocation( shaderID, (ssLight.str() + "position").c_str() );

		::g_TheLights[index].UniformLocation_ambient
			= glGetUniformLocation( shaderID, (ssLight.str() + "ambient").c_str() );

		::g_TheLights[index].UniformLocation_diffuse
			= glGetUniformLocation( shaderID, (ssLight.str() + "diffuse").c_str() );

		::g_TheLights[index].UniformLocation_specular
			= glGetUniformLocation( shaderID, (ssLight.str() + "specular").c_str() );

		::g_TheLights[index].UniformLocation_attenConst
			= glGetUniformLocation( shaderID, (ssLight.str() + "attenConst").c_str() );

		::g_TheLights[index].UniformLocation_attenLinear
			= glGetUniformLocation( shaderID, (ssLight.str() + "attenLinear").c_str() );

		::g_TheLights[index].UniformLocation_attenQuad
			= glGetUniformLocation( shaderID, (ssLight.str() + "attenQuad").c_str() );

	}// for ( int index = 0;...

	return;
}
