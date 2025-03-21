#ifndef _CGLPrintf_HG_
#define _CGLPrintf_HG_

#include <string>
#include "CModelTypeManager.h"		// For loading the ply models
#include "CGameObjectManager.h"		// For creating the character set in the world
#include <vector>
#include <map>

// This handles the printing out of geometry based characters
// Assumes that the model files have the format:
// ASCII_XXX.ply, where the XXX is the ASCII number, 
// so "A" (capitol "A") would be ASCII_065.ply
// It will skip any characters it doesn't find
// Assumes that each font is in a separate folder
class CGLPrintf
{
public:
	CGLPrintf( CModelTypeManager* pModelTypeManager, CGameObjectManager* pGameObjectManager );
	~CGLPrintf();

	void ShutDown(void);

	void SetBaseDirectory( std::string baseDirectory );
	// Returns false if we can't find the directory, or you've already loaded this font
	bool LoadCharacterSet( std::string fontName, std::string folderName, std::string &error );
	struct sLoadOptions
	{
		sLoadOptions(): bScaleFontOnLoad(false), scaleOnLoad(1.0f), bInterpretScaleAsBoundingBox(false) {}
		bool bScaleFontOnLoad;	// false
		float scaleOnLoad;		// 1.0f
		bool bInterpretScaleAsBoundingBox;	// false;
	};
	bool LoadCharacterSet( std::string fontName, std::string folderName, sLoadOptions loadOptions, std::string &error );

	struct sCharRenderInfo
	{
		sCharRenderInfo() : ASCII_Value(0), scale(1.0f), bIsValid(false), /*maxExtent(0.0f),*/ pGO(NULL) {}
		unsigned char ASCII_Value;
		bool bIsValid;	// Did it load, etc. (does it actually have a mesh)
		CGameObject* pGO;		// "Mesh" (really a "game object") to render
		glm::vec3 position;		// These are for the particular character in the string
		glm::vec3 meshSizeMax;	// x is width, z is "thickness", y is height
		glm::vec3 meshSizeMin;	
//		float maxExtent;
		float scale;
		glm::quat orientation;
	};
	//Note: Only centre alignement is implemente
	enum eAlignmentHorizonal	{	LEFT_ALIGNED, CENTRE_ALIGNED, RIGHT_ALIGNED };

	// Returns a vector of sRenderInfo objects with appropriate positions
	// Returns "false" if not all the characters are found (I guess?)
	// (Note: AABB is not fully complete - does not take into account orientation)
	bool GetRenderListForString( std::string textToRender, std::vector< sCharRenderInfo > &vecCharacters, 
		                         glm::vec3 startPosition, glm::quat orientation, CAABB &AABB, float relativeScale = 1.0f );
	bool GetRenderListForString( std::string fontName, std::string textToRender, std::vector< sCharRenderInfo > &vecCharacters, 
		                         glm::vec3 startPosition, glm::quat orientation, CAABB &AABB, float relativeScale = 1.0f );
	//bool GetRenderListForString( std::string fontName, std::string textToRender, std::vector< sCharRenderInfo > &vecCharacters, 
	//	                         glm::vec3 startPosition, glm::quat orientation, eAlignmentHorizonal alignment );


	struct sRenderFormat
	{
		sRenderFormat() : alignmentHorzontal(LEFT_ALIGNED), relativeScale(1.0f) {};
		glm::vec3 startPosition;
		glm::quat qOrientation;
		float relativeScale;
		eAlignmentHorizonal alignmentHorzontal;
		CAABB AABB;
	};
	bool GetRenderListForString( std::string fontName, std::string textToRender, sRenderFormat &renderFormat, std::vector< sCharRenderInfo > &vecCharacters );
	bool GetRenderListForString( std::string textToRender, sRenderFormat &renderFormat, std::vector< sCharRenderInfo > &vecCharacters );

	// These are all based on the current mesh scale as loaded
	void setFontRenderScale( float scale = 1.0f );
	void setFontRenderScale( std::string fontName, float scale = 1.0f );
	// If true, then the scale is based on the relative height of the original mesh.
	// (so scale of 1.0f means "size as loaded", and 2.0f would be 2x that size)
	void calculateFontRenderScaleBasedOnMaxHeight( float desiredHeight );
	void calculateFontRenderScaleBasedOnMaxHeight( std::string fontName, float desiredHeight );

	// Returns false if that font isn't there (or is invalid)
	bool SelectCurrentFont( std::string fontName );
	// Returns empty string if not current font selected
	std::string GetCurrentFont(void);
	// If we are using bInterpretScaleAsMaxHeight

	// How far appart the characters are
	enum enumCharacterSpacingMode
	{
		SPACE_BETWEEN_CHARACTERS_IS_FIXED,
		SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MIN_CHARACTER_WIDTH,		// Default
		SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_AVERAGE_CHARACTER_WIDTH,
		SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MAX_CHARACTER_WIDTH
	};
	void SetCharacterSpacingMode( enumCharacterSpacingMode characterSpacingMode, float sizeIfFixed_or_Ratio = 1.0f );
	void SetCharacterSpacingMode( std::string fontName, enumCharacterSpacingMode characterSpacingMode, float sizeIfFixed_or_Ratio = 1.0f );


	// This is how big the " " (space) character is
	enum enumSpaceCharacterMode
	{
		SPACE_CHAR_IS_MIN_CHAR_WIDTH,
		SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH,		// Defualt
		SPACE_CHAR_IS_MAX_CHAR_WIDTH, 
		SPACE_CHAR_IS_FIXED
	};
	void SetSpaceCharacterSize( enumSpaceCharacterMode spaceCharacterMode, float sizeIfFixed_or_Ratio = 1.0f );
	void SetSpaceCharacterSize( std::string fontName, enumSpaceCharacterMode spaceCharacterSize, float sizeIfFixed_or_Ratio = 1.0f );

	 static const unsigned char MAXNUMBEROFCHARACTERS = 255;
private:
	CGLPrintf() {};

	std::string m_baseDirectory;
	// Stores the pointers to the various ASCII characters (NULL pointers means: there isn't any)
	// Indexed by "font name" (whatever you passed in when calling LoadCharacterSet
	// NOTE: When stored in here, this is 
	struct sFontInfo
	{
		sFontInfo() : 
			spaceCharacterSizeMode(SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH), 
			characerSpacingMode(SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MIN_CHARACTER_WIDTH),
			fontScale(0.0f),			/*can't be calculated until fonts are loaded*/
			spaceCharacterSize(0.0f),	/*can't be calculated until fonts are loaded*/
			characterSpacing(0.0f),		/*can't be calculated until fonts are loaded*/	
			meshCharMaxHeight(0.0f),	/*can't be calculated until fonts are loaded*/		
			meshCharWidthMin(0.0f),		/*can't be calculated until fonts are loaded*/	
			meshCharWidthMax(0.0f),		/*can't be calculated until fonts are loaded*/	
			meshCharWidthAverage(0.0f)	/*can't be calculated until fonts are loaded*/	
			{};
		std::string fontName;
		float fontScale;
		float spaceCharacterSize;
		enumSpaceCharacterMode spaceCharacterSizeMode;
		enumCharacterSpacingMode characerSpacingMode;
		float characterSpacing;
		float meshCharWidthMin;		float meshCharWidthMax;		float meshCharWidthAverage;
		float meshCharMaxHeight;
		std::map< unsigned char /*ASCII code*/, sCharRenderInfo > mapFont_mapASCII_to_pGO;
	};
	std::map< std::string /*fontName*/, sFontInfo > m_mapFonts;

	CModelTypeManager*		m_pModelTypeManager;
	CGameObjectManager*	m_pGameObjectManager;

	std::string m_currentFont;

	// Used internally to load the mesh information 
	struct sMeshLoadingInfo
	{
	sMeshLoadingInfo( unsigned char ASCIIValue, std::string meshFileToLoad );
		sCharRenderInfo renderInfo;	// Contains the ASCII value
		std::string meshFileToLoad;
		bool bMeshWasLoaded;
	};

	// This generates all the mesh files we need to load (the ones that are expected, anyway)
	void m_GenerateMeshFileLoadList( std::vector< sMeshLoadingInfo > &meshFileLoadList );

	// Used internally to get characters. If character doesn't exit, will return "unknown" characters
//	void m_GetCharacterRenderInfo( std::string fontName, unsigned char ASCIICode, sCharRenderInfo &charRenderInfo );
	void m_GetCharacterRenderInfo( const std::map< std::string /*fontName*/, sFontInfo >::iterator &itFont, unsigned char ASCIICode, sCharRenderInfo &charRenderInfo );


	glm::vec3 m_getLocationFromOrientation( glm::quat orientation, glm::vec3 posVector );
};

#endif
