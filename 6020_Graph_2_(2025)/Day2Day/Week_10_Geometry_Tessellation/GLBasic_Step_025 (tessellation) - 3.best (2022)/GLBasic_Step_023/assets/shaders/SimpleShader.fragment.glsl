#version 400

in vec4 ex_Color;
out vec4 out_Color;

uniform vec4 sexyVariable;

void main(void)
{
  //out_Color = ex_Color;
  
  out_Color = sexyVariable;
  
  //out_Color.x = 0.0f;
  //out_Color.y = 1.0f;
  //out_Color.z = 0.0f;
}