#ifndef _ShaderVertexTypes_HG_
#define _ShaderVertexTypes_HG_

//typedef struct Vertex
//{
//  float Position[4];  // 0 is x, 1 is y, 2 is z
//  float Color[4];
//} Vertex;

typedef struct cFloat4
{
  float x, y, z, w;
} cFloat4;

typedef struct Vertex_p4n4
{
  //float Position[4];	//float x, y, z, w;
  //float Normal[4];		//float r,g,b,a
  cFloat4 Pos;
  cFloat4 Normal;
} Vertex_p4n4;

typedef struct Vertex_p4n4t4
{
	//float Position[4];		//float x, y, z, w;
	//float Normal[4];		//float r,g,b,a
	//float UV[4];		// st in OpenGL 
	cFloat4 Pos;  
	cFloat4 Normal;
	cFloat4 TextUVx2;
} Vertex_p4n4t4;


#endif ShaderVertexTypes