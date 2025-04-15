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
// For shadows
out vec4 gFragPosLightSpace;

//uniform mat4 MVP;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matModel;

struct sLight
{
	vec4 position;			
	vec4 diffuse;	
	vec4 specular;	// rgb = highlight colour, w = power
	vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 direction;	// Spot, directional lights
	vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	                // 0 = pointlight
					// 1 = spot light
					// 2 = directional light
	vec4 param2;	// x = 0 for off, 1 for on
	                // y, z, and w : TBD
	vec4 shadowInfo;// x : shadow info: 0 = none (light doesn't cast shadow)
					//                  1 = 2D (perspective), 
					//                  2 = cubeMap (persepective)
					// y : shadow sampler ID (integer)
					// z : near plane
					// w : far plane
	mat4 lightSpaceShadowMatrix;
};

const int NUMBEROFLIGHTS = 10;
uniform sLight theLights[NUMBEROFLIGHTS]; 

uniform bool bUseNormalMap;
// If this is a "from the light" depth pass for the
//	shadow map, then we only save the gl_Position and then exit
uniform bool bIsShadowMapPass;	

void main()
{
	vec3 finalVert = vPos;	
	
	// Screen space location of vertex
	mat4 matMVP = matProjection * matView * matModel;
	gl_Position = matMVP * vec4(finalVert, 1.0);
	
	if ( bIsShadowMapPass )
	{
		// Early exit, just writing to the depth buffer
		return;
	}

	
//	gl_Position = matModel * vec4(finalVert, 1.0);
//	gl_Position = matView * vec4(gl_Position);
//	gl_Position = matProjection * vec4(gl_Position);
	
	
	// Calculate location of the vertex in the "world"
	gVertexWorldLocation = matModel * vec4(finalVert, 1.0);
	
	// Shadows
	gFragPosLightSpace = (theLights[1].lightSpaceShadowMatrix * matModel) * vec4(finalVert, 1.0);
	
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
