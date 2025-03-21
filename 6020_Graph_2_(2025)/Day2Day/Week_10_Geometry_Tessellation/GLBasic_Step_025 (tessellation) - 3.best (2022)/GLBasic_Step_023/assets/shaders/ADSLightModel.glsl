vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition )
{
	const vec3 myLightPosition = vec3( 1. , 0.5, 0. );
	const vec3 myLightAmbient = vec3( 0.2, 0.2, 0.2 );
	const vec3 myLightDiffuse = vec3( 1. , 1. , 1 . );
	const vec3 myLightSpecular = vec3( 1. , 1. , 1. );
	const vec3 myMaterialAmbient = vec3( 1. , 0.5, 0. );
	const vec3 myMaterialDiffuse = vec3( 1. , 0.5, 0. );
	const vec3 myMaterialSpecular = vec3( 0.6, 0.6, 0.6 );
	const float myMaterialShininess = 80.;
	// normal, light, view, and light reflection vectors
	vec3 norm = normalize( myNormal );
	vec3 lightv = normalize( myLightPosition - myPosition);
	vec3 viewv = normalize( vec3(0.,0.,0.) - myPosition );
	vec3 refl = reflect( vec3(0.,0.,0.) - lightv, norm );
	// ambient light computation
	vec3 ambient = myMaterialAmbient*myLightAmbient;
	// diffuse light computation
	vec3 diffuse = max(0.0, dot(lightv, norm)) * myMaterialDiffuse
	*myLightDiffuse;
	// Optionally you can add a diffuse attenuation term at this
	//point
	// specular light computation
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
		specular = pow(max(0.0, dot(viewv,refl)),
		myMaterialShininess)*myMaterialSpecular*
		myLightSpecular;
	}
	return clamp( ambient + diffuse + specular, 0.0, 1.0);
}