#ifndef _CModelTypeManager_HG_
#define _CModelTypeManager_HG_

// This thing handles the loading of the model files, along with 
//	looking up the rendering information as needed.

#include "Ply/CPlyFile5nt.h"
#include <map>
#include <string>

class CMeshLoadParams
{
public:
	CMeshLoadParams() : 
		bScaleOnLoad(true), fScaleOnLoadValue(1.0f), bScaleToCube(false),
	    bCalcNormalsIfNotPresent(true), bForceNormalRecalcOnLoad(false),
		bCalcTextureCoordsIfNotPresent(true), bForceTextureCoordRecalcOnLoad(false), bCalcTextureCoordsByNormal(false) {}; 
	bool bScaleOnLoad;
	float fScaleOnLoadValue;		// Scale to use
	bool bScaleToCube;		// If this is true, then "scaleOnLoad" is the size of bounding box to use
	bool bCalcNormalsIfNotPresent;
	bool bForceNormalRecalcOnLoad;
	bool bCalcTextureCoordsIfNotPresent;
	bool bForceTextureCoordRecalcOnLoad;
	bool bCalcTextureCoordsByNormal;
};

struct CMeshType
{
public:
	CMeshType();
	CMeshType( std::string theName, std::string theFileName );
	CMeshType( std::string theName, std::string theFileName, CMeshLoadParams meshLoadingParams );
	std::string name;
	std::string filename;
	std::string fileNameFullPath;
	// This will hold all of the ply information that we loaded (extents, number of vertices, etc.)
	CPlyFile5nt* pPlyFile;
	// Note that we're using 'unsigned int' instead of GLuint so we don't have to include the GL headers
	unsigned int GL_VBO_ID;
	unsigned int GL_VertexBuffer_ID;
	unsigned int GL_IndexBuffer_ID;
	CMeshLoadParams meshLoadingParams;
	void Clear(void);
};

class CModelTypeManager
{
public:
	CModelTypeManager();
	~CModelTypeManager();

	void SetBaseFilePath( std::string baseFilePath );
	std::string GetBaseFilePath(void);

	// The 'name' is the identifier we are using, which can be the same as the file name if you want
	// The name and file name are taken from the "meshLoaded". Any information is returned (if you want it)
	bool LoadModelTypeFromFile( CMeshType &meshLoaded, std::string &error );
	// Same as above, but you add a vector or mesh types
	bool LoadModelTypesFromFile( std::vector< CMeshType > vecMeshesToLoad, std::string &error );

	// Looks at the file name of the "meshLoaded"
	bool GetModelInfoByName( CMeshType &meshLoaded, std::string &error );
	bool GetModelInfoByFileName( CMeshType &meshLoaded, std::string &error );

	// NOTE: There are WAY better (i.e. safer!) ways to do this. See MultiByteToWideChar(), etc. in windows
	// But this is "good enough" for now (and works file converting just the ASCII characters)
	std::wstring ASCIIToUnicodeQnD( std::string ASCIIString );
	std::string UnicodeToASCII_QnD( std::wstring UnicodeString );

	static const std::string STRINGNOERROR;// = "OK";

	
	void getInformationDumpOfModelInfo(std::string &infomation);

private:
	// Map of name to mesh type
	std::map< std::string /*name*/, CMeshType > m_mapMeshTypes;

	std::string m_baseFilePath;
};

#endif
