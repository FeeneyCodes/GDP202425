#version 400

//in vec4 ex_Color;
in vec4 ex_Position;		// Coming from vertex
in vec4 ex_PositionWorld;
in vec4 ex_Normal;			// NOW coming from the tessellation shader
in vec4 ex_UV_x2;

//in float TCout_ex_DebugColour;

out vec4 out_Colour;

struct LightDesc
{
	vec3 position;
	vec3 ambient;	
	vec3 diffuse;
	vec3 specular;
	float attenConst;	// = 0.1f;
	float attenLinear;	// = 0.1f;
	float attenQuad;	// = 0.1f;
};

const int NUMLIGHTS = 10;
uniform LightDesc myLights[NUMLIGHTS];

//uniform vec3 myLightPosition;	//  = vec3( 1.0f , 0.5f, 0.0f );

uniform vec3 myMaterialAmbient;		// = vec3( 0.2f , 0.1f, 0.0f );
uniform vec3 myMaterialDiffuse;		// = vec3( 1.0f , 0.5f, 0.0f );
uniform vec3 myMaterialSpecular;	// = vec3( 0.6f, 0.6f, 0.6f );
uniform float alphaValue;		// 0.0f to 1.0f
uniform float myMaterialShininess;	// = 80.0f; 

uniform vec3 eye;	// Eye location of the camera

uniform vec4 debugColour;	
uniform bool bUseDebugColour;	// Note: the "bool" type is relatively new to shaders. 
                                // You could also use a float or int (0.0 being false, anything else being true, for instance)

// Three 2D texture variables
uniform sampler2D texture_0;		// Brick  
uniform sampler2D texture_1;		// Emma
uniform sampler2D texture_2;		// Mud
uniform sampler2D texture_3;		// Height Map
uniform sampler2D texture_4;		// Emma
uniform sampler2D texture_5;		// Mud

uniform samplerCube skyMapTexture;
uniform bool bIsSkyMap;

uniform int SelTex_0_ID;
uniform int SelTex_1_ID;

vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition, 
                    in int LightIndex );

void main(void)
{
	out_Colour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//out_Colour = vec4(0.0f, 0.0f, 0.0f, alphaValue);
	
	
	if ( bIsSkyMap )	// SKYMAP STUFF
	{
		// Sky map is ONLY contribution from the cubemap texture
		out_Colour = texture( skyMapTexture, ex_Normal.xyz );
		
		// Code to make the skybox visible on the projector (it's dark)
//		float brighten = 1.0f;
//		float gammaAdjust = 0.2f;
//		out_Colour += vec4( gammaAdjust, gammaAdjust, gammaAdjust, 0.0f );
//		out_Colour *= vec4( brighten, brighten, brighten, 1.0f );		

		// no transparency
		out_Colour.a = 1.0f;
		return;
	}
	
	// "Sample" the texture colour from the texture.
	// Note that here we are using the same texture coordinates, but 
	// 	you could use different ones, if needed
	// (My point is that the texture coordinates DON'T have to be 
	//	the same for all textures. It just happens to be the case here.)
	vec4 texture0Colour = texture( texture_0, ex_UV_x2.xy );
	vec4 texture1Colour = texture( texture_1, ex_UV_x2.xy );
	vec4 texture2Colour = texture( texture_2, ex_UV_x2.xy );
	vec4 texture3Colour = texture( texture_3, ex_UV_x2.xy );
	vec4 texture4Colour = texture( texture_4, ex_UV_x2.xy );
	vec4 texture5Colour = texture( texture_5, ex_UV_x2.xy );

	// ex_Normal came from the vertex shader.
	//	it's the Normal at this particular pixel fragment
	vec3 myNormal = vec3( ex_Normal.x, 
						  ex_Normal.y, 
						  ex_Normal.z );
						
	vec3 myPositionWorld = vec3( ex_PositionWorld.xyz );
	
	// Are we using the "debug" colour (i.e. no lighthing)
//	if ( bUseDebugColour )
//	{	// Yes, so skip lighting and texturing
//		out_Colour = debugColour;
//		// Exit early (it's faster)
//		return;
//	}

	vec3 colour = vec3(0.0f, 0.0f, 0.0f);
	// Could optionally add the texture samples as the "colour" 
	// 	of the vertex at this position
	for ( int LightIndex = 0; LightIndex < NUMLIGHTS; LightIndex++ )
	{
		colour += ADSLightModel( myNormal, myPositionWorld,
                                LightIndex ); 
	}
	
	// Limit the colour range from 0.0 to 1.0
    colour = clamp( colour, 0.0f, 1.0f );
	
	// Lighting + materials only
	//out_Colour = vec4( colour, 1.0f );
	
	// Another way to apply the textures, AFTER the lighthing is done
	// Lighting + materials + texture
	
	// Assume the texture is WHITE to start
	vec4 texContrib_0 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 texContrib_1 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	switch (SelTex_0_ID)
	{
	case 0:	texContrib_0 = texture0Colour;	break;
	case 1:	texContrib_0 = texture1Colour;	break;
	case 2:	texContrib_0 = texture2Colour;	break;
	case 3:	texContrib_0 = texture3Colour;	break;
	case 4:	texContrib_0 = texture4Colour;	break;
	case 5:	texContrib_0 = texture5Colour;	break;
	// ... and so on
	default:
		texContrib_0 = vec4(1.0f,1.0f,1.0f,1.0f);	// Should 'never' happen
	};

	switch (SelTex_1_ID)
	{
	case 0:	texContrib_1 = texture0Colour;	break;
	case 1:	texContrib_1 = texture1Colour;	break;
	case 2:	texContrib_1 = texture2Colour;	break;
	case 3:	texContrib_1 = texture3Colour;	break;
	case 4:	texContrib_1 = texture4Colour;	break;
	case 5:	texContrib_1 = texture5Colour;	break;
	// ... and so on
	default:
		texContrib_1 = vec4(1.0f,1.0f,1.0f,1.0f);	// Should 'never' happen
	};
	
	// Combine lighting with texture contribution
	out_Colour = vec4(colour, 1.0f) * texContrib_0 * texContrib_1;
	
	// Add the transparency contribution  xyzw   rgba
	out_Colour.w = alphaValue;		// "w" is the 4th number in the vec4
	
	
//	out_Colour.xyz *= 0.01f;
//	out_Colour.xyz += vec3(TCout_ex_DebugColour,TCout_ex_DebugColour,TCout_ex_DebugColour);
	return;
}


vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition, 
                    in int LightIndex )
{
//	const vec3 myLightPosition = vec3( 1.0f , 0.5f, 0.0f );
//	const vec3 myLightAmbient = vec3( 0.2f, 0.2f, 0.2f );
//	const vec3 myLightDiffuse = vec3( 1.0f , 1.0f , 1.0f );
//	const vec3 myLightSpecular = vec3( 1.0f , 1.0f , 1.0f );
	
//	const vec3 myMaterialAmbient = vec3( 0.2f , 0.1f, 0.0f );
//	const vec3 myMaterialDiffuse = vec3( 1.0f , 0.5f, 0.0f );
//	const vec3 myMaterialSpecular = vec3( 0.6f, 0.6f, 0.6f );
//	const float myMaterialShininess = 80.0f;  

	
	// normal, light, view, and light reflection vectors
	vec3 norm = normalize( myNormal );
	//vec3 lightv = normalize( myLightPosition - myPosition);
	vec3 lightv = normalize( myLights[LightIndex].position - myPosition);
	
	//const vec3 eye = vec3( 0.0f, 0.0f, 0.0f );	
	//vec3 viewv = normalize( vec3(0.0f,0.0f,0.0f) - myPosition );
	//vec3 refl = reflect( vec3(0.0f,0.0f,0.0f) - lightv, norm );


	vec3 viewv = normalize( eye - myPosition );
	//vec3 refl = reflect( eye - lightv, norm );
	vec3 refl = -( reflect( lightv, norm ) );

	
	// ambient light computation
	//vec3 ambient = myMaterialAmbient * myLightAmbient;
	vec3 ambient = myMaterialAmbient * myLights[LightIndex].ambient;
	
	// diffuse light computation

	vec3 diffuse = max(0.0f, dot(lightv, norm))
                   * myMaterialDiffuse
				   * myLights[LightIndex].diffuse;// myLightDiffuse;
				   
	// Optionally you can add a diffuse attenuation term at this point
	//float dist = distance( myPosition, myLightPosition );	
	float dist = distance( myPosition, myLights[LightIndex].position );	
//	float myLightAttenConst = 0.1f;
//	float myLightAttenLinear = 0.1f;
//	float myLightAttenQuad = 0.1f;
//	float atten = 1.0f /( myLightAttenConst + 
//	                      myLightAttenLinear * dist +
//						  myLightAttenQuad * dist * dist );
	float atten = 1.0f /( myLights[LightIndex].attenConst + 
	                      myLights[LightIndex].attenLinear * dist +
						  myLights[LightIndex].attenQuad * dist * dist );
	
	diffuse *= atten;
	
	// specular light computation
	vec3 specular = vec3( 0.0f, 0.0f, 0.0f );	

	//if( dot(lightv, viewv) > 0.0f )
	if( dot(lightv, norm) > 0.0f )
	{
		specular = pow( max(0.0f, dot(viewv,refl)), myMaterialShininess)
					* myMaterialSpecular
					* myLights[LightIndex].specular;// // myLightSpecular;
		specular *= atten;
	}
	
	//specular = vec3( 1.0f, 1.0f, 1.0f );

	return clamp( ambient + diffuse + specular, 0.0f, 1.0f );
}






