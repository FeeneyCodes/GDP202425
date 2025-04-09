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

uniform bool bUseNormalMap;

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
	mat3 matInvTransModel = inverse(transpose(mat3(matModel)));	
	
	gVertexNormal.xyz = normalize(matInvTransModel * vNormal.xyz);
	
	g_matTBN = mat3(1.0f);
	
	if ( bUseNormalMap )
	{
		//vec3 N = normalize(matInvTransModel * vNormal.xyz);
		vec3 T = normalize(matInvTransModel * vTangent);
		vec3 B = normalize(matInvTransModel * vBiTangent);
		//vec3 N = normalize(matInvTransModel_3x3 * vNormNormalize);
		// We already have this, tho: gVertexNormal
		g_matTBN = mat3( T, B, gVertexNormal.xyz);
	}
	
	gColour = vCol;
	gUV = vUV;			// Sent UVs to fragment shader
	
	gTangent = vTangent;
	gBiTangent = vBiTangent;
}
