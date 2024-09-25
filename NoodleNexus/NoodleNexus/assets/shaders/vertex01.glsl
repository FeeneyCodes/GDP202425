#version 330
// Vertex shader
in vec3 vCol;
in vec3 vPos;

out vec3 fColour;
out vec4 fvertexWorldLocation;

//uniform mat4 MVP;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matModel;

void main()
{
	vec3 finalVert = vPos;	
	
	// Screen space location of vertex
	mat4 matMVP = matProjection * matView * matModel;
	gl_Position = matMVP * vec4(finalVert, 1.0);
	
	// Calculate location of the vertex in the "world"
	fvertexWorldLocation = matModel * vec4(finalVert, 1.0);
	
	fColour = vCol;
}
