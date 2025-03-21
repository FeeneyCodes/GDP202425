#version 400 core

// Taken from "Tessellation Shader Tutorial with Source Code C++"
// (which looks very much like the one from the SuperBible )

// This is the (optional) 2nd stage of the pipeline to run, 
// AFTER the vertex shader. 
//
// The tessellation process has three stages:
// 1. Tessellation Control (optional)  
// 2. Tessellation (fixed function, which you can't change or program)
// 3. Tessellation Evaluation    +++THIS ONE+++

// TESSELLATION EVAULATION SHADER

// (In DX11 speak, this is the "domain shader")

layout(triangles, equal_spacing, ccw) in;

in vec4 TCout_Normal[];
in vec4 TCout_UV_x2[];
//in float TCout_DebugColour[];
in vec4 TCout_PositionWorld[];
in vec4 TCout_ex_Shad_Coord[];

out vec4 ex_Normal;
out vec4 ex_UV_x2;
out vec4 ex_Shad_Coord;
//out float TCout_ex_DebugColour;

uniform float hackNormalProdrudeAdjustRatio;// = 0.01f;


void main()
{	
	// gl_TessCoord is the coordinate of the vertex within the current patch

	// Push out the location based on the normal
	gl_Position.xyzw =	gl_in[0].gl_Position.xyzw * gl_TessCoord.x +
						gl_in[1].gl_Position.xyzw * gl_TessCoord.y +
						gl_in[2].gl_Position.xyzw * gl_TessCoord.z;
	vec4 posWorld =	TCout_PositionWorld[0].xyzw * gl_TessCoord.x +
					TCout_PositionWorld[0].xyzw * gl_TessCoord.y +
					TCout_PositionWorld[0].xyzw * gl_TessCoord.z;
										
	// You can't use a loop for this as the indices must be constant
	ex_Normal.xyzw = TCout_Normal[0].xyzw * gl_TessCoord.x +
				     TCout_Normal[1].xyzw * gl_TessCoord.y +
				     TCout_Normal[2].xyzw * gl_TessCoord.z;
					 
	// Hack-o-rama: Based on how close to the centre of the triangle we are
	// "push out" the position along the normal
	const vec3 vecBaryCentreOfTheTriangle = vec3(1.0f/3.0f, 1.0f/3.0f, 1.0f/3.0f);	// Get it?? Math joke!!!
	// Will return a value of 0.0 to something less then 1.0
	float distToCentre = distance(posWorld.xyz, vecBaryCentreOfTheTriangle);
	// Make some sexy ratio
//	const float hackNormalProdrudeAdjustRatio = 0.01f;
	const float maxDistanceFromCentre = 2.0f/3.0f;
	float normAdjust = ( maxDistanceFromCentre - distToCentre ) * hackNormalProdrudeAdjustRatio;
	gl_Position.xyz += ( ex_Normal.xyz * normAdjust );
	
	
//	ex_Normal.xyzw = (TCout_Normal[0].xyzw + TCout_Normal[1].xyzw + TCout_Normal[2].xyzw)/3.0f;
	
	//ex_Normal.xyz += vec3( 1.0f, 0.0f, 0.0f );	// HACK
	ex_Normal.w = 1.0f;
	
	// We have to, independent, sets of texture coordinates, one stored
	// 	in xy and the other stored in wz. In our examples, they are being passed
	//	the same values, but we need to be careful to keep them separated.
	// So we can't have ex_UV_x2.xywz... 
	
	ex_UV_x2.xy = TCout_UV_x2[0].xy * gl_TessCoord.x +
				  TCout_UV_x2[1].xy * gl_TessCoord.y +
				  TCout_UV_x2[2].xy * gl_TessCoord.z; 
	ex_UV_x2.zw = TCout_UV_x2[0].zw * gl_TessCoord.x +
				  TCout_UV_x2[1].zw * gl_TessCoord.y +
				  TCout_UV_x2[2].zw * gl_TessCoord.z; 
				  
//	TCout_ex_DebugColour = TCout_DebugColour[0] * gl_TessCoord.x +
//						   TCout_DebugColour[1] * gl_TessCoord.y +
//						   TCout_DebugColour[2] * gl_TessCoord.z; 

	ex_Shad_Coord.xyzw = TCout_ex_Shad_Coord[0].xyzw * gl_TessCoord.x +
						 TCout_ex_Shad_Coord[1].xyzw * gl_TessCoord.y +
						 TCout_ex_Shad_Coord[2].xyzw * gl_TessCoord.z;


	return;
}

//0(44) : error C1031: swizzle mask element not present in operand "xy"
//0(45) : error C7505: OpenGL does not allow swizzles on scalar expressions
//0(45) : error C1031: swizzle mask element not present in operand "zw"
