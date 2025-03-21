#include "global.h"
#include <iostream>		// Added


CRoom* g_pMasterRoom = NULL;


std::vector< CRoom* > g_vecpRoomsRegular;



// Camera stuff (SCREAMING to be a class)
float g_cameraEyeX = 0.0f;
float g_cameraEyeY = 0.0f;
float g_cameraEyeZ = 2.0f;

float g_cameraAtX = 0.0f;
float g_cameraAtY = 0.0f;
float g_cameraAtZ = 0.0f;


glm::mat4 matView(1.0f);		// "View" matrix set to identity
glm::mat4 matProjection(1.0f);	// Again with the identity. Gheesh.

IGLShaderManager* g_pTheShaderManager = NULL;
CModelTypeManager* g_pTheMeshManager = NULL;
CTextureManager* g_pTheTextureManager = NULL;
CMouseState*	g_pTheMouse = NULL;
CHRTimer* g_pIOTimer = NULL;

// Now global so that the physics can get at the ply information
CModelTypeManager*	g_pModelTypeManger = 0;
CGameObjectManager* g_pGameObjectManager = 0;

GLint g_UniformLocation_texture0 = 0;
GLint g_UniformLocation_texture1 = 0;
GLint g_UniformLocation_texture2 = 0;
GLint g_UniformLocation_texture3 = 0;
GLint g_UniformLocation_texture4 = 0;
GLint g_UniformLocation_texture5 = 0;

GLint g_UniformLocation_texture_HM_vert = 0;

GLint g_UniformLocation_skybox = 0;

GLint g_UniformLocation_ProjectionMatrix = 0;
GLint g_UniformLocation_ViewMatrix = 0;
GLint g_UniformLocation_ModelMatrix = 0;
GLint g_UniformLocation_ModelMatrixRotOnly = 0;

GLint g_UniformLocation_ambient = 0;	
GLint g_UniformLocation_diffuse = 0;		
GLint g_UniformLocation_spec = 0;		
GLint g_UniformLocation_shininess = 0;	

GLint g_UniformLocation_eye = 0;	

GLint g_UniformLocation_debugColour = 0;
GLint g_UniformLocation_bUseDebugColour = 0;

CLightDescription g_TheLights[NUMBEROFLIGHTS];
unsigned int g_selectedLightID = 0;

GLint g_UniformLocation_SelTex_0_ID = 0;
GLint g_UniformLocation_SelTex_1_ID = 0;

// Added for transparency
GLint g_UniformLocation_Alpha = 0;

GLint g_UniformLocation_bIsSkyBox = 0;	// bIsSkyMap


bool g_bGroundIsWireframe = false;
bool g_bGroundIsTextured = true;
// At 0.0f, is no tessellation (distance from camera)
// Less than this value, tessellation happens
float g_tessellationDistance = 0.01f;
// The amount of tessellation that happens
// 1.0f is no tessellation
float g_tessellationRatioOuter = 3.0f;
float g_tessellationRatioInner = 3.0f;
// 
bool g_bTessellateOnlyEdges = false;
float g_tessellationEdgeDotProductThreshold = 0.2f;

// How far the "hack" curvature thing is pushing the triangles out by
float g_tessNormProtrudeValue = 0.0f;


CGLPrintf* g_pGLPrintf = 0;

bool g_bDrawCameraTargetBall = true;
bool g_bDrawRooms = true;
bool g_bDrawRoomsAsWireframe = true;



//std::vector< CGameObject > g_vecTheObjects;
// These are now pointers since the "child" objects
//	are pointers, and it makes the DrawObject() call
//	more uniform.
//std::vector< CGameObject* > g_vec_pTheObjects;
//
//CGameObject* pTie = 0;


int CurrentWidth = 800;
int CurrentHeight = 600;
int WindowHandle = 0;


//const Matrix IDENTITY_MATRIX = { {
//  1, 0, 0, 0,
//  0, 1, 0, 0,
//  0, 0, 1, 0,
//  0, 0, 0, 1
//} };

float Cotangent(float angle)
{
  return (float)(1.0 / tan(angle));
}

float DegreesToRadians(float degrees)
{
  return degrees * (float)(PI / 180);
}

float RadiansToDegrees(float radians)
{
  return radians * (float)(180 / PI);
}



void ExitOnGLError(const char* error_message)
{
  const GLenum ErrorValue = glGetError();

  if (ErrorValue != GL_NO_ERROR)
  {
    //fprintf(stderr, "%s: %s\n", error_message, gluErrorString(ErrorValue));
	std::cout << gluErrorString(ErrorValue) << std::endl;
    exit(EXIT_FAILURE);
  }
}

//GLuint LoadShader(const char* filename, GLenum shader_type)
//{
//  GLuint shader_id = 0;
//  FILE* file;
//  long file_size = -1;
//  char* glsl_source;
//
//  if (NULL != (file = fopen(filename, "rb")) &&
//    0 == fseek(file, 0, SEEK_END) &&
//    -1 != (file_size = ftell(file)))
//  {
//    rewind(file);
//    
//    if (NULL != (glsl_source = (char*)malloc(file_size + 1)))
//    {
//      if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file))
//      {
//        glsl_source[file_size] = '\0';
//
//        if (0 != (shader_id = glCreateShader(shader_type)))
//        {
//          glShaderSource(shader_id, 1, &glsl_source, NULL);
//          glCompileShader(shader_id);
//          ExitOnGLError("Could not compile a shader");
//        }
//        else
//          fprintf(stderr, "ERROR: Could not create a shader.\n");
//      }
//      else
//        fprintf(stderr, "ERROR: Could not read file %s\n", filename);
//
//      free(glsl_source);
//    }
//    else
//      fprintf(stderr, "ERROR: Could not allocate %i bytes.\n", file_size);
//
//    fclose(file);
//  }
//  else
//  {
//    if (NULL != file)
//      fclose(file);
//    fprintf(stderr, "ERROR: Could not open file %s\n", filename);
//  }
//
//  return shader_id;
//}



//// Beyond here is the old math stuff that's been replaced by the glm (OpenGL Math) library
//Matrix MultiplyMatrices(const Matrix* m1, const Matrix* m2)
//{
//  Matrix out = IDENTITY_MATRIX;
//  unsigned int row, column, row_offset;
//
//  for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
//    for (column = 0; column < 4; ++column)
//      out.m[row_offset + column] =
//        (m1->m[row_offset + 0] * m2->m[column + 0]) +
//        (m1->m[row_offset + 1] * m2->m[column + 4]) +
//        (m1->m[row_offset + 2] * m2->m[column + 8]) +
//        (m1->m[row_offset + 3] * m2->m[column + 12]);
//
//  return out;
//}

//void ScaleMatrix(Matrix* m, float x, float y, float z)
//{
//  Matrix scale = IDENTITY_MATRIX;
//
//  scale.m[0] = x;
//  scale.m[5] = y;
//  scale.m[10] = z;
//
//  memcpy(m->m, MultiplyMatrices(m, &scale).m, sizeof(m->m));
//}

//void TranslateMatrix(Matrix* m, float x, float y, float z)
//{
//  Matrix translation = IDENTITY_MATRIX;
//  
//  translation.m[12] = x;
//  translation.m[13] = y;
//  translation.m[14] = z;
//
//  memcpy(m->m, MultiplyMatrices(m, &translation).m, sizeof(m->m));
//}

//void RotateAboutX(Matrix* m, float angle)
//{
//  Matrix rotation = IDENTITY_MATRIX;
//  float sine = (float)sin(angle);
//  float cosine = (float)cos(angle);
//  
//  rotation.m[5] = cosine;
//  rotation.m[6] = -sine;
//  rotation.m[9] = sine;
//  rotation.m[10] = cosine;
//
//  memcpy(m->m, MultiplyMatrices(m, &rotation).m, sizeof(m->m));
//}

//void RotateAboutY(Matrix* m, float angle)
//{
//  Matrix rotation = IDENTITY_MATRIX;
//  float sine = (float)sin(angle);
//  float cosine = (float)cos(angle);
//  
//  rotation.m[0] = cosine;
//  rotation.m[8] = sine;
//  rotation.m[2] = -sine;
//  rotation.m[10] = cosine;
//
//  memcpy(m->m, MultiplyMatrices(m, &rotation).m, sizeof(m->m));
//}

//void RotateAboutZ(Matrix* m, float angle)
//{
//  Matrix rotation = IDENTITY_MATRIX;
//  float sine = (float)sin(angle);
//  float cosine = (float)cos(angle);
//  
//  rotation.m[0] = cosine;
//  rotation.m[1] = -sine;
//  rotation.m[4] = sine;
//  rotation.m[5] = cosine;
//
//  memcpy(m->m, MultiplyMatrices(m, &rotation).m, sizeof(m->m));
//}

//Matrix CreateProjectionMatrix(
//  float fovy,
//  float aspect_ratio,
//  float near_plane,
//  float far_plane
//)
//{
//  Matrix out = { { 0 } };
//
//  const float
//    y_scale = Cotangent(DegreesToRadians(fovy / 2)),
//    x_scale = y_scale / aspect_ratio,
//    frustum_length = far_plane - near_plane;
//
//  out.m[0] = x_scale;
//  out.m[5] = y_scale;
//  out.m[10] = -((far_plane + near_plane) / frustum_length);
//  out.m[11] = -1;
//  out.m[14] = -((2 * near_plane * far_plane) / frustum_length);
//  
//  return out;
//}