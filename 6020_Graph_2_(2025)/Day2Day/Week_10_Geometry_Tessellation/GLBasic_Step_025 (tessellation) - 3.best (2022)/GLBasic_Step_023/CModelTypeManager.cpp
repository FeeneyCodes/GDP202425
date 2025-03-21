#include "CModelTypeManager.h"
#include <sstream>
#include <string>

#include "ShaderVertexTypes.h"

// This is really for the GLunit that we are using the the index buffer
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "CError/COpenGLError.h"

CModelTypeManager::CModelTypeManager()
{

	return;
}

CModelTypeManager::~CModelTypeManager()
{

	return;
}

void CModelTypeManager::SetBaseFilePath( std::string baseFilePath )
{
	this->m_baseFilePath = baseFilePath;
	return;
}

std::string CModelTypeManager::GetBaseFilePath(void)
{
	return this->m_baseFilePath;
}

//static const 
const std::string CModelTypeManager::STRINGNOERROR = "OK";

CMeshType::CMeshType()
{
	this->pPlyFile = 0;
	this->Clear();
	return;
}

CMeshType::CMeshType( std::string theName, std::string theFileName )
{
	this->pPlyFile = 0;
	this->Clear();
	this->name = theName;
	// The plyloader will use this name as the file name
	this->filename = theFileName;	// Was "theName". sorry.
	return;
}

CMeshType::CMeshType( std::string theName, std::string theFileName, CMeshLoadParams meshLoadingParams )
{
	this->pPlyFile = 0;
	this->Clear();
	this->name = theName;
	// The plyloader will use this name as the file name
	this->filename = theFileName;	// Was "theName". sorry.
	this->meshLoadingParams = meshLoadingParams;
	return;
}


void CMeshType::Clear(void)
{
	this->name = "";
	this->filename = "";
	this->GL_VBO_ID = 0;
	this->GL_VertexBuffer_ID = 0;
	this->GL_IndexBuffer_ID = 0;
	// Should clear the ply thingy, too, I suppose
	if ( this->pPlyFile != 0 )
	{
		delete this->pPlyFile;
	}
	this->pPlyFile = 0;
	return;
}

// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now (and works file converting just the ASCII characters)
std::wstring CModelTypeManager::ASCIIToUnicodeQnD( std::string ASCIIString )
{
	std::wstringstream ss;
	for ( std::string::iterator itChar = ASCIIString.begin(); itChar != ASCIIString.end(); itChar++ )
	{
		char tempChar = *itChar;
		wchar_t tempCharUni = static_cast< wchar_t >( tempChar );
		ss << tempCharUni;
	}
	return ss.str();
}

// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
// But this is "good enough" for now (and works file converting just the ASCII characters)
std::string CModelTypeManager::UnicodeToASCII_QnD( std::wstring UnicodeString )
{
	std::stringstream ssReturnASCII;
	for ( std::wstring::iterator itChar = UnicodeString.begin(); itChar != UnicodeString.end(); itChar++ )
	{
		char theChar = static_cast<char>( *itChar );
		ssReturnASCII << theChar;
	}
	return ssReturnASCII.str();
}


bool CModelTypeManager::LoadModelTypeFromFile( CMeshType &meshLoaded, std::string &error  )
{
	// Already got one of these? 
	if ( this->m_mapMeshTypes.find( meshLoaded.name ) != this->m_mapMeshTypes.end() ) 
	{	// Already have this one
		std::stringstream ss;
		ss << "Mesh >" << meshLoaded.name << "< is already loaded with file >" 
			<< this->m_mapMeshTypes.find( meshLoaded.name )->second.filename << "<.";
		error = ss.str();
		return false;
	}

	// Update the filename with the full path
	meshLoaded.fileNameFullPath =  this->m_baseFilePath + meshLoaded.filename;

	// Haven't loaded this one, yet
	std::wstring tempfileName = this->ASCIIToUnicodeQnD( meshLoaded.fileNameFullPath );
	std::wstring wError;
	
	if ( meshLoaded.pPlyFile != 0 )
	{	// Delete the ply file if already present (like you passed one in)
		delete meshLoaded.pPlyFile;
	}
	meshLoaded.pPlyFile = new CPlyFile5nt();
	//if ( !meshLoaded.pPlyFile->OpenPLYFile( tempfileName, wError ) )		// Loads everything students have thrown at it for 7+ years
	if ( !meshLoaded.pPlyFile->OpenPLYFile2( tempfileName, wError ) )		// (way) faster, but doesn't load every type (most, though)
	{
		// Didn't load it
		std::stringstream ssError;
		ssError << "Can't load ply model from that file: " << this->UnicodeToASCII_QnD( wError );
		error = ssError.str();
		return false;
	}

	// It's loaded

	if ( meshLoaded.meshLoadingParams.bScaleOnLoad )
	{
		if ( meshLoaded.meshLoadingParams.bScaleToCube )
		{
			meshLoaded.pPlyFile->ScaleToFit( meshLoaded.meshLoadingParams.fScaleOnLoadValue );
		}
		else 
		{
			meshLoaded.pPlyFile->scaleVertices( meshLoaded.meshLoadingParams.fScaleOnLoadValue );
		}
	}// if ( loadParams.bScaleOnLoad )



	// Not really needed as ScaleToFit() does this already, but YOLO! Am I right?!?
	meshLoaded.pPlyFile->calcualteExtents();

	// START OF: Calculate normals?
	if ( meshLoaded.meshLoadingParams.bForceNormalRecalcOnLoad )
	{
		meshLoaded.pPlyFile->normalizeTheModelBaby();
	}
	else if ( !meshLoaded.pPlyFile->bHadNormalsInFile() && meshLoaded.meshLoadingParams.bCalcNormalsIfNotPresent )
	{
		meshLoaded.pPlyFile->normalizeTheModelBaby();
	}
	// END OF: Calculate normals?

	// START OF: Calculate texture coordinates?
	// Texture coordinates?
	if ( meshLoaded.meshLoadingParams.bForceTextureCoordRecalcOnLoad )
	{
		meshLoaded.pPlyFile->GenTextureCoordsSpherical( CPlyFile5nt::POSITIVE_X, CPlyFile5nt::POSITIVE_Y,
			                                            meshLoaded.meshLoadingParams.bCalcTextureCoordsByNormal, true, false );
	}
	else if ( !meshLoaded.pPlyFile->bHadTextureCoordinatesInFile() && meshLoaded.meshLoadingParams.bCalcTextureCoordsIfNotPresent )
	{
		meshLoaded.pPlyFile->GenTextureCoordsSpherical( CPlyFile5nt::POSITIVE_X, CPlyFile5nt::POSITIVE_Y,
			                                            meshLoaded.meshLoadingParams.bCalcTextureCoordsByNormal, true, false );
	}
	// END OF: Calculate texture coordinates?

	// At this point, the ply model is loaded and we can copy it up into the GL buffers...

	// This code is taken from the LoadMeshDataIntoBuffers()


	// Used to have a hard coded cube. While sexy, it's now gone.
	unsigned int numVerticesInVertArray = static_cast<unsigned int>( meshLoaded.pPlyFile->GetNumberOfVerticies() );


	// Allocate a C-style array for our vertices
	// Also, maybe make this a little bigger just in case
	// (hence the *2 value)
	Vertex_p4n4t4* pTempVertArray = new Vertex_p4n4t4[ numVerticesInVertArray * 2 ];

	// Copy the "nice" type into the C stye array
	for ( int index = 0; index != numVerticesInVertArray; index++)
	{
		PlyVertex tempVertex = meshLoaded.pPlyFile->getVertex_at( index );

		pTempVertArray[index].Pos.x = tempVertex.xyz.x;
		pTempVertArray[index].Pos.y = tempVertex.xyz.y;
		pTempVertArray[index].Pos.z = tempVertex.xyz.z;
		pTempVertArray[index].Pos.w = 1.0f;	// w
		
		// We are stealing the "color" to place normals in it
		pTempVertArray[index].Normal.x = tempVertex.nx;	
		pTempVertArray[index].Normal.y = tempVertex.ny;
		pTempVertArray[index].Normal.z = tempVertex.nz;
		pTempVertArray[index].Normal.w = 1.0f;	// Alpha

		pTempVertArray[index].TextUVx2.x = tempVertex.tex0u;
		pTempVertArray[index].TextUVx2.y = tempVertex.tex0v;
		pTempVertArray[index].TextUVx2.z = tempVertex.tex1u;
		pTempVertArray[index].TextUVx2.w = tempVertex.tex1v;
	}


	// Remember there are three indices per triangle
	unsigned int numIndicesInIndexArray = meshLoaded.pPlyFile->GetNumberOfElements() * 3;
	// Index buffers are 1D arrays, not triangles...
	// Again, you might want to make this a little bigger 
	//	that we need (hence the X2) 

	GLuint* pIndexArrayLocal = new GLuint[numIndicesInIndexArray * 2];

	int triIndex = 0;	// The "triangle" index (of the vector)
	int index = 0;		// The index into the index buffer
	for ( ; 
		  triIndex != meshLoaded.pPlyFile->GetNumberOfElements(); 
		  triIndex++, index += 3 )
	{
		PlyElement tempElement = meshLoaded.pPlyFile->getElement_at( triIndex );

		pIndexArrayLocal[index + 0]  = tempElement.vertex_index_1;
		pIndexArrayLocal[index + 1]  = tempElement.vertex_index_2;
		pIndexArrayLocal[index + 2]  = tempElement.vertex_index_3;
	}
	

	GLenum errorEnum;
	std::string errorString;
	std::string errorDetails;

	// glGenVertexArrays(1, &BufferIds[0]);
	//lGenVertexArrays( 1, &VBO_ID );
	glGenVertexArrays( 1, &(meshLoaded.GL_VBO_ID) );
	//ExitOnGLError("ERROR: Could not generate the VAO");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}


	//glBindVertexArray(BufferIds[0]);
	//glBindVertexArray( VBO_ID );
	glBindVertexArray( meshLoaded.GL_VBO_ID );
	//ExitOnGLError("ERROR: Could not bind the VAO");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);	// UV (texture) coordinates
	//ExitOnGLError("ERROR: Could not enable vertex attributes");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}



	//glGenBuffers(2, &BufferIds[1]);
	// This line above is the same as the two lines below...
	//glGenBuffers(1, &BufferIds[1]);
	//glGenBuffers(1, &BufferIds[2]);

	//glGenBuffers(1, &vertexBuffer_ID );
	//glGenBuffers(1, &indexBuffer_ID );
	glGenBuffers(1, &(meshLoaded.GL_VertexBuffer_ID) );
	glGenBuffers(1, &(meshLoaded.GL_IndexBuffer_ID) );
	//ExitOnGLError("ERROR: Could not generate the buffer objects");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}

	//glBindBuffer(GL_ARRAY_BUFFER, BufferIds[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_ID );
	glBindBuffer(GL_ARRAY_BUFFER, meshLoaded.GL_VertexBuffer_ID );


	// Copy this local vertex buffer up to the GPU
	//glBufferData(GL_ARRAY_BUFFER, 
		//          sizeof(VERTICES),	// How big is each vertex?
		//          VERTICES, 
		//	   GL_STATIC_DRAW);

	unsigned int totalVertBufferSizeBYTES = numVerticesInVertArray * sizeof( Vertex_p4n4t4 );

	glBufferData(GL_ARRAY_BUFFER, 
				totalVertBufferSizeBYTES,	// How big is all of it?
				pTempVertArray,				// Pointer to the actual data
				GL_STATIC_DRAW);

	//ExitOnGLError("ERROR: Could not bind the VBO to the VAO");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}


	unsigned int bytesInOneVertex = sizeof( Vertex_p4n4t4 );
	unsigned int byteOffsetToPosition = offsetof( Vertex_p4n4t4, Pos );			// This is really zero (at the start of the vertex structure)
	unsigned int byteOffsetToNormal = offsetof( Vertex_p4n4t4, Normal );		// Four floats in, so 4 x (4 bytes), so 16 bytes in
	unsigned int byteOffsetToUVCoords = offsetof( Vertex_p4n4t4, TextUVx2 );	// Another four in, so 16 + (4 x (4 bytes) ) = 32 bytes in

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 
						  bytesInOneVertex,			// sizeof( Vertex_p4n4t4 ),	
						  (GLvoid*)byteOffsetToPosition );
						  //(GLvoid*)0 );

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 
						  bytesInOneVertex,			// sizeof( Vertex_p4n4t4 ),	
						  (GLvoid*)byteOffsetToNormal );

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 
						  bytesInOneVertex,			// sizeof( Vertex_p4n4t4 ),	
						  (GLvoid*)byteOffsetToUVCoords );

	//ExitOnGLError("ERROR: Could not set VAO attributes");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[2]);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_ID );
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshLoaded.GL_IndexBuffer_ID );


	// This is the index buffer copy into GPU
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		//          sizeof(INDICES), 
		//	   INDICES, 
		//	   GL_STATIC_DRAW);

	unsigned int sizeOfIndexArrayInBytes = 
					numIndicesInIndexArray * sizeof( GLuint );

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
				sizeOfIndexArrayInBytes,		// total size in bytes, 
				pIndexArrayLocal,			// Pointer to array
				GL_STATIC_DRAW);


	//ExitOnGLError("ERROR: Could not bind the IBO to the VAO");
	if ( COpenGLError::bWasThereAnOpenGLError(errorEnum, errorString, errorDetails ) )
	{
		std::stringstream ss;
		ss << errorString << ":" << errorDetails;
		error = ss.str();
		return false;
	}

	//glBindVertexArray(BufferIds[0]);
	glBindVertexArray(0);

	// Get rid of the temporary "client" (CPU RAM) side arrays
	delete [] pTempVertArray;			// not goofy syntax trap
	delete [] pIndexArrayLocal;


	// Save this into the map so we can look it up later...
	// map is of this type: map< string, CMeshType >
	this->m_mapMeshTypes[ meshLoaded.name ] = meshLoaded;


	error = CModelTypeManager::STRINGNOERROR;
	return true;
}


// Looks at the file name of the "meshLoaded"
bool CModelTypeManager::GetModelInfoByName( CMeshType &meshLoaded, std::string &error )
{
	// Find the model by name...
	std::map< std::string /*name*/, CMeshType >::iterator itMesh = this->m_mapMeshTypes.find( meshLoaded.name );
	if ( itMesh == this->m_mapMeshTypes.end() )
	{	// Didn't find it
		std::stringstream ss;
		ss << "Can't find >" << meshLoaded.name << "< model";
		error = ss.str();
		return false;
	}

	// We've found the information
	meshLoaded = itMesh->second;

	return true;
}

// Looks at the FILE NAME of the "meshLoaded"
bool CModelTypeManager::GetModelInfoByFileName( CMeshType &meshLoaded, std::string &error )
{
	// Find the model by FILE name...
	// Map is indexed by "type" name (the name of the "type" of mesh we wanted), not the 
	//	filename, so we have to do a linear search through the map
	for ( std::map< std::string /*name*/, CMeshType >::iterator itMesh = this->m_mapMeshTypes.begin();
		  itMesh != this->m_mapMeshTypes.end(); itMesh++ )
	{
		if ( itMesh->second.filename == meshLoaded.filename )
		{	// Copy the information
			meshLoaded = itMesh->second;
			return true;
		}
	}

	// We didn't find it
	std::stringstream ss;
	ss << "Can't find >" << meshLoaded.filename << "< model";
	error = ss.str();
	return false;
}

// Same as above, but you add a vector or mesh types
bool CModelTypeManager::LoadModelTypesFromFile( std::vector< CMeshType > vecMeshesToLoad, std::string &error )
{
	std::stringstream ssErrors;
	bool bAllGood = true;	// Assume everything went OK
	for ( std::vector< CMeshType >::iterator itMeshToLoad = vecMeshesToLoad.begin();
	      itMeshToLoad != vecMeshesToLoad.end(); itMeshToLoad++ )
	{
		if ( ! this->LoadModelTypeFromFile( (*itMeshToLoad), error ) )
		{
			bAllGood = false;	// We got at least one error
			ssErrors << error << "\n";
		}
	}
	if ( ! bAllGood )
	{
		// Copy the (potential multiple) error(s) to the string
		error = ssErrors.str();
		return false;
	}
	// It's all good
	return true;
}





void CModelTypeManager::getInformationDumpOfModelInfo(std::string &infomation)
{
	std::stringstream ss;
	for ( std::map< std::string /*name*/, CMeshType >::iterator itMeshType = this->m_mapMeshTypes.begin();
		  itMeshType != this->m_mapMeshTypes.end(); itMeshType++ )
	{
		ss << "Name: " << itMeshType->first
			<< ", " << itMeshType->second.filename 
			<< ", " << itMeshType->second.fileNameFullPath
			<< ", IndexBuffID: " << itMeshType->second.GL_IndexBuffer_ID
			<< ", GL_VGO_ID: " << itMeshType->second.GL_VBO_ID
			<< ", VertexBuffID: " << itMeshType->second.GL_VertexBuffer_ID
			<< ", Triangles: " << itMeshType->second.pPlyFile->GetNumberOfElements()
			<< ", Verts: " <<itMeshType->second.pPlyFile->GetNumberOfVerticies() << std::endl;
		ss << std::endl;
	}
	infomation = ss.str();
	return;
}
