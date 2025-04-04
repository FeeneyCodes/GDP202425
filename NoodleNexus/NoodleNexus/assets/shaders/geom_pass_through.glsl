// Geometry (pass-through) shader
#version 420
layout(triangles) 			in;
layout(triangle_strip)		out;	// Have to be 'strips'
layout(max_vertices = 3)	out;

// From the vertex shader
// Note the [] because you are accepting more than one vertex
in vec3 gColour[];
in vec4 gVertexWorldLocation[];
in vec4 gVertexNormal[];		
in vec2 gUV[];	
in vec3 gTangent[];
in vec3 gBiTangent[];
in mat3 g_matTBN[];

// 'f' for 'going to the Fragment shader'
out vec3 fColour;			
out vec4 fvertexWorldLocation;
out vec4 fvertexNormal;
out vec2 fUV;	
out vec3 fTangent;
out vec3 fBiTangent;
out mat3 f_matTBN;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	fColour = gColour[0];	
	fvertexNormal = gVertexNormal[0];
	fvertexWorldLocation = gVertexWorldLocation[0];
	fUV = gUV[0];
	fTangent = gTangent[0];
	fBiTangent = gBiTangent[0];
	f_matTBN = g_matTBN[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	fColour = gColour[1];	
	fvertexNormal = gVertexNormal[1];
	fvertexWorldLocation = gVertexWorldLocation[1];
	fUV = gUV[1];
	fTangent = gTangent[1];
	fBiTangent = gBiTangent[1];
	f_matTBN = g_matTBN[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	fColour = gColour[2];	
	fvertexNormal = gVertexNormal[2];
	fvertexWorldLocation = gVertexWorldLocation[2];
	fUV = gUV[2];
	fTangent = gTangent[2];
	fBiTangent = gBiTangent[2];
	f_matTBN = g_matTBN[2];
	EmitVertex();

	EndPrimitive();
}