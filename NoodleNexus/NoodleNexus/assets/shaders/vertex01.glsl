#version 330
// Vertex shader
in vec3 vCol;
in vec3 vPos;
in vec3 vNormal;	// Normal from the model ("model" space)
in vec2 vUV;		// Texture coordinates
in vec3 vTangent;
in vec3 vBiTangent;

// Changed 'f' (Fragment) to 'g' for Geometry shader
out vec3 gColour;
out vec4 gVertexWorldLocation;
out vec4 gVertexNormal;		// Normal in "world" space
out vec2 gUV;				// Texture coordinates (to the fragment shader)
out vec3 gTangent;
out vec3 gBiTangent;
out mat3 g_matTBN;		// TBN matrix for normal mapping

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
	
//	gl_Position = matModel * vec4(finalVert, 1.0);
//	gl_Position = matView * vec4(gl_Position);
//	gl_Position = matProjection * vec4(gl_Position);
	
	
	// Calculate location of the vertex in the "world"
	gVertexWorldLocation = matModel * vec4(finalVert, 1.0);
	
	// Calculatte the vertex normal
	// Don't want scaling or translation
	//fvertexNormal = matRoationOnly * vec4(vNormal, 1.0);
	mat4 matInvTransModel = inverse(transpose(matModel));	
	vec3 vNormNormalize = normalize(vNormal.xyz);
	gVertexNormal = matInvTransModel * vec4(vNormNormalize, 1.0);
	// Just in case
	gVertexNormal.xyz = normalize(gVertexNormal.xyz);
	
	mat3 matInvTransModel_3x3 = mat3(matInvTransModel);
	vec3 T = normalize(matInvTransModel_3x3 * gTangent);
	vec3 B = normalize(matInvTransModel_3x3 * gBiTangent);
	//vec3 N = normalize(matInvTransModel_3x3 * vNormNormalize);
	// We already have this, tho: gVertexNormal
	g_matTBN = mat3( T, B, gVertexNormal);
	
	gColour = vCol;
	gUV = vUV;			// Sent UVs to fragment shader
	
	gTangent = vTangent;
	gBiTangent = vBiTangent;
}
