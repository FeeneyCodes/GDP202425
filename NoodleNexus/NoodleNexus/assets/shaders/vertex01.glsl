#version 330
// Vertex shader
in vec3 vCol;
in vec3 vPos;
in vec3 vNormal;	// Normal from the model ("model" space)
in vec2 vUV;		// Texture coordinates

// Changed 'f' (Fragment) to 'g' for Geometry shader
out vec3 gColour;
out vec4 gVertexWorldLocation;
out vec4 gVertexNormal;		// Normal in "world" space
out vec2 gUV;				// Texture coordinates (to the fragment shader)

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
	gVertexWorldLocation = matModel * vec4(finalVert, 1.0);
	
	// Calculatte the vertex normal
	// Don't wank scaling or translation
	//fvertexNormal = matRoationOnly * vec4(vNormal, 1.0);
	mat4 matInvTransModel = inverse(transpose(matModel));
	// Just in case
	
	vec3 vNormNormalize = normalize(vNormal.xyz);
	gVertexNormal = matInvTransModel * vec4(vNormNormalize, 1.0);
	// Just in case
	gVertexNormal.xyz = normalize(gVertexNormal.xyz);
	
	gColour = vCol;
	gUV = vUV;			// Sent UVs to fragment shader
}
