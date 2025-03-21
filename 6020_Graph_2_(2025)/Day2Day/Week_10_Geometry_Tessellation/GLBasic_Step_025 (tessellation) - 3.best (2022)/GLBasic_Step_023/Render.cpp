#include "global.h"

#include <sstream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/quaternion.hpp>	// For quaternion stuff

#include <iomanip>		// for the floating point precision settings on the title

#include "CGLColourHelper.h"



// JUST FOR DEBUGGING
#include "CPhysicsWorld.h"

#include <iostream>



unsigned FrameCount = 0;

float CubeRotation = 0;
clock_t LastTime = 0;

#include "CRoom.h"


void TimerFunction(int Value)
{
  if (0 != Value) 
  {
	//char* TempString = (char*)
	//  malloc(512 + strlen(WINDOW_TITLE_PREFIX));

	//sprintf(
	//  TempString,
	//  "%s: %d Frames Per Second @ %d x %d",
	//  WINDOW_TITLE_PREFIX,
	//  FrameCount * 4,
	//  CurrentWidth,
	//  CurrentHeight
	//);

	std::stringstream ss;
	//ss << WINDOW_TITLE_PREFIX << ": " 
	//	<< FrameCount * 4 << " Frames Per Second @ "
	//	<< CurrentWidth << " x "
	//	<< CurrentHeight;

	ss << "Light[" << ::g_selectedLightID << "]: "
		<< ::g_TheLights[::g_selectedLightID].GetLightInfoString();
		//<< std::fixed << std::setprecision(3)			// Fixed precision and 3 decimal places
		//<< " pos: " << ::g_TheLights[::g_selectedLightID].position.x << ", " << ::g_TheLights[::g_selectedLightID].position.y << ", " << ::g_TheLights[::g_selectedLightID].position.y
		//<< " attenConst: " << ::g_TheLights[::g_selectedLightID].attenConst
		//<< " attenLin: " << ::g_TheLights[::g_selectedLightID].attenLinear
		//<< " attenQuad: " << ::g_TheLights[::g_selectedLightID].attenQuad;


//    glutSetWindowTitle(ss.str().c_str());
	//glutSetWindowTitle(TempString);
	//free(TempString);
  }

  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);

  return;
}

static float lightX = 2.0f;
static float lightY = 0.5f;
static float lightZ = -2.0f;

//CGameObject* findGameObjectByFriendlyName( std::string friendlyName )
//{
//	for ( std::vector< CGameObject* >::iterator itGO = ::g_vec_pTheObjects.begin();
//		  itGO != ::g_vec_pTheObjects.end(); itGO++ )
//	{
//		if ( (*itGO)->friendlyName == friendlyName )
//		{	// Found it
//			return (*itGO);
//		}
//	}
//	// Didn't find it
//	return 0;
//}
//
//CGameObject* findGameObjectByID( unsigned int ID )
//{
//	for ( std::vector< CGameObject* >::iterator itGO = ::g_vec_pTheObjects.begin();
//		  itGO != ::g_vec_pTheObjects.end(); itGO++ )
//	{
//		if ( (*itGO)->GetID() == ID )
//		{	// Found it
//			return (*itGO);
//		}
//	}
//	// Didn't find it
//	return 0;
//}



void DrawTestDebugPhysics(void);

void DrawRoom( CRoom theRoom, CGameObject* pRoomObject, bool bDrawOnlyDoors, CGameObject* pDoorObject, unsigned int drawPassNumber );

void RenderFunction(void)
{
  ++FrameCount;

  //glClearColor( x, 0.1f, 0.1f, 0.0f );

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Point the camera at something... 
	matView = glm::lookAt(
		glm::vec3(::g_cameraEyeX, ::g_cameraEyeY, ::g_cameraEyeZ),	// Camera (aka "Eye")
		glm::vec3(::g_cameraAtX, ::g_cameraAtY, ::g_cameraAtZ),	// At (aka "target")
		glm::vec3(0.0f, 1.0f, 0.0f) );	// Up

	::g_pTheShaderManager->UseShaderProgram( 0 );
	::g_pTheShaderManager->UseShaderProgram( "simpleShader" );

	//ExitOnGLError("ERROR: Could not use the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not use the shader program", __LINE__, __FILE__, ::g_ErrorLog );

	// Set all "scene based" things. i.e. things that change only 
	//	once per "frame"
	glUniform3f( g_UniformLocation_eye, ::g_cameraEyeX, ::g_cameraEyeY, ::g_cameraEyeZ );		

	// Find the light
	//CGameObject* pLight00 = findGameObjectByID( "Light00" );
	//if ( pLight00 != 0 )
	//{
	//	lightX = pLight00->position.x;
	//	lightY = pLight00->position.y;
	//	lightZ = pLight00->position.z;
	//}

	//for ( int index = 0; index != 1; index++ )
	for ( int index = 0; index != NUMBEROFLIGHTS; index++ )
	{
		//mySexyLights[index].SetRandomDiffuse();

		if ( ::g_TheLights[index].bIsEnabled )
		{
			glUniform3f( ::g_TheLights[index].UniformLocation_position, 
						 ::g_TheLights[index].position.x, 
						 ::g_TheLights[index].position.y, 
						 ::g_TheLights[index].position.z );

			glUniform3f( ::g_TheLights[index].UniformLocation_diffuse, 
						 ::g_TheLights[index].diffuse.x, 
						 ::g_TheLights[index].diffuse.y, 
						 ::g_TheLights[index].diffuse.z );	

			glUniform3f( ::g_TheLights[index].UniformLocation_ambient, 
						 ::g_TheLights[index].ambient.x, 
						 ::g_TheLights[index].ambient.y, 
						 ::g_TheLights[index].ambient.z );

			glUniform3f( ::g_TheLights[index].UniformLocation_specular, 
						 ::g_TheLights[index].specular.x, 
						 ::g_TheLights[index].specular.y, 
						 ::g_TheLights[index].specular.z );		

			glUniform1f( ::g_TheLights[index].UniformLocation_attenConst, 
						 ::g_TheLights[index].attenConst );	

			glUniform1f( ::g_TheLights[index].UniformLocation_attenLinear, 
						 ::g_TheLights[index].attenLinear );	

			glUniform1f( ::g_TheLights[index].UniformLocation_attenQuad, 
						 ::g_TheLights[index].attenQuad );	
		}//if ( ::g_TheLights[index].bIsEnabled )
	}//for ( int index = 0...

	//glUniform3f( myLightPosition_ID, lightX, lightY, lightZ );

	//lightZ += 0.005f; 
	//lightX -= 0.001f;

extern bool g_bTessellateOnlyEdges;

	GLuint curShadID = ::g_pTheShaderManager->GetCurrentShaderID();
	::g_pTheShaderManager->SetUniformVar1f(curShadID, 
		                                   "tessRatioOuter", ::g_tessellationRatioOuter );
	::g_pTheShaderManager->SetUniformVar1f(curShadID, 
		                                   "tessRatioInner", ::g_tessellationRatioInner );
	// Note: We are using the "default uniform block" in the tess eval shader,
	//	so we have to pass this here (as well as in the fragment shader)
	// If you don't want to do this, use a "named uniform block"
	::g_pTheShaderManager->SetUniformVar3f(curShadID, 
		    "tessEyePos", ::g_cameraEyeX, ::g_cameraEyeY, ::g_cameraEyeZ );        

	// And these things, too (we'll use them in a moment)
	::g_pTheShaderManager->SetUniformVar1f(curShadID, 
		                      "tessDistance", ::g_tessellationDistance );

	::g_pTheShaderManager->SetUniformVar1f(curShadID, 
		                      "tessEdgeDotProdThresh", ::g_tessellationEdgeDotProductThreshold );
	
	if ( ::g_bTessellateOnlyEdges )
	{
		::g_pTheShaderManager->SetUniformVar1f( curShadID, "bTessOnlyEdges", static_cast<GLfloat>( GL_TRUE ) );
	}
	else 
	{
		::g_pTheShaderManager->SetUniformVar1f( curShadID, "bTessOnlyEdges", static_cast<GLfloat>( GL_FALSE ) );
	}

	::g_pTheShaderManager->SetUniformVar1f(curShadID, 
		                      "hackNormalProdrudeAdjustRatio", ::g_tessNormProtrudeValue );

	// We aren't passing the size of the vector anymore. 
	// (it's contained inside each game object)
	DrawScene( );

  glutSwapBuffers();

  return;
}



// Used to be in DrawScene.
// Draws a SINGLE object
//void DrawObject( std::vector< CGameObject* >::iterator &itCurrentGO,
//				 // BOOM goes the dynomite!!!
//				 const glm::mat4 &matModelParent, 
//				 const glm::mat4 &matModelParentRotOnly )
void DrawObject( CGameObject* pCurrentGO,			// Pass a pointer instead
				 // BOOM goes the dynomite!!!
				 const glm::mat4 &matModelParent, 
				 const glm::mat4 &matModelParentRotOnly, unsigned int drawPassNumber )
{
	// Get a pointer to the game object.
	// (This is mainly so we can debug the stupid thing, since Visual Studio won't resolve the iterator... why? who knows?)
	//CGameObject* pCurrentGO = (*itCurrentGO);

	// Visible?
	if ( ! pCurrentGO->bIsVisible )
	{	// Don't draw it (or its children - we might want to change this later)
		return;
	}

	glm::mat4 matModel = matModelParent;
	glm::mat4 matModelRotOnly = matModelParentRotOnly;


	// Rotation (post)
	matModel = glm::rotate( matModel, pCurrentGO->postRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f) );
	matModel = glm::rotate( matModel, pCurrentGO->postRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f) );
	matModel = glm::rotate( matModel, pCurrentGO->postRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f) );

	matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->postRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f) );
	matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->postRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f) );
	matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->postRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f) );


	// Translation 
	matModel = glm::translate( matModel, 
								glm::vec3( pCurrentGO->position.x, pCurrentGO->position.y, pCurrentGO->position.z) );
	// Rotation (pre)
	// #include <glm/gtx/quaternion.hpp>
	glm::mat4 matQRotation = glm::toMat4( pCurrentGO->qOrientation );

	//matModel = glm::rotate( matModel, pCurrentGO->preRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f) );
	//matModel = glm::rotate( matModel, pCurrentGO->preRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f) );
	//matModel = glm::rotate( matModel, pCurrentGO->preRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f) );
	matModel *= matQRotation;		// Combine rotation matrix to model matrix

	//matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->preRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f) );
	//matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->preRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f) );
	//matModelRotOnly = glm::rotate( matModelRotOnly, pCurrentGO->preRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f) );
	matModelRotOnly *= matQRotation;

	// Scale 
	matModel = glm::scale( matModel, glm::vec3( pCurrentGO->scale, pCurrentGO->scale, pCurrentGO->scale ) );


	// add the "wireframe" stuff...
	if ( pCurrentGO->bIsWireframe )
	{	// Wireframe...
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//glCullFace( GL_NONE );
		glDisable( GL_CULL_FACE );
	}
	else
	{	// Not wireframe
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		//glCullFace( GL_BACK );
		glEnable( GL_CULL_FACE );
	}

	//glDisable( GL_CULL_FACE );

	//glCullFace( GL_NONE );
	//glDisable( GL_CULL_FACE );
 
	//glUseProgram(ShaderIds[0]);
	// The ends up calling the same line as above. If you follow the code through, 
	//	you'll see that the shader manager looks up the shader by name, then calls
	//	glUseProgram with the ID that OpenGL gave it.

	//::g_pTheShaderManager->UseShaderProgram( 0 );
	//::g_pTheShaderManager->UseShaderProgram( "simpleShader" );

	//ExitOnGLError("ERROR: Could not use the shader program");

	//	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, 
	//		               GL_FALSE, ViewMatrix.m);
	//::g_pTheShaderManager->SetUniformVar4f( "simpleShader", 
	//	                                    "ViewMatrix", 
	//										glm::value_ptr(matView) );

	//ExitOnGLError("ERROR: Could not use the shader program");

	glUniformMatrix4fv( g_UniformLocation_ViewMatrix, 1, 
						GL_FALSE, glm::value_ptr(matView) );

	//ExitOnGLError("ERROR: Could not use the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not bind the VAO for drawing purposes", __LINE__, __FILE__, ::g_ErrorLog );


	//	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, 
	//		               GL_FALSE, ModelMatrix.m);

	glUniformMatrix4fv( g_UniformLocation_ModelMatrix, 1, 
						GL_FALSE, glm::value_ptr(matModel));
	//ExitOnGLError("ERROR: Could not use the shader program");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not use the shader program", __LINE__, __FILE__, ::g_ErrorLog );

	glUniformMatrix4fv( g_UniformLocation_ModelMatrixRotOnly, 1,
						GL_FALSE, glm::value_ptr(matModelRotOnly) );

	// Now set the colour of the object
	// (i.e. set the sexyVariable uniform in the fragment shader)
	//glUniform4f( SexyVariableID, (*itGO)->red,		// 0.0f, // red
	//	                         (*itGO)->green,	// 1.0f, // green 
	//							 (*itGO)->blue,	// 0.0f, // blue
	//							 1.0f );	// Alpha
	glUniform3f( g_UniformLocation_ambient, pCurrentGO->ambient.x, pCurrentGO->ambient.y, pCurrentGO->ambient.z );		// Orange is the new
	glUniform3f( g_UniformLocation_diffuse, pCurrentGO->diffuse.x, pCurrentGO->diffuse.y, pCurrentGO->diffuse.z );		// Orange is the new
	glUniform3f( g_UniformLocation_spec, pCurrentGO->specular.x, pCurrentGO->specular.y, pCurrentGO->specular.z );		// Orange is the new
	float shine = pCurrentGO->shininess;
	glUniform1f( g_UniformLocation_shininess, pCurrentGO->shininess );		// Orange is the new

	// Turns ON the fixed function blend (i.e. alpha) 
	glEnable( GL_BLEND );		// Enables "blending"
	//glDisable( GL_BLEND );
	// Source == already on framebuffer
	// Dest == what you're about to draw
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Added: transparency
	glUniform1f( ::g_UniformLocation_Alpha, pCurrentGO->alphaTransparency );
	////// ***********************************************************
	////// Set selected texture 
	static const GLuint NOTEXTURESELECTED = 1000;


	// What texture does our object want... they are listed by name
	{
		GLuint objText0ID = NOTEXTURESELECTED;
		std::string texture0NameDebug = pCurrentGO->textureName0;
		if ( texture0NameDebug == "mt-ruapehu-and-mt-ngauruhoe.bmp" )
		{
			int sexy = 0;
		}
		if ( ! ::g_pTheTextureManager->GetTexUnitFromName( texture0NameDebug, objText0ID ) )
		{
			objText0ID = NOTEXTURESELECTED;
		}
		else 
		{
			objText0ID -= GL_TEXTURE0;
		}

		glUniform1i( ::g_UniformLocation_SelTex_0_ID, objText0ID );
	}

	{
		GLuint objText1ID = NOTEXTURESELECTED;
		std::string texture1NameDebug = pCurrentGO->textureName1;
		if ( ! ::g_pTheTextureManager->GetTexUnitFromName( texture1NameDebug, objText1ID ) )
		{
			objText1ID = NOTEXTURESELECTED;
		}
		else 
		{
			objText1ID -= GL_TEXTURE0;
		}
		glUniform1i( ::g_UniformLocation_SelTex_1_ID, objText1ID );
	}

	// false for bool is 0 or 0.0f; true is anything else
	// Can be set with the i, ui, or f variants of glUniform
	glUniform1f( ::g_UniformLocation_bUseDebugColour, static_cast<GLfloat>( GL_FALSE ) );	
	if ( pCurrentGO->bUseDebugColour )
	{
		glUniform1f( ::g_UniformLocation_bUseDebugColour, static_cast<GLfloat>( GL_TRUE ) );	
		// The last parameter, which is often the 'alpha' (aka 'transparency') is being 
		//	passes as 1.0; since we are using a 'debug colour', we likely don't want it transparent
		// (reminder: 0.0f == fully transparent, 1.0f == fully solid (opaque)
		glUniform4f( ::g_UniformLocation_debugColour, pCurrentGO->debugColour.x, pCurrentGO->debugColour.y, pCurrentGO->debugColour.z, 1.0f );
	}

	// Is this a skybox?
	glUniform1f( g_UniformLocation_bIsSkyBox, static_cast<GLfloat>( GL_FALSE ) );
	glEnable( GL_DEPTH );
	glEnable( GL_CULL_FACE );
	if ( pCurrentGO->bIsSkyBox )
	{
		// Turn off alpha blending
		glDisable( GL_BLEND );		// No transparency, so speed things along
		glDisable( GL_DEPTH );
		glDisable( GL_CULL_FACE );	// Our normals point "out" and we are inside the isophere
		glUniform1f( g_UniformLocation_bIsSkyBox, static_cast<GLfloat>( GL_TRUE ) );
	}


	//ExitOnGLError("ERROR: Could not set the shader uniforms");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not set the shader uniforms", __LINE__, __FILE__, ::g_ErrorLog );

	unsigned int numberOfIndices = pCurrentGO->numberOfTriangles * 3;
 
	// We point (bind) to the particular vertex buffer
	if ( ! pCurrentGO->bUseLOD )
	{
		glBindVertexArray(  pCurrentGO->Cached_VBO_ID );
		numberOfIndices = pCurrentGO->numberOfTriangles * 3;
	}
	else
	{	// use LOD rendering
		glm::vec3 eye( ::g_cameraEyeX, ::g_cameraEyeY, ::g_cameraEyeZ );

		float distance = fabs( glm::distance( eye, pCurrentGO->position ) );

		// Based on the distance, pick the particular model
		if ( distance <= 5.0f )	// Closest, so highest res model
		{
			glBindVertexArray(  pCurrentGO->Cached_VBO_ID_LOD[0] );
			numberOfIndices = pCurrentGO->LOD_NumberOfTriangles[0] * 3;
		}
		else if ( distance <= 10.0f )
		{
			glBindVertexArray(  pCurrentGO->Cached_VBO_ID_LOD[1] );
			numberOfIndices = pCurrentGO->LOD_NumberOfTriangles[1] * 3;
		}
		else if ( distance <= 50.0f )
		{
			glBindVertexArray(  pCurrentGO->Cached_VBO_ID_LOD[2] );
			numberOfIndices = pCurrentGO->LOD_NumberOfTriangles[2] * 3;
		}
		else 
		{
			glBindVertexArray(  pCurrentGO->Cached_VBO_ID_LOD[3] );
			numberOfIndices = pCurrentGO->LOD_NumberOfTriangles[3] * 3;
		}

		//numberOfIndices
	}

	//ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");
	COpenGLError::LogOpenGLErorrIfPresent( "ERROR: Could not bind the VAO for drawing purposes", __LINE__, __FILE__, ::g_ErrorLog );

	// Do we draw this on this pass?
	if ( pCurrentGO->bDrawOnPass[drawPassNumber] )
	{
		//unsigned int numberOfIndices = pCurrentGO->numberOfTriangles * 3;
		//glDrawElements(GL_TRIANGLES, numberOfIndices, 
		//				GL_UNSIGNED_INT, 
		//				(GLvoid*)0);

		// Because we are using the tessellator, you aren't sending 'triangles', but 'triangle patches'
		// In other words, the verticies aren't being used "as vertices", but as control points TO GENERATE
		//	triangles (lots and lots of triangles, maybe)

		// Here we tell the tessellator what kind of control "patches" we are sending 
		// (lines, triangles, or quads)
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		glDrawElements(GL_PATCHES, numberOfIndices, 
						GL_UNSIGNED_INT, 
						(GLvoid*)0);
	}

	// Now the magic....
	// Go through this object, drawing all the children...
	for ( std::vector< CGameObject* >::iterator itChildObject 
					= pCurrentGO->vec_pChildObjects.begin();
		itChildObject != pCurrentGO->vec_pChildObjects.end();
		itChildObject++ )
	{
		// DON'T reset the world matrix. 
		// Apply the opposite of scale to "clear" the scale of the model
		glm::mat4 matChildWorld = glm::scale( matModel, glm::vec3( 1.0f/pCurrentGO->scale, 1.0f/pCurrentGO->scale, 1.0f/pCurrentGO->scale ) );

		CGameObject* pGO = (*itChildObject);	// pointer to child object

		DrawObject( pGO, matChildWorld, matModelRotOnly, drawPassNumber );
//		DrawObject( itChildObject, matChildWorld, matModelRotOnly );
	}

	return;
}


// Same as other DrawObject, but sets an identity for parent and model matrices
void DrawObject( CGameObject* pCurrentGO, unsigned int drawPassNumber )
{
	glm::mat4 matModelParent(1.0f);
	glm::mat4 matModelParentRotOnly(1.0f);

	DrawObject( pCurrentGO, matModelParent, matModelParentRotOnly, drawPassNumber );

	return;
}


void DrawGLText( std::string textToDraw, glm::vec3 position, glm::quat orientation, 
				 CGLPrintf::eAlignmentHorizonal alignment, 
				 glm::vec3 diffuse, CAABB &AABB, unsigned int drawPassNumber, float relativeScale = 1.0f )
{
//	std::cout << "****************************************" << std::endl;

	// Draw some text
	std::vector< CGLPrintf::sCharRenderInfo > vecCharacters;
//	::g_pGLPrintf->GetRenderListForString( textToDraw, vecCharacters, position, orientation, relativeScale );

	CGLPrintf::sRenderFormat renderFormat;
	renderFormat.alignmentHorzontal = alignment;
	renderFormat.qOrientation = orientation;
	renderFormat.startPosition = position;
	renderFormat.relativeScale = relativeScale;

//	::g_pGLPrintf->GetRenderListForString( textToDraw, vecCharacters, position, orientation, AABB, relativeScale );
	::g_pGLPrintf->GetRenderListForString( textToDraw, renderFormat, vecCharacters );

	AABB = renderFormat.AABB;

	//std::cout << "Character: " 
	//	<< vecCharacters[0].ASCII_Value << "): "
	//	<< vecCharacters[0].position.x << ", "
	//	<< vecCharacters[0].position.y << ", "
	//	<< vecCharacters[0].position.z << std::endl;

	for ( int index = 0; index != vecCharacters.size(); index++ )
	{

		vecCharacters[index].pGO->pushRenderingState();

		glm::vec3 debugPosition = vecCharacters[index].position;

		vecCharacters[index].pGO->position = vecCharacters[index].position;
		vecCharacters[index].pGO->qOrientation = vecCharacters[index].orientation;
		bool bOldVisibilityState = vecCharacters[index].pGO->bIsVisible;
		vecCharacters[index].pGO->bIsVisible = true;

		vecCharacters[index].pGO->diffuse = diffuse;
		vecCharacters[index].pGO->ambient = diffuse * 0.2f;
		vecCharacters[index].pGO->scale = vecCharacters[index].scale;

		DrawObject( vecCharacters[index].pGO, glm::mat4(1.0f), glm::mat4(1.0f), drawPassNumber );
		
		//std::cout << char(vecCharacters[index].ASCII_Value) << " - "
		//	<< "pos: " << vecCharacters[index].pGO->zz_DEBUG_getPositionAsString() 
		//	<< "; angle: " << vecCharacters[index].pGO->zz_DEBUG_getOrientationAsString(true) 
		//	<< std::endl;

		vecCharacters[index].pGO->popRenderingState();
		vecCharacters[index].pGO->bIsVisible = bOldVisibilityState;
	}
	return;
}

static float textPosY = -5.0f;

void DrawDebugBallAtLocation( glm::vec3 position, unsigned int drawPassNumber, float scale = 1.0f )
{
	CGameObject* pBall = ::g_pGameObjectManager->FindGameObjectByFriendlyName("YellowDebugBall");
	pBall->pushRenderingState();
	pBall->position = position;
	pBall->scale = scale;
	DrawObject( pBall, glm::mat4(1.0f), glm::mat4(1.0f), drawPassNumber );
	pBall->popRenderingState();
	return;
}

static float angle = 0.0f;

void DrawEverything( unsigned int passNumber )
{
	// ***************************************************
	// Loop throught all the objects in the vector...
	std::vector< CGameObject* > vec_pGameObjects;
	::g_pGameObjectManager->AppendListOfObjectsToRender( vec_pGameObjects );
	for ( std::vector< CGameObject* >::iterator itGO = vec_pGameObjects.begin();
		itGO != vec_pGameObjects.end();
		itGO++ )
	{
		// All of this has been moved to DrawObject();
		// Note: vecTriangles will be removed... 

		// this matModel used to be global, now we are passing it
		glm::mat4 matModel = glm::mat4(1.0f);
		glm::mat4 matModelRotOnly = glm::mat4(1.0f);

		CGameObject* pCurrentGO = (*itGO);

		// If the object IS transparnt, DON'T draw it, yet
		if ( (*itGO)->alphaTransparency >= 1.0f )
		{	// Draws all NON-transparent objects
			DrawObject( pCurrentGO, matModel, matModelRotOnly, passNumber );
		}
	}

	// Now draw all TRANSPARENT objects
	// (i.e. you are drawing the transparent objects LAST)
	// If there is MORE than one transparent object, you want to draw them 
	//	from BACK to FRONT **RELATIVE TO THE CAMERA**
	for ( std::vector< CGameObject* >::iterator itGO = vec_pGameObjects.begin();
		itGO != vec_pGameObjects.end();
		itGO++ )
	{
		// All of this has been moved to DrawObject();
		// Note: vecTriangles will be removed... 

		// this matModel used to be global, now we are passing it
		glm::mat4 matModel = glm::mat4(1.0f);
		glm::mat4 matModelRotOnly = glm::mat4(1.0f);

		CGameObject* pCurrentGO = (*itGO);

		// If the object IS transparnt, DRAW it
		// (DON'T draw 
		if ( (*itGO)->alphaTransparency < 1.0f )
		{	// Draws all NON-transparent objects
			DrawObject( pCurrentGO, matModel, matModelRotOnly, passNumber );
		}
	}

	return;
}


//void DrawScene( std::vector<CTriangle> &vecTriangles )
void DrawScene( void )
{
	//float CubeAngle;
	clock_t Now = clock();

	if (LastTime == 0)
	LastTime = Now;

	//CubeRotation += 45.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	//CubeAngle = DegreesToRadians(CubeRotation);

	//BunnyPosX += 0.1f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	LastTime = Now;

	::g_pTheTextureManager->UpdateTextureBindings();

	//glUniform1ui( ::g_UniformLocation_texture0, tex0UnitID - GL_TEXTURE0);
	//glUniform1ui( ::g_UniformLocation_texture0, textureUnit0);
	//////glUniform1ui( ::g_UniformLocation_texture1, tex1UnitID - GL_TEXTURE0 );
	glUniform1i( ::g_UniformLocation_texture0, 0 );		// grass
	glUniform1i( ::g_UniformLocation_skybox, 1 );		// Skybox
	glUniform1i( ::g_UniformLocation_texture1, 2 );		// Mud
	glUniform1i( ::g_UniformLocation_texture2, 3 );		// mt-ruapehu-and-mt-ngauruhoe.bmp
	glUniform1i( ::g_UniformLocation_texture3, 3 );		
	glUniform1i( ::g_UniformLocation_texture4, 5 );		
	glUniform1i( ::g_UniformLocation_texture5, 6 );		
	////// ***********************************************************

	glUniform1i( ::g_UniformLocation_texture_HM_vert, 3 );

	CGameObject* pRoomObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Room");
	CGameObject* pDoorObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Door");

	pRoomObject->bIsWireframe = false;
	pDoorObject->bIsWireframe = false;

//	pDoorObject->diffuse = CGLColourHelper::getInstance()->getComplimentaryRGB( pRoomObject->diffuse );
	pDoorObject->diffuse = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_CADET_BLUE );
	pDoorObject->ambient = pDoorObject->diffuse * 0.2f;

	// Pass #0: Room, the skybox, and the "water" ground object
	DrawEverything( 0 );		// Pass number being passed at the end


	glBindVertexArray(0);
	glUseProgram(0);

	return;
}


float calcDistanceBetweenTwoPoints( glm::vec3 a, glm::vec3 b )
{
	return sqrt( pow(a.x-b.x, 2) + pow(a.y-b.y, 2) + pow( a.z-b.z, 2) );
}

void DrawTestDebugPhysics(void)
{
	
	// Use the position of bug bunny as the point to test
	CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "BugsBunny" );

	// Use the ground to get at the ply model to get at the triangles
	CGameObject* pGround = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "Ground" );
	

	CMeshType meshGround;
	meshGround.filename = pGround->plyModelName;
	std::string error = "";
	if ( ! ::g_pModelTypeManger->GetModelInfoByFileName( meshGround, error ) )
	{
		// Can not find the mesh information
		return;
	}

	CPhysicsWorld tempPhysWorld;

	// Draw the closest point on all the triangles in the ground mesh
	unsigned int numTriangles = meshGround.pPlyFile->GetNumberOfElements();
	for ( unsigned int triIndex = 0; triIndex != numTriangles; triIndex++ )
	{
		PlyElement curTriangle = meshGround.pPlyFile->getElement_at( triIndex );

		// Get the three corners of this triangle
		PlyVertex vertA = meshGround.pPlyFile->getVertex_at( curTriangle.vertex_index_1 );
		PlyVertex vertB = meshGround.pPlyFile->getVertex_at( curTriangle.vertex_index_2 );
		PlyVertex vertC = meshGround.pPlyFile->getVertex_at( curTriangle.vertex_index_3 );

		glm::vec3 cornerA = glm::vec3( vertA.xyz.x, vertA.xyz.y, vertA.xyz.z );
		glm::vec3 cornerB = glm::vec3( vertB.xyz.x, vertB.xyz.y, vertB.xyz.z );
		glm::vec3 cornerC = glm::vec3( vertC.xyz.x, vertC.xyz.y, vertC.xyz.z );

		// The ground isn't at the origin, so adjust the location of each triangle
		cornerA += pGround->position;
		cornerB += pGround->position;
		cornerC += pGround->position;

		bool bIsAboveTriangle = false;
		glm::vec3 closestPoint = 
			tempPhysWorld.ClosestPtPointTriangle( pBunny->position, cornerA, cornerB, cornerC, bIsAboveTriangle );

		// Speed up: is this within a sphere near the object?
		// (so we don't have to draw thousands of spheres that are "too" far away)

		const float FURTHESTDISTANCE = 25.0f;
		if ( calcDistanceBetweenTwoPoints( closestPoint, pBunny->position ) <= FURTHESTDISTANCE )
		{

			// Added just for debugging the triangle-sphere intersection
			CGameObject* pTempObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "ClosetPointBall" );

			std::vector< CGameObject* > vec_pTempDebugObjects;
			vec_pTempDebugObjects.push_back( pTempObject );
			// Points "iterator" object (a thing to "get at" the contents of the vector or container)
			//	to the 1st object in the container vec_pTempDebugObjects[0]
			//  "begin()" returns the 1st object
			std::vector< CGameObject* >::iterator itBall = vec_pTempDebugObjects.begin();

			//(*itBall)->position.x = x;
			(*itBall)->position = closestPoint;

			// change ball colour if point is "above" (or below) the triangle
			// (this is the region defined by the normals to the surface of the triangle)
			(*itBall)->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW );
			if ( bIsAboveTriangle )
			{
				(*itBall)->debugColour = CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_LIME_GREEN );
			}

			glm::mat4 matTempModel = glm::mat4(1.0f);
			glm::mat4 matTempModelRotOnly = glm::mat4(1.0f);	

			CGameObject* pGO = (*itBall);

			DrawObject( pGO, matTempModel, matTempModelRotOnly, 0 );
		}// if ( calcDistanceBetweenTwoPoints(...

	}//for ( unsigned int triIndex ...




	return;
}

//enum enumDirection
//{
//	ZPOS_NORTH_AWAY,
//	XPOS_EAST_RIGHT,
//	XNEG_WEST_LEFT,
//	ZNEG_SOUTH_TOWARDS
//};

void DrawDoor( CRoom::enumDirection theDirection, float roomWidth, glm::vec3 roomPosition, glm::vec4 colour, CGameObject* pDoorObject, unsigned int drawPassNumber )
{

	pDoorObject->pushRenderingState();
	pDoorObject->bIsVisible = true;
	//pDoorObject->bIsWireframe = false;
	//if ( ::g_bDrawRoomsAsWireframe )
	//{
//		pDoorObject->bIsWireframe = ::g_bDrawRoomsAsWireframe;
	//}


	//CGameObject* pDoor = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Door");
	pDoorObject->position = roomPosition;

	float staticOffset = 0.1f;

	// Offset door relative to room (aligned with wall)
	// And align the door to face the room
	switch ( theDirection )
	{
	case CRoom::ZPOS_NORTH_AWAY:
		pDoorObject->position.z = roomPosition.z + (roomWidth/2.0f) - staticOffset;
		pDoorObject->setOrientationFromEuler( glm::vec3( 0.0f, glm::radians(-180.0f), 0.0f ) );
		break;
	case CRoom::XPOS_EAST_RIGHT:
		pDoorObject->position.x = roomPosition.x + (roomWidth/2.0f) - staticOffset;
		pDoorObject->setOrientationFromEuler( glm::vec3( 0.0f, glm::radians(-90.0f), 0.0f ) );
		break;
	case CRoom::XNEG_WEST_LEFT:
		pDoorObject->position.x = roomPosition.x - (roomWidth/2.0f) + staticOffset;
		pDoorObject->setOrientationFromEuler( glm::vec3( 0.0f, glm::radians(90.0f), 0.0f ) );
		break;
	case CRoom::ZNEG_SOUTH_TOWARDS:
		pDoorObject->position.z = roomPosition.z - (roomWidth/2.0f) + staticOffset;
		pDoorObject->setOrientationFromEuler( glm::vec3( 0.0f, glm::radians(0.0f), 0.0f ) );
		break;
	// Else, we are going to draw the door at the centre of the room... yikes!
	}

	// Make door same colour as room
//	pDoorObject->diffuse = glm::vec3( colour );
//	pDoorObject->ambient = pDoorObject->diffuse * 0.2f;
	glm::vec3 doorColour( colour );
	doorColour.r = 1.0f - colour.r;
	doorColour.g = 1.0f - colour.g;
	doorColour.b = 1.0f - colour.b;
	pDoorObject->diffuse = doorColour;
	pDoorObject->ambient = pDoorObject->diffuse * 0.2f;

	// Draw it!
	DrawObject( pDoorObject, glm::mat4(1.0f), glm::mat4(1.0f), drawPassNumber );

	pDoorObject->popRenderingState();
	return;
}

void DrawRoom( CRoom theRoom, CGameObject* pRoomObject, bool bDrawOnlyDoors, CGameObject* pDoorObject, unsigned int drawPassNumber )
{
	// This was added for the stencil buffer example
	if ( ! bDrawOnlyDoors )
	{
		//// Find the game object for the room
		//CGameObject* pRoom = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Room");
		//CGameObject* pDoor = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Door");
		pDoorObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Door");
		// 
		pRoomObject->pushRenderingState();		// Save old position

	
		// Set the the position
		pRoomObject->position = theRoom.position;
		pRoomObject->diffuse = glm::vec3( theRoom.colour );
		pRoomObject->ambient = glm::vec3( theRoom.colour * 0.2f );
		pRoomObject->bIsVisible = true;
	//	pRoomObject->bIsWireframe = ::g_bDrawRoomsAsWireframe;

		DrawObject( pRoomObject, glm::mat4(1.0f), glm::mat4(1.0f), drawPassNumber );

		// Draw the room ID number (which is an integer number)
		std::stringstream ssRoomID;	ssRoomID << "RoomID: ";// << theRoom.getRoomID();
		glm::vec4 RGBCompRoom = CGLColourHelper::getInstance()->getComplimentaryRGBA( theRoom.colour );
		CAABB AABB;
		DrawGLText( ssRoomID.str(),	theRoom.position, 
					glm::quat( glm::vec3(0.0f,0.0f,0.0f) ), CGLPrintf::CENTRE_ALIGNED, glm::vec3(RGBCompRoom), AABB, drawPassNumber, 1.0f );
	}
	
	// Draw doors if there are no children
	// West door
	if ( theRoom.pRoom_XNeg == NULL )		
	{
		DrawDoor( CRoom::XNEG_WEST_LEFT, theRoom.getRoomWidth(), theRoom.position, theRoom.colour, pDoorObject, drawPassNumber );
	}

	if ( theRoom.pRoom_XPos == NULL )
	{
		DrawDoor( CRoom::XPOS_EAST_RIGHT, theRoom.getRoomWidth(), theRoom.position, theRoom.colour, pDoorObject, drawPassNumber );
	}

	if ( theRoom.pRoom_ZPos == NULL )
	{
		DrawDoor( CRoom::ZPOS_NORTH_AWAY, theRoom.getRoomWidth(), theRoom.position, theRoom.colour, pDoorObject, drawPassNumber );
	}

	if ( theRoom.pRoom_ZNeg == NULL )
	{
		DrawDoor( CRoom::ZNEG_SOUTH_TOWARDS, theRoom.getRoomWidth(), theRoom.position, theRoom.colour, pDoorObject, drawPassNumber );
	}

	// Retore old position
	pRoomObject->popRenderingState();
	return;
}



















// OLD code
//if ( ::g_bDrawRooms )
//{
//	// ***********************
////	// Draw the maze of rooms
//	std::vector< CRoom* > vec_pRooms;
//	::g_pMasterRoom->GetListOfRooms( vec_pRooms );
//	
//	// Find the game object for the room
//	CGameObject* pRoomObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Room");
//	CGameObject* pDoorObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Door");
//
//	for ( std::vector< CRoom* >::iterator it_pRooms = vec_pRooms.begin();
//		  it_pRooms != vec_pRooms.end(); it_pRooms++ )
//	//for ( std::vector< CRoom* >::iterator it_pRooms = ::g_vecpRoomsRegular.begin();
//	//	  it_pRooms != g_vecpRoomsRegular.end(); it_pRooms++ )
//	{
//		//DrawRoom( ::g_MasterRoom );	
//		CRoom* pCurrentRoom = *it_pRooms;
//		DrawRoom( *pCurrentRoom, pRoomObject, pDoorObject );
//		//DrawRoom( *(*it_pRooms) );
//	}
//}	
	//// ***********************



//// Draw camera target
//CGameObject* pCameraProxyObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName("CameraProxy");
//CGameObject* pCameraTarget = ::g_pGameObjectManager->FindGameObjectByFriendlyName("YellowDebugBall");
////if ( ::g_bDrawCameraTargetBall )
////{
//	pCameraTarget->pushRenderingState();
//
//	pCameraTarget->position = pCameraProxyObject->getTarget( glm::vec3( 0.0f, 0.0f, 3.0f ) );
//	DrawObject( pCameraTarget, glm::mat4(1.0f), glm::mat4(1.0f) );
//	if ( ::g_bDrawCameraTargetBall )
//	{
//		DrawDebugBallAtLocation( pCameraTarget->position );
//	}
//	glm::vec3 posAdjust = pCameraTarget->position;
////	posAdjust = glm::vec3(0.0f,0.0f,0.0f);
//	posAdjust.z += -5.0f;
//	posAdjust.x += -1.0f;
//	std::stringstream ss;
//	ss << posAdjust.x << ", " << posAdjust.y << ", " << posAdjust.z;
//	std::cout << ss.str() << std::endl;
//
//	CAABB AABB;
//
//	//angle += 0.1f;
//	//std::cout << "Angle Y: " << angle << std::endl;
//
//	DrawGLText( ss.str(), 
//				glm::vec3( posAdjust.x, posAdjust.y, posAdjust.z ), 
//				glm::quat(glm::vec3( 0.0f, glm::radians(angle), 0.0f )), 
//				CGLPrintf::CENTRE_ALIGNED, 
//				CGLColourHelper::getInstance()->getColourRGB( CGLColourHelper::COLOUR_YELLOW ),
//				AABB, 0.5f );
//
//	DrawDebugBallAtLocation( AABB.minXYZ, 0.1f );												// 0,0,0
//	DrawDebugBallAtLocation( glm::vec3( AABB.minXYZ.x, AABB.minXYZ.y, AABB.maxXYZ.z ), 0.1f );	// 0,0,1
//	DrawDebugBallAtLocation( glm::vec3( AABB.minXYZ.x, AABB.maxXYZ.y, AABB.minXYZ.z ), 0.1f );	// 0,1,0
//	DrawDebugBallAtLocation( glm::vec3( AABB.minXYZ.x, AABB.maxXYZ.y, AABB.maxXYZ.z ), 0.1f );	// 0,1,1
//	DrawDebugBallAtLocation( glm::vec3( AABB.maxXYZ.x, AABB.minXYZ.y, AABB.minXYZ.z ), 0.1f );	// 1,0,0
//	DrawDebugBallAtLocation( glm::vec3( AABB.maxXYZ.x, AABB.minXYZ.y, AABB.maxXYZ.z ), 0.1f );	// 1,0,1
//	DrawDebugBallAtLocation( glm::vec3( AABB.maxXYZ.x, AABB.maxXYZ.y, AABB.minXYZ.z ), 0.1f );	// 1,1,0
//	DrawDebugBallAtLocation( AABB.maxXYZ, 0.1f );												// 1,1,1
//
//	pCameraTarget->popRenderingState();
////}