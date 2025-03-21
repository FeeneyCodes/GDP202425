#version 400

//in vec4 ex_Color;
in vec4 ex_Position;		// Coming from vertex
in vec4 ex_PositionWorld;
in vec4 ex_Normal;			// Coming from vertex
in vec4 ex_UV_x2;

out vec4 out_Color;

uniform vec4 sexyVariable;

struct LightDesc
{
	vec3 Position;
	float constAttent;
	// float linearAtten;
	// vec3 diffuse	..and so on...
};

const int NUMLIGHTS = 3;
uniform LightDesc myLights[NUMLIGHTS];
//uniform vec3 myLightPosition;	//  = vec3( 1.0f , 0.5f, 0.0f );

uniform vec3 myMaterialAmbient;		// = vec3( 0.2f , 0.1f, 0.0f );
uniform vec3 myMaterialDiffuse;		// = vec3( 1.0f , 0.5f, 0.0f );
uniform vec3 myMaterialSpecular;	// = vec3( 0.6f, 0.6f, 0.6f );
uniform float myMaterialShininess;	// = 80.0f; 

uniform vec3 eye;	// Eye location of the camera

vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition, 
                    in int LightIndex );

void main(void)
{
	//out_Color = ex_Color;
	// out vec4 out_Color;
	out_Color = sexyVariable;

	// ex_Normal came from the vertex shader.
	//	it's the Normal at this particular pixel fragment
	vec3 myNormal = vec3( ex_Normal.x, 
						  ex_Normal.y, 
						  ex_Normal.z );
						
	vec3 myPositionWorld = vec3( ex_PositionWorld.xyz );
	
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	for ( int LightIndex = 0; LightIndex < NUMLIGHTS; LightIndex++ )
	{
		color += ADSLightModel( myNormal, myPositionWorld,
                                LightIndex ); 
	}
	
	// Limit the colour range from 0.0 to 1.0
    color = clamp( color, 0.0f, 1.0f );
	
	out_Color = vec4( color, 1.0f );

	// Brighten it up for the dark projector
	out_Color *= 1.2f;
	
	//out_Color.x = 0.0f;
	//out_Color.y = 1.0f;
	//out_Color.z = 0.0f;
	return;
}


vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition, 
                    in int LightIndex )
{
//	const vec3 myLightPosition = vec3( 1.0f , 0.5f, 0.0f );
	const vec3 myLightAmbient = vec3( 0.2f, 0.2f, 0.2f );
	const vec3 myLightDiffuse = vec3( 1.0f , 1.0f , 1.0f );
	const vec3 myLightSpecular = vec3( 1.0f , 1.0f , 1.0f );
	
//	const vec3 myMaterialAmbient = vec3( 0.2f , 0.1f, 0.0f );
//	const vec3 myMaterialDiffuse = vec3( 1.0f , 0.5f, 0.0f );
//	const vec3 myMaterialSpecular = vec3( 0.6f, 0.6f, 0.6f );
//	const float myMaterialShininess = 80.0f;  

	
	// normal, light, view, and light reflection vectors
	vec3 norm = normalize( myNormal );
	//vec3 lightv = normalize( myLightPosition - myPosition);
	vec3 lightv = normalize( myLights[LightIndex].Position - myPosition);
	
	//const vec3 eye = vec3( 0.0f, 0.0f, 0.0f );	
	//vec3 viewv = normalize( vec3(0.0f,0.0f,0.0f) - myPosition );
	//vec3 refl = reflect( vec3(0.0f,0.0f,0.0f) - lightv, norm );


	vec3 viewv = normalize( eye - myPosition );
	//vec3 refl = reflect( eye - lightv, norm );
	vec3 refl = -( reflect( lightv, norm ) );

	
	// ambient light computation
	vec3 ambient = myMaterialAmbient*myLightAmbient;
	
	// diffuse light computation

	vec3 diffuse = max(0.0f, dot(lightv, norm))
                   * myMaterialDiffuse
				   * myLightDiffuse;
				   
	// Optionally you can add a diffuse attenuation term at this point
	//float dist = distance( myPosition, myLightPosition );	
	float dist = distance( myPosition, myLights[LightIndex].Position );	
	float myLightAttenConst = 0.1f;
	float myLightAttenLinear = 0.1f;
	float myLightAttenQuad = 0.1f;
	float atten = 1.0f /( myLightAttenConst + 
	                      myLightAttenLinear * dist +
						  myLightAttenQuad * dist * dist );
	
	diffuse *= atten;
	
	// specular light computation
	vec3 specular = vec3( 0.0f, 0.0f, 0.0f );	

	//if( dot(lightv, viewv) > 0.0f )
	if( dot(lightv, norm) > 0.0f )
	{
		specular = pow( max(0.0f, dot(viewv,refl)), myMaterialShininess)
					* myMaterialSpecular
					* myLightSpecular;
		specular *= atten;
	}

	return clamp( ambient + diffuse + specular, 0.0f, 1.0f );
}






