#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Normal;	// Color is being used
layout(location=2) in vec4 in_UV_x2;	// x2 is because we're passing two sets of UV coordinates

// out means off to the next shader stage
out vec4 ex_Position;			
out vec4 ex_PositionWorld;			// Added
out vec4 ex_Normal;
out vec4 ex_UV_x2;

uniform mat4 ModelMatrix;	
uniform mat4 ModelMatrixRotOnly;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
  mat4 oneMatrixToRuleThemAll
	= ProjectionMatrix * ViewMatrix * ModelMatrix;
  gl_Position = oneMatrixToRuleThemAll * in_Position;
    
  // Sent 'pass through' variables to the fragment shader
  ex_Position = gl_Position;
  ex_PositionWorld = ModelMatrix * in_Position;
  ex_Normal = ModelMatrixRotOnly * normalize(in_Normal);
  ex_UV_x2 = in_UV_x2;

  return;
}


