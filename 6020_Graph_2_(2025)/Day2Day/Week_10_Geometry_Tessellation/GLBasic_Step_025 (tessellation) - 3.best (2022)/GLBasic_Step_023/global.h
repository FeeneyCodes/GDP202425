#ifndef _global_HG_
#define _global_HG_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define GLEW_STATIC
#define FREEGLUT_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
// 
#include <vector>
#include "CGameObject.h"
#include "CShaderManager/IGLShaderManager.h"
#include "ShaderVertexTypes.h"
#include "CModelTypeManager.h"
#include "GLTexture/CTextureManager.h"
#include "CGameObjectManager.h"
#include "CLightDescription.h"
#include "Mouse/CMouseState.h"
#include "CHRTimer.h"
#include "CError/CErrorLog.h"
#include "CError/COpenGLError.h"
#include "CGLPrintf.h"


#include "CRoom.h"

extern std::vector< CRoom* > g_vecpRoomsRegular;
extern CRoom* g_pMasterRoom;


// This isn't extern since it's static (i.e. there's only one)
static CErrorLog g_ErrorLog;

extern IGLShaderManager* g_pTheShaderManager;

extern CModelTypeManager* g_pTheMeshManager;

extern CTextureManager* g_pTheTextureManager;

// Now global so that the physics can get at the ply information
extern CModelTypeManager* g_pModelTypeManger;
extern CGameObjectManager* g_pGameObjectManager;

extern CMouseState*	g_pTheMouse;

extern GLint g_UniformLocation_texture0;
extern GLint g_UniformLocation_texture1;
extern GLint g_UniformLocation_texture2;
extern GLint g_UniformLocation_texture3;
extern GLint g_UniformLocation_texture4;
extern GLint g_UniformLocation_texture5;

extern GLint g_UniformLocation_texture_HM_vert;

extern GLint g_UniformLocation_skybox;

extern CGLPrintf* g_pGLPrintf;

extern CHRTimer* g_pIOTimer;

static const double PI = 3.14159265358979323846;


extern int CurrentWidth;// = 800;
extern int CurrentHeight;// = 600;
extern int WindowHandle;// = 0;


float pickRandZeroToOne(void);


// GLUT keyboard callback function signatures:
void glutKeyboard_callback(unsigned char key, int x, int y);
void glutSpecialKey_callback( int key, int x, int y );

void glutMenuHandler_callback(int value);

// allocation
// Initilization
extern float g_cameraEyeX; //  = 0;
extern float g_cameraEyeY;
extern float g_cameraEyeZ;

extern float g_cameraAtX;
extern float g_cameraAtY;
extern float g_cameraAtZ;

extern glm::mat4 matView;		//(1.0f);		// "View" matrix set to identity
extern glm::mat4 matProjection; //(1.0f);	// Again with the identity. Gheesh.

extern IGLShaderManager* g_pTheShaderManager;// = 0;

extern GLint g_UniformLocation_ProjectionMatrix;	// = 0;
extern GLint g_UniformLocation_ViewMatrix;		// = 0;
extern GLint g_UniformLocation_ModelMatrix;		// = 0;
extern GLint g_UniformLocation_ModelMatrixRotOnly;	// = 0;
// 
extern GLint g_UniformLocation_ambient;	
extern GLint g_UniformLocation_diffuse;		
extern GLint g_UniformLocation_spec;		
extern GLint g_UniformLocation_shininess;		

extern GLint g_UniformLocation_eye;		// Position of camera "eye" passed to shader

extern GLint g_UniformLocation_debugColour;
extern GLint g_UniformLocation_bUseDebugColour;


extern GLint g_UniformLocation_SelTex_0_ID;
extern GLint g_UniformLocation_SelTex_1_ID;

extern GLint g_UniformLocation_Alpha;
extern GLint g_UniformLocation_bIsSkyBox;	// bIsSkyMap

extern bool g_bGroundIsWireframe;
extern bool g_bGroundIsTextured;
extern float g_tessellationDistance;
extern float g_tessellationRatioOuter;
extern float g_tessellationRatioInner;
extern bool g_bTessellateOnlyEdges;
extern float g_tessellationEdgeDotProductThreshold;

// How far the "hack" curvature thing is pushing the triangles out by
extern float g_tessNormProtrudeValue;


static const unsigned int NUMBEROFLIGHTS = 10;
extern CLightDescription g_TheLights[NUMBEROFLIGHTS];

// This is the id of the light we are selecting in the keyboard callback
extern unsigned int g_selectedLightID;
//

//void CreateAllTheObjectsYo(void);
void CreateAllTheObjectsYo_2(void);		// New one that uses the builder


// These functions were moved into individual files (they were getting REALLY big)
// These are used to init everything
bool InitWindow(int, char*[]);
bool Initialize(int, char*[]);

void DrawScene( void );


// The freeGLUT "callback" function definitions.
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void ShutErDown(void);			// Was DestroyCube()


extern bool g_bDrawCameraTargetBall;
extern bool g_bDrawRooms;
extern bool g_bDrawRoomsAsWireframe;

#define WINDOW_TITLE_PREFIX "Chapter 4"



#endif
