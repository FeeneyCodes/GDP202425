#version 400 core

// This is the (optional) 2nd stage of the pipeline to run, 
// AFTER the vertex shader. 
//
// The tessellation process has three stages:
// 1. Tessellation Control (optional)  +++THIS ONE+++
// 2. Tessellation (fixed function, which you can't change or program)
// 3. Tessellation Evaluation 

// Taken from "Tessellation Shader Tutorial with Source Code C++"
// (which looks very much like the one from the SuperBible )
// We will also need to pass the other vertex attributes here

// TESSELLATION CONTROL SHADER
// (In DX11 speak, this is a "hull shader")

// This is called n times for each vertex in the incoming patch.
// We're using a triangle here, so this shader is called 3x, once 
// 	for each "vertex" in the "patch"

// While each tessellation control shader has access to the entire patch,
//	it is only able to write to ITS OWN invocation. That's why the output
//	values always have gl_InvocationID included as an index.
// (They can READ from any other index, but should have a barrier() function included)

layout(vertices = 3) out;

// Note that these are arrays
in vec4 ex_Normal[];
in vec4 ex_UV_x2[];

out vec4 TCout_Normal[];
out vec4 TCout_UV_x2[];


uniform float tessRatioOuter;
uniform float tessRatioInner;

// Position of eye (aka camera) in world space
uniform vec3 tessEyePos;	// Location of camera in world space
uniform float tessDistance;

// For testing for the "edge" of the model, not the triangle
uniform bool bTessOnlyEdges;
uniform float tessEdgeDotProdThresh;


void main(void)
{
// If the normal is facing right angles from the eye-vertex, then increase
// tessellation

	// ----------------------------------------------------------------
	// Calcuate the angle of the normal relative to the camera
	// ----------------------------------------------------------------
	// Average normal
	vec3 triNorm = ( ex_Normal[0].xyz + ex_Normal[1].xyz + ex_Normal[2].xyz ) / 3.0f;
	// Centre of triangle
	vec3 vertPosCentre = ( gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz ) / 3.0f;
	// Camera to triangle centre vector
	vec3 vecEyeVert = tessEyePos - vertPosCentre;
	// 
	const float DOT90DEGREES = dot(vec3(0.0f,1.0f,0.0f), vec3(1.0f,0.0f,0.0f));
	float dotEyeNorm = dot(vecEyeVert, triNorm);
	if ( abs(DOT90DEGREES - dotEyeNorm) < tessEdgeDotProdThresh ) 
	{	// The triangle is "on an edge"
	
	}
	
	gl_TessLevelOuter[0] = tessRatioOuter;		// 1.0;
	gl_TessLevelOuter[1] = tessRatioOuter;		// 1.0;
	gl_TessLevelOuter[2] = tessRatioOuter;		// 1.0;

	gl_TessLevelInner[0] = tessRatioInner;		// 3.0;


	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	
	TCout_Normal[gl_InvocationID] = ex_Normal[gl_InvocationID];
	TCout_UV_x2[gl_InvocationID] = ex_UV_x2[gl_InvocationID];
	
	return;
}
