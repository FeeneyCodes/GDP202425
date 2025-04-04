#include "cVAOManager.h"
#include "../GLCommon.h"	// All the GLFW, etc. (OpenGL stuff)

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

bool cVAOManager::CloneMeshToDynamicVAO(
	std::string newMeshName,
	sModelDrawInfo& drawInfo,
	unsigned int shaderProgramID)
{
	// This is MOSTLY the same as the origial "Load VAO" method

	sModelDrawInfo cloneMeshDrawInfo;
	// Copy all the info
	cloneMeshDrawInfo = drawInfo;
	// Update the cloned stuff
	cloneMeshDrawInfo.meshName = newMeshName;

//	cloneMeshDrawInfo.pVertices = new sVertex_SHADER_FORMAT_xyz_rgb_N_UV[drawInfo.numberOfVertices];
	cloneMeshDrawInfo.pVertices = new sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi[drawInfo.numberOfVertices];
	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{
		cloneMeshDrawInfo.pVertices[index] = drawInfo.pVertices[index];
	}

	cloneMeshDrawInfo.pIndices = new unsigned int[drawInfo.numberOfIndices];
	for (unsigned int index = 0; index != drawInfo.numberOfIndices; index++)
	{
		cloneMeshDrawInfo.pIndices[index] = drawInfo.pIndices[index];
	}


	// Copy the CLONED mesh to the VAO
	glGenVertexArrays(1, &(cloneMeshDrawInfo.VAO_ID));
	glBindVertexArray(cloneMeshDrawInfo.VAO_ID);

	glGenBuffers(1, &(cloneMeshDrawInfo.VertexBufferID));

	glBindBuffer(GL_ARRAY_BUFFER, cloneMeshDrawInfo.VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER,
//		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV) * cloneMeshDrawInfo.numberOfVertices,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi) * cloneMeshDrawInfo.numberOfVertices,
		(GLvoid*)cloneMeshDrawInfo.pVertices,
// ************************************************
		GL_DYNAMIC_DRAW);			// <-- KEY CHANGE (GL_STATIC_DRAW)
// ************************************************

	glGenBuffers(1, &(cloneMeshDrawInfo.IndexBufferID));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cloneMeshDrawInfo.IndexBufferID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,			// Type: Index element array
		sizeof(unsigned int) * cloneMeshDrawInfo.numberOfIndices,
		(GLvoid*)cloneMeshDrawInfo.pIndices,
		GL_STATIC_DRAW);

	GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPos");			// in vec3 vPos;
	GLint vcol_location = glGetAttribLocation(shaderProgramID, "vCol");			// in vec3 vCol;
	GLint vnorm_location = glGetAttribLocation(shaderProgramID, "vNormal");		// in vec3 vNormal;
	GLint vUV_location = glGetAttribLocation(shaderProgramID, "vUV");			// in vec2 vUV;
	GLint vTangent_location = glGetAttribLocation(shaderProgramID, "vTangent");		// in vec3 vTangent;
	GLint vBiTangent_location = glGetAttribLocation(shaderProgramID, "vBiTangent");	// in vec3 vBiTangent;


	// Set the vertex attributes for this shader
	glEnableVertexAttribArray(vpos_location);	
	glVertexAttribPointer(vpos_location,	// vPos
		3,		
		GL_FLOAT, GL_FALSE,
//		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV),	
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, x));

	glEnableVertexAttribArray(vcol_location);	// vCol
	glVertexAttribPointer(vcol_location,
		3,		// vCol
		GL_FLOAT, GL_FALSE,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, r));

	glEnableVertexAttribArray(vnorm_location);	// vNormal
	glVertexAttribPointer(vnorm_location,
		3,		
		GL_FLOAT, GL_FALSE,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, nx));

	glEnableVertexAttribArray(vUV_location);	// vUV
	glVertexAttribPointer(vUV_location,
		2,		// in vec2 vUV;
		GL_FLOAT, GL_FALSE,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, u));

	glEnableVertexAttribArray(vTangent_location);	// vTangent
	glVertexAttribPointer(vTangent_location,
		3,		// in vec3 vTangent;
		GL_FLOAT, GL_FALSE,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, tx));

	glEnableVertexAttribArray(vBiTangent_location);	// vBiTangent
	glVertexAttribPointer(vBiTangent_location,
		3,		// in vec3 vBiTangent;
		GL_FLOAT, GL_FALSE,
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi),
		(void*)offsetof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi, bx));


	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vpos_location);
	glDisableVertexAttribArray(vcol_location);
	glDisableVertexAttribArray(vnorm_location);
	glDisableVertexAttribArray(vUV_location);
	glDisableVertexAttribArray(vTangent_location);
	glDisableVertexAttribArray(vBiTangent_location);


	// Store the draw information into the map
	this->m_LockModelMap();
	this->m_map_ModelName_to_VAOID[cloneMeshDrawInfo.meshName] = cloneMeshDrawInfo;
	this->m_UnlockModelMap();

	return true;
}


bool cVAOManager::UpdateDynamicMesh(
	std::string friendlyName,
	// Will only look at the vertex info!
	sModelDrawInfo& updatedDrawInfo,
	unsigned int shaderProgramID)
{
	// We are UPDATING the information on an EXISTING buffer, not creating a new one
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferSubData.xhtml

	glBindBuffer(GL_ARRAY_BUFFER, updatedDrawInfo.VertexBufferID);

// ************************************************
// 
// 	   We ALLOCATED the buffer with this call:
// 
// 	   But we AREN'T doing that here. 
// 	   NOTE-DANGER: You CAN do this, but it will allocate a NEW buffer
// 	                EVERY FRAME. So it'll "work", but you'll run out of memory on the GPU
// 
//	glBufferData(GL_ARRAY_BUFFER,
//		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV) * updatedDrawInfo.numberOfVertices,
//		(GLvoid*)updatedDrawInfo.pVertices,
//		// ************************************************
//		GL_DYNAMIC_DRAW);			// <-- KEY CHANGE
// ************************************************
	
	// This will copy whatever is currently in the pVertices array
	//	back to the vertex buffer on the GPU
	// (overwriting whatever is there)


	glBufferSubData(GL_ARRAY_BUFFER,		// GLenum target --> vertex buffer
		0,									// GLintptr offset
		// GLsizeiptr size: number of BYTES
//		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV) * updatedDrawInfo.numberOfVertices,	
		sizeof(sVertex_SHADER_FORMAT_xyz_rgb_N_UV_TanBi) * updatedDrawInfo.numberOfVertices,
		(GLvoid*)updatedDrawInfo.pVertices);			// const void* data);

	return true;
}