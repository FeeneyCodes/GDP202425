#version 330
// (Pixel) Fragment fragment
in vec3 color;

uniform vec4 objectColour;
uniform bool bUseObjectColour;

out vec4 finalPixelColour;

void main()
{
	vec3 finalColour = color;
	if ( bUseObjectColour )
	{
		finalColour = objectColour.rgb;
	}
	
	finalPixelColour = vec4(finalColour, 1.0);
}
