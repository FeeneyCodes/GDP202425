#include "CGLPrintf.h"
#include <sstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>	

CGLPrintf::CGLPrintf( CModelTypeManager* pModelTypeManager, CGameObjectManager* pGameObjectManager )
{
	this->m_pModelTypeManager = pModelTypeManager;
	this->m_pGameObjectManager = pGameObjectManager;
	return;
}

CGLPrintf::~CGLPrintf()
{
	// TODO: Delete all the font objects??? 
	return;
}

void CGLPrintf::SetBaseDirectory( std::string baseDirectory )
{
	this->m_baseDirectory = baseDirectory;
	return;
}

//bool CGLPrintf::LoadCharacterSet( std::string fontName, std::string folderName, std::string &error )
//{
//	return true;
//}



bool CGLPrintf::LoadCharacterSet( std::string fontName, std::string folderName, CGLPrintf::sLoadOptions loadOptions, std::string &error )

{
	// Already have this font? 
	if ( this->m_mapFonts.find(fontName) != 
		 this->m_mapFonts.end() )
	{	// Yup. What ARE you doing, man!?
		error = "That font is already loaded.";
		return false;
	}
	// Load this font 


	sFontInfo newFont;
	newFont.fontName = fontName;
	newFont.spaceCharacterSizeMode = SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH;
	newFont.characterSpacing = 0.0f;		// Will be calculated after fonts are loaded
	newFont.fontScale = 1.0f;				// Will be calculated after fonts are loaded
	newFont.spaceCharacterSize = 0.0f;		// Will be calculated after fonts are loaded
//	// Load all the placeholders for the characters
//	for ( unsigned char charIndex = 0; charIndex != MAXNUMBEROFCHARACTERS; charIndex++ )
//	{
//		sCharRenderInfo curChar;	
//		curChar.ASCII_Value = charIndex;
//		newFont.mapFont_mapASCII_to_pGO[charIndex] = curChar;
//	}

	// There is a font in there, but there's no actual data (mesh info) loaded, yet
	// (all characters are "not valid" in other words)


	// Get a list of all the mesh files that we need
	std::vector< sMeshLoadingInfo > vecMeshFilesToLoad;
	this->m_GenerateMeshFileLoadList( vecMeshFilesToLoad );

	// Use the type manager to load them all
	bool bAllCharactersLoaded = true;	// error flag
	std::stringstream ssCharsNotLoaded;
	ssCharsNotLoaded << "Some characters were not loaded: " << std::endl;

	for ( std::vector< sMeshLoadingInfo >::iterator itMeshFile = vecMeshFilesToLoad.begin(); 
		  itMeshFile != vecMeshFilesToLoad.end(); itMeshFile++ )
	{
		// In here as the LoadModelTypeFromFile is passed by reference to continue to get loaded
		CMeshType meshToLoad;
		// START OF: same for all characters being loaded
		meshToLoad.meshLoadingParams.bScaleOnLoad = false;			//loadOptions.bScaleFontOnLoad;
		meshToLoad.meshLoadingParams.fScaleOnLoadValue = false;		//loadOptions.scaleOnLoad;
		meshToLoad.meshLoadingParams.bScaleToCube = false;			//loadOptions.bInterpretScaleAsBoundingBox;
		meshToLoad.meshLoadingParams.bCalcTextureCoordsByNormal = false;
		meshToLoad.meshLoadingParams.bCalcNormalsIfNotPresent = true;
		meshToLoad.meshLoadingParams.bCalcTextureCoordsIfNotPresent = true;
		// END OF: same for all characters being loaded
		meshToLoad.name = fontName + "/" + itMeshFile->meshFileToLoad;
		meshToLoad.filename = this->m_baseDirectory + "/" + fontName + "/" + itMeshFile->meshFileToLoad;

		if ( this->m_pModelTypeManager->LoadModelTypeFromFile( meshToLoad, error ) )
		{	// character loaded, so get the informaiton 
			itMeshFile->bMeshWasLoaded = true;
			// Create a game object to match
			unsigned int charID = 0;
			if ( this->m_pGameObjectManager->AddGameObjectToWorld( meshToLoad.filename, true, charID, error  ) )
			{	// Object is loaded into game world
				sCharRenderInfo curCharInfo;	
				curCharInfo.ASCII_Value = itMeshFile->renderInfo.ASCII_Value;
				curCharInfo.pGO = this->m_pGameObjectManager->FindGameObjectByID( charID );
				// We get max, rather than delta, since the characters are offset from the origin
				// (i.e. the origin is where the proportional font mesh 'starts', and the next 
				//  character starts relative to the "end" of the x, for instance)
				curCharInfo.meshSizeMax.x = meshToLoad.pPlyFile->getMaxX();
				curCharInfo.meshSizeMax.y = meshToLoad.pPlyFile->getMaxY();
				curCharInfo.meshSizeMax.z = meshToLoad.pPlyFile->getMaxZ();
				curCharInfo.meshSizeMin.x = meshToLoad.pPlyFile->getMinX();
				curCharInfo.meshSizeMin.y = meshToLoad.pPlyFile->getMinY();
				curCharInfo.meshSizeMin.z = meshToLoad.pPlyFile->getMinZ();
//				curCharInfo.maxExtent = meshToLoad.pPlyFile->getMaxExtent();
				curCharInfo.bIsValid = true;

				// Add character to map
				newFont.mapFont_mapASCII_to_pGO[curCharInfo.ASCII_Value] = curCharInfo;

				// Make the character mesh invisible (as it's part of the game world, but we don't want to draw it)
				this->m_pGameObjectManager->FindGameObjectByID(charID)->bIsVisible = false;
//				this->m_pGameObjectManager->FindGameObjectByID(charID)->position.y = 2.0f;

			}
			else
			{	// not sure what to do here... the mesh loaded, but we can't add it to the world...
				ssCharsNotLoaded << "Mesh " << meshToLoad.filename << " was loaded, but can't be added to the game world because " << error << std::endl;
				bAllCharactersLoaded = false;
			}//if ( this->m_pGameObjectManager->AddGameObjectToWorld
		}
		else 
		{	// Didn't load
			ssCharsNotLoaded << meshToLoad.filename << std::endl;
			bAllCharactersLoaded = false;
			// but we keep going
		}//if ( this->m_pModelTypeManager->LoadModelTypeFromFile( meshToLoad, error ) )
	}//for ( std::vector< sMeshLoadingInfo >::iterator itMeshFile....

	// Loaded them all? 
	if ( ! bAllCharactersLoaded ) 
	{
		error = ssCharsNotLoaded.str();
	}

	// The objects are all loaded, so update the font class... 
	newFont.meshCharWidthMin = newFont.mapFont_mapASCII_to_pGO.begin()->second.meshSizeMax.x;
	newFont.meshCharWidthMax = newFont.mapFont_mapASCII_to_pGO.begin()->second.meshSizeMax.x;
	float sumOfWidths = 0.0f;	// For calculation of average widths
	newFont.meshCharMaxHeight = newFont.mapFont_mapASCII_to_pGO.begin()->second.meshSizeMax.y;

	for ( std::map< unsigned char /*ASCII code*/, sCharRenderInfo >::iterator itChar = newFont.mapFont_mapASCII_to_pGO.begin();
		  itChar != newFont.mapFont_mapASCII_to_pGO.end(); itChar++ )
	{
		// Calcualte min and max
		if ( itChar->second.meshSizeMax.x < newFont.meshCharWidthMin )	{ newFont.meshCharWidthMin = itChar->second.meshSizeMax.x; }
		if ( itChar->second.meshSizeMax.x > newFont.meshCharWidthMax )	{ newFont.meshCharWidthMax = itChar->second.meshSizeMax.x; }
		if ( itChar->second.meshSizeMax.y > newFont.meshCharMaxHeight )	{ newFont.meshCharMaxHeight = itChar->second.meshSizeMax.y; }
		//sumOfWidths += itChar->second.sizeOfMesh.x;
		sumOfWidths += itChar->second.meshSizeMax.x;
	}//for ( std::map< unsigned char /*ASCII code*/, sCharRenderInfo >::iterator....

	newFont.meshCharWidthAverage = sumOfWidths / static_cast<float>(newFont.mapFont_mapASCII_to_pGO.size());

	this->m_mapFonts[newFont.fontName] = newFont;

	this->SetCharacterSpacingMode( newFont.fontName, SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MIN_CHARACTER_WIDTH, 1.0f );
	this->SetSpaceCharacterSize( newFont.fontName, SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH, 1.0f );

	// If this is the 1st font, set it to the current one
	if ( this->m_currentFont == "" )
	{
		this->m_currentFont = newFont.fontName;
	}


	return bAllCharactersLoaded;
}

// This takes into account the scaling and spacing inforamtion 
bool CGLPrintf::GetRenderListForString( std::string textToRender, std::vector< sCharRenderInfo > &vecCharacters, 
		                                glm::vec3 startPosition, glm::quat orientation, CAABB &AABB, float relativeScale /*=1.0f*/ )
{
	return this->GetRenderListForString( this->m_currentFont, textToRender, vecCharacters, startPosition, orientation, AABB, relativeScale );
}

glm::vec3 CGLPrintf::m_getLocationFromOrientation( glm::quat orientation, glm::vec3 posVector )
{
	glm::vec4 posVector4 = glm::vec4( posVector, 1.0f );	// Because we're multiplying by a mat4
	posVector4.w = 1.0f;	// The 4th value should always be 1.0f

	// calculate the matrix based on orientation 
	// #include <glm/gtx/quaternion.hpp>	
	glm::mat4 matOrientation = glm::toMat4( orientation );

	glm::vec4 posAdjustByOrientatoin = matOrientation * posVector4;

	return glm::vec3( posAdjustByOrientatoin );
}

bool CGLPrintf::GetRenderListForString( std::string fontName, std::string textToRender, std::vector< sCharRenderInfo > &vecCharacters, 
		                                glm::vec3 startPosition, glm::quat orientation, CAABB &AABB, float relativeScale /*=1.0f*/ )
{
	sRenderFormat renderFormat;
	renderFormat.startPosition = startPosition;
	renderFormat.qOrientation = orientation;
	renderFormat.relativeScale = relativeScale;

	bool bReturn = this->GetRenderListForString( fontName, textToRender, renderFormat, vecCharacters );
	AABB = renderFormat.AABB;
	return bReturn;
}

bool CGLPrintf::GetRenderListForString( std::string textToRender, CGLPrintf::sRenderFormat &renderFormat, 
									    std::vector< sCharRenderInfo > &vecCharacters )
{
	return this->GetRenderListForString( this->m_currentFont, textToRender, renderFormat, vecCharacters );
}

bool CGLPrintf::GetRenderListForString( std::string fontName, std::string textToRender, 
									    CGLPrintf::sRenderFormat &renderFormat, 
									    std::vector< sCharRenderInfo > &vecCharacters )
{
	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
	if ( itFont == this->m_mapFonts.end() )
	{	// We don't have that font
		return false;
	}

	vecCharacters.clear();
//	glm::vec3 curPosition = renderFormat.startPosition;	
	// String is printed at origin to start (so rotations are in model space, not world)
	glm::vec3 curPosition;	//  = renderFormat.startPosition;	

	for ( std::string::size_type indexChar = 0; indexChar != textToRender.length(); indexChar++ )
	{
		// Is the character a space?
		if ( textToRender[indexChar] == 32 )		// ASCII 32 is space, yo
		{
			// Set the current offset to take into account the space, then continue
			curPosition.x += itFont->second.spaceCharacterSize * itFont->second.fontScale * renderFormat.relativeScale;
			continue;
		}
		// It's not a space
		sCharRenderInfo curChar;
		this->m_GetCharacterRenderInfo( itFont, textToRender[indexChar], curChar );

		curChar.orientation = renderFormat.qOrientation;
//		curChar.position = this->m_getLocationFromOrientation( curChar.orientation, curPosition );// + startPosition;
		curChar.position = curPosition;
		curChar.scale = itFont->second.fontScale * renderFormat.relativeScale;

		vecCharacters.push_back( curChar );

		glm::vec3 meshSizeMaxScaled = curChar.meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale;

		// Move to next location
//		curPosition.x += ( curChar.meshSizeMax.x * relativeScale ); 
		curPosition.x += meshSizeMaxScaled.x;
		curPosition.x += ( itFont->second.characterSpacing * renderFormat.relativeScale );
	}//for ( std::string::size_type indexChar = 0;.....

	
	// Now calcualte the max and min so we can adjust the alignment... (then the overall AABB, which is dependent on orientation)

	// First the size of the characters themselves...(in world space)
	CAABB AABBCharacters;
	AABBCharacters.minXYZ = vecCharacters[0].position + (vecCharacters[0].meshSizeMin * itFont->second.fontScale * renderFormat.relativeScale);
	AABBCharacters.maxXYZ = vecCharacters[0].position + (vecCharacters[0].meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale);
	for ( std::vector< sCharRenderInfo >::iterator itChar = vecCharacters.begin(); itChar != vecCharacters.end(); itChar++ )
	{
		glm::vec3 charMin = itChar->position + (itChar->meshSizeMin * itFont->second.fontScale * renderFormat.relativeScale);
		glm::vec3 charMax = itChar->position + (itChar->meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale);

		// Note that the axes have to be done independantly
		if ( charMin.x < AABBCharacters.minXYZ.x ) { AABBCharacters.minXYZ.x = charMin.x; }
		if ( charMin.y < AABBCharacters.minXYZ.y ) { AABBCharacters.minXYZ.y = charMin.y; }
		if ( charMin.z < AABBCharacters.minXYZ.z ) { AABBCharacters.minXYZ.z = charMin.z; }
		if ( charMax.x > AABBCharacters.maxXYZ.x ) { AABBCharacters.maxXYZ.x = charMax.x; }
		if ( charMax.y > AABBCharacters.maxXYZ.y ) { AABBCharacters.maxXYZ.y = charMax.y; }
		if ( charMax.z > AABBCharacters.maxXYZ.z ) { AABBCharacters.maxXYZ.z = charMax.z; }
	}

	// Adjust for alignment:
	glm::vec3 alignmentAdjust;	// x is horizontal, y is vertical

	switch ( renderFormat.alignmentHorzontal )
	{
	case LEFT_ALIGNED:
		// Do nothing as they are already left aligned
		break;
	case CENTRE_ALIGNED:
		// Slide the characters along the left to left half the delta of the character bounding box
		alignmentAdjust.x -= ( AABBCharacters.maxXYZ.x - AABBCharacters.minXYZ.x )/2.0f;
		break;
	case RIGHT_ALIGNED:
		// Slide the characters along the left to the left the delta of the character bounding box
		alignmentAdjust.x -= ( AABBCharacters.maxXYZ.x - AABBCharacters.minXYZ.x );
		break;
	}

	// Now go through, updating the character position based on the alignment, then orientation
	for ( std::vector< sCharRenderInfo >::iterator itChar = vecCharacters.begin(); itChar != vecCharacters.end(); itChar++ )
	{
		itChar->position += alignmentAdjust;
		itChar->position = this->m_getLocationFromOrientation( renderFormat.qOrientation, itChar->position );
		// Place characters in world position (world space)
		itChar->position += renderFormat.startPosition;	

	}

	// Update the character alignment
	AABBCharacters.minXYZ += alignmentAdjust;
	AABBCharacters.maxXYZ += alignmentAdjust;
	// Adjust the final AABB relative to the position 
	renderFormat.AABB.minXYZ = this->m_getLocationFromOrientation( renderFormat.qOrientation, AABBCharacters.minXYZ );
	renderFormat.AABB.maxXYZ = this->m_getLocationFromOrientation( renderFormat.qOrientation, AABBCharacters.maxXYZ );
	// Adjust AABB into world space
	renderFormat.AABB.minXYZ += renderFormat.startPosition;	
	renderFormat.AABB.maxXYZ += renderFormat.startPosition;	


	return true;
}


// Used internally to get characters. If character doesn't exit, will return "unknown" characters

void CGLPrintf::m_GetCharacterRenderInfo( const std::map< std::string /*fontName*/, sFontInfo >::iterator &itFont, 
										  unsigned char ASCIICode, sCharRenderInfo &charRenderInfo )
{
	std::map< unsigned char /*ASCII code*/, sCharRenderInfo >::iterator itTheChar = itFont->second.mapFont_mapASCII_to_pGO.find( ASCIICode );
	// Find it? 
	if ( itTheChar != itFont->second.mapFont_mapASCII_to_pGO.end() )
	{	// Yes, we found it
		charRenderInfo = itTheChar->second;
		return;
	}
	else
	{	// Don't have that character, so pick the "unknown" character at location 0
		itTheChar == itFont->second.mapFont_mapASCII_to_pGO.find(0); 
		// Have we loaded an "unknown" character?
		if ( itTheChar == itFont->second.mapFont_mapASCII_to_pGO.end() )
		{	// All is truly lost - you didn't load an "unknown" character
			return;
		}
		// Return the (0) character
		charRenderInfo = itTheChar->second;
		return;
	}//if ( itTheChar == itFont->second.mapFont_mapASCII_to_pGO.end() )

	// Should never ger here....
	return;
}





// These are all based on the current mesh scale as loaded
void CGLPrintf::setFontRenderScale( float scale /*=1.0f*/ )
{
	// Check if we have a current font
	if ( this->m_currentFont != "" )
	{	
		this->m_mapFonts[this->m_currentFont].fontScale = scale;
	}
	return;
}

void CGLPrintf::setFontRenderScale( std::string fontName, float scale /*=1.0f*/ )
{
	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
	if ( itFont != this->m_mapFonts.end() )
	{	// Found the font
		itFont->second.fontScale = scale;
	}
	return;
}

// If true, then the scale is based on the relative height of the original mesh.
// (so scale of 1.0f means "size as loaded", and 2.0f would be 2x that size)
void CGLPrintf::calculateFontRenderScaleBasedOnMaxHeight( float desiredHeight )
{
	this->calculateFontRenderScaleBasedOnMaxHeight( this->m_currentFont, desiredHeight );
	return;
}

void CGLPrintf::calculateFontRenderScaleBasedOnMaxHeight( std::string fontName, float desiredHeight )
{
	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
	if ( itFont == this->m_mapFonts.end() )
	{	// We don't have that font
		return;
	}	

	itFont->second.fontScale = desiredHeight / itFont->second.meshCharMaxHeight;
	return;
}

bool CGLPrintf::SelectCurrentFont( std::string fontName )
{
	// If we've loaded the font, then set it to the current
	if ( this->m_mapFonts.find(fontName) != this->m_mapFonts.end() )
	{
		this->m_currentFont = fontName;
		return true;
	}
	// Don't have that font
	return false;
}

std::string CGLPrintf::GetCurrentFont(void)
{
	return this->m_currentFont;
}

void CGLPrintf::SetCharacterSpacingMode( enumCharacterSpacingMode characterSpacingMode, float sizeIfFixed_or_Ratio /*=1.0f*/ )
{ 
	this->SetCharacterSpacingMode( this->m_currentFont, characterSpacingMode, sizeIfFixed_or_Ratio );
	return;
}

void CGLPrintf::SetCharacterSpacingMode( std::string fontName, enumCharacterSpacingMode characterSpacingMode, float sizeIfFixed_or_Ratio /*=1.0f*/ )
{
	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
	if ( itFont == this->m_mapFonts.end() )
	{	// We don't have that font
		return;
	}	

	switch ( characterSpacingMode )
	{
	case SPACE_BETWEEN_CHARACTERS_IS_FIXED:
		itFont->second.characterSpacing = sizeIfFixed_or_Ratio;		
		break;
	case SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MIN_CHARACTER_WIDTH:		// Default
		itFont->second.characterSpacing = itFont->second.meshCharWidthMin * sizeIfFixed_or_Ratio;
		break;
	case SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_AVERAGE_CHARACTER_WIDTH:
		itFont->second.characterSpacing = itFont->second.meshCharWidthAverage * sizeIfFixed_or_Ratio;
		break;
	case SPACE_BETWEEN_CHARACTERS_IS_PERCENTAGE_OF_MAX_CHARACTER_WIDTH:
		itFont->second.characterSpacing = itFont->second.meshCharWidthMax * sizeIfFixed_or_Ratio;
		break;
	default: // should never happen
		assert(false);
		break;
	};

	itFont->second.characerSpacingMode = characterSpacingMode;
	return;
}


void CGLPrintf::SetSpaceCharacterSize( enumSpaceCharacterMode spaceCharacterMode, float sizeIfFixed_or_Ratio /*=1.0f*/ )
{
	this->SetSpaceCharacterSize( this->m_currentFont, spaceCharacterMode, sizeIfFixed_or_Ratio );
	return;
}

void CGLPrintf::SetSpaceCharacterSize( std::string fontName, enumSpaceCharacterMode spaceCharacterSize, float sizeIfFixed_or_Ratio /*=1.0f*/ )
{
	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
	if ( itFont == this->m_mapFonts.end() )
	{	// We don't have that font
		return;
	}	

	switch ( spaceCharacterSize )
	{
	case SPACE_CHAR_IS_MIN_CHAR_WIDTH:
		itFont->second.spaceCharacterSize = itFont->second.meshCharWidthMin * sizeIfFixed_or_Ratio;
		break;
	case SPACE_CHAR_IS_AVERAGE_CHAR_WIDTH:		// Defualt
		itFont->second.spaceCharacterSize = itFont->second.meshCharWidthAverage * sizeIfFixed_or_Ratio;
		break;
	case SPACE_CHAR_IS_MAX_CHAR_WIDTH:
		itFont->second.spaceCharacterSize = itFont->second.meshCharWidthMax * sizeIfFixed_or_Ratio;
		break;
	case SPACE_CHAR_IS_FIXED:
		itFont->second.spaceCharacterSize = sizeIfFixed_or_Ratio;
		break;
	default:
		assert(false);
		break;
	}

	itFont->second.spaceCharacterSizeMode = spaceCharacterSize;
	return;
}




CGLPrintf::sMeshLoadingInfo::sMeshLoadingInfo( unsigned char ASCIIValue, std::string meshFileToLoad )
{
	this->renderInfo.ASCII_Value = ASCIIValue;
	this->meshFileToLoad = meshFileToLoad;
	this->bMeshWasLoaded = false;
	return;
}


void CGLPrintf::m_GenerateMeshFileLoadList( std::vector< sMeshLoadingInfo > &meshFileLoadList )
{
	// Sort of tedious, but it is what it is...
	meshFileLoadList.clear();

	// Note: 32, a space, isn't here as it's set up in a diffent manner when 
	//	a string of text is prepared. That way the spacing can be controlled a little more
	meshFileLoadList.push_back( sMeshLoadingInfo( 33, "ASCII_033.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 34, "ASCII_034.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 35, "ASCII_035.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 36, "ASCII_036.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 37, "ASCII_037.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 38, "ASCII_038.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 39, "ASCII_039.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 40, "ASCII_040.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 41, "ASCII_041.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 42, "ASCII_042.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 43, "ASCII_043.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 44, "ASCII_044.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 45, "ASCII_045.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 46, "ASCII_046.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 47, "ASCII_047.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 48, "ASCII_048.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 49, "ASCII_049.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 50, "ASCII_050.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 51, "ASCII_051.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 52, "ASCII_052.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 53, "ASCII_053.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 54, "ASCII_054.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 55, "ASCII_055.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 56, "ASCII_056.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 57, "ASCII_057.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 58, "ASCII_058.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 59, "ASCII_059.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 60, "ASCII_060.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 61, "ASCII_061.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 62, "ASCII_062.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 63, "ASCII_063.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 64, "ASCII_064.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 65, "ASCII_065.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 66, "ASCII_066.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 67, "ASCII_067.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 68, "ASCII_068.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 69, "ASCII_069.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 70, "ASCII_070.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 71, "ASCII_071.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 72, "ASCII_072.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 73, "ASCII_073.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 74, "ASCII_074.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 75, "ASCII_075.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 76, "ASCII_076.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 77, "ASCII_077.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 78, "ASCII_078.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 79, "ASCII_079.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 80, "ASCII_080.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 81, "ASCII_081.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 82, "ASCII_082.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 83, "ASCII_083.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 84, "ASCII_084.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 85, "ASCII_085.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 86, "ASCII_086.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 87, "ASCII_087.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 88, "ASCII_088.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 89, "ASCII_089.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 90, "ASCII_090.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 91, "ASCII_091.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 92, "ASCII_092.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 93, "ASCII_093.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 94, "ASCII_094.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 95, "ASCII_095.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 96, "ASCII_096.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 97, "ASCII_097.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 98, "ASCII_098.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 99, "ASCII_099.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 100, "ASCII_100.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 101, "ASCII_101.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 102, "ASCII_102.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 103, "ASCII_103.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 104, "ASCII_104.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 105, "ASCII_105.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 106, "ASCII_106.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 107, "ASCII_107.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 108, "ASCII_108.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 109, "ASCII_109.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 110, "ASCII_110.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 111, "ASCII_111.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 112, "ASCII_112.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 113, "ASCII_113.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 114, "ASCII_114.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 115, "ASCII_115.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 116, "ASCII_116.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 117, "ASCII_117.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 118, "ASCII_118.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 119, "ASCII_119.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 120, "ASCII_120.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 121, "ASCII_121.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 122, "ASCII_122.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 123, "ASCII_123.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 124, "ASCII_124.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 125, "ASCII_125.ply" ) );
	meshFileLoadList.push_back( sMeshLoadingInfo( 126, "ASCII_126.ply" ) );
	// And some others
	meshFileLoadList.push_back( sMeshLoadingInfo( 161, "ASCII_161.ply" ) );		// (Inverted_Exclamation)
	meshFileLoadList.push_back( sMeshLoadingInfo( 169, "ASCII_169.ply" ) );		// (Copyright)
	meshFileLoadList.push_back( sMeshLoadingInfo( 174, "ASCII_174.ply" ) );		// (Registered_Trademark)
	meshFileLoadList.push_back( sMeshLoadingInfo( 176, "ASCII_176.ply" ) );		// (Degree)
	meshFileLoadList.push_back( sMeshLoadingInfo( 177, "ASCII_177.ply" ) );		// (Plus_Minus)
	meshFileLoadList.push_back( sMeshLoadingInfo( 191, "ASCII_191.ply" ) );		// (Inverted_Question)
	meshFileLoadList.push_back( sMeshLoadingInfo( 247, "ASCII_247.ply" ) );		// (Obelus)
	// This is for any character that we don't know
	meshFileLoadList.push_back( sMeshLoadingInfo( 0, "ASCII_XXX(UNKNOWN).ply") );

	return;
}

void CGLPrintf::ShutDown(void)
{
	// TODO: Some awesome stuff
	return;
}














//bool CGLPrintf::GetRenderListForString( std::string fontName, std::string textToRender, 
//									    CGLPrintf::sRenderFormat &renderFormat, 
//									    std::vector< sCharRenderInfo > &vecCharacters )
//{
//	std::map< std::string /*fontName*/, sFontInfo >::iterator itFont = this->m_mapFonts.find(fontName);
//	if ( itFont == this->m_mapFonts.end() )
//	{	// We don't have that font
//		return false;
//	}
//
//	vecCharacters.clear();
//	glm::vec3 curPosition = renderFormat.startPosition;	
//
//	for ( std::string::size_type indexChar = 0; indexChar != textToRender.length(); indexChar++ )
//	{
//		// Is the character a space?
//		if ( textToRender[indexChar] == 32 )		// ASCII 32 is space, yo
//		{
//			// Set the current offset to take into account the space, then continue
//			curPosition.x += itFont->second.spaceCharacterSize * itFont->second.fontScale * renderFormat.relativeScale;
//			continue;
//		}
//		// It's not a space
//		sCharRenderInfo curChar;
//		this->m_GetCharacterRenderInfo( itFont, textToRender[indexChar], curChar );
//
//		curChar.orientation = renderFormat.qOrientation;
//		curChar.position = this->m_getLocationFromOrientation( curChar.orientation, curPosition );// + startPosition;
//		curChar.position = curPosition;
//		curChar.scale = itFont->second.fontScale * renderFormat.relativeScale;
//
//		vecCharacters.push_back( curChar );
//
//		glm::vec3 meshSizeMaxScaled = curChar.meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale;
//
//		// Move to next location
////		curPosition.x += ( curChar.meshSizeMax.x * relativeScale ); 
//		curPosition.x += meshSizeMaxScaled.x;
//		curPosition.x += ( itFont->second.characterSpacing * renderFormat.relativeScale );
//	}//for ( std::string::size_type indexChar = 0;.....
//
//	
//	// Now calcualte the max and min so we can adjust the alignment... (then the overall AABB, which is dependent on orientation)
//
//	// First the size of the characters themselves...(in world space)
//	CAABB AABBCharacters;
//	AABBCharacters.minXYZ = vecCharacters[0].position + (vecCharacters[0].meshSizeMin * itFont->second.fontScale * renderFormat.relativeScale);
//	AABBCharacters.maxXYZ = vecCharacters[0].position + (vecCharacters[0].meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale);
//	for ( std::vector< sCharRenderInfo >::iterator itChar = vecCharacters.begin(); itChar != vecCharacters.end(); itChar++ )
//	{
//		glm::vec3 charMin = itChar->position + (itChar->meshSizeMin * itFont->second.fontScale * renderFormat.relativeScale);
//		glm::vec3 charMax = itChar->position + (itChar->meshSizeMax * itFont->second.fontScale * renderFormat.relativeScale);
//
//		// Note that the axes have to be done independantly
//		if ( charMin.x < AABBCharacters.minXYZ.x ) { AABBCharacters.minXYZ.x = charMin.x; }
//		if ( charMin.y < AABBCharacters.minXYZ.y ) { AABBCharacters.minXYZ.y = charMin.y; }
//		if ( charMin.z < AABBCharacters.minXYZ.z ) { AABBCharacters.minXYZ.z = charMin.z; }
//		if ( charMax.x > AABBCharacters.maxXYZ.x ) { AABBCharacters.maxXYZ.x = charMax.x; }
//		if ( charMax.y > AABBCharacters.maxXYZ.y ) { AABBCharacters.maxXYZ.y = charMax.y; }
//		if ( charMax.z > AABBCharacters.maxXYZ.z ) { AABBCharacters.maxXYZ.z = charMax.z; }
//	}
//
//	// Adjust for alignment:
//	glm::vec3 alignmentAdjust;	// x is horizontal, y is vertical
//
//	switch ( renderFormat.alignmentHorzontal )
//	{
//	case LEFT_ALIGNED:
//		// Do nothing as they are already left aligned
//		break;
//	case CENTRE_ALIGNED:
//		// Slide the characters along the left to left half the delta of the character bounding box
//		alignmentAdjust.x -= ( AABBCharacters.maxXYZ.x - AABBCharacters.minXYZ.x )/2.0f;
//		break;
//	case RIGHT_ALIGNED:
//		// Slide the characters along the left to the left the delta of the character bounding box
//		alignmentAdjust.x -= ( AABBCharacters.maxXYZ.x - AABBCharacters.minXYZ.x );
//		break;
//	}
//
//	//// Now go through, updating the character position based on the alignment, then orientation
//	//for ( std::vector< sCharRenderInfo >::iterator itChar = vecCharacters.begin(); itChar != vecCharacters.end(); itChar++ )
//	//{
//	//	itChar->position += alignmentAdjust;
//	//	itChar->position = this->m_getLocationFromOrientation( renderFormat.qOrientation, itChar->position );
//	//	// And update the mesh locations based on this, too
//	//}
//
//	// Update the character alignment
//	AABBCharacters.minXYZ += alignmentAdjust;
//	AABBCharacters.maxXYZ += alignmentAdjust;
//	// Adjust the final AABB relative to the position 
//	renderFormat.AABB.minXYZ = this->m_getLocationFromOrientation( renderFormat.qOrientation, AABBCharacters.minXYZ );
//	renderFormat.AABB.maxXYZ = this->m_getLocationFromOrientation( renderFormat.qOrientation, AABBCharacters.maxXYZ );
//
//
//
//	return true;
//}