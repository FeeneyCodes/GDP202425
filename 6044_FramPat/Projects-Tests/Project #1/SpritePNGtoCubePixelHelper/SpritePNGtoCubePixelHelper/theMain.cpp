#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// I used the INFO6044_SpaceInvader_Block_to_Model_Gizmo and 
// the Robotron3DTextToModelThingy code as a base for this one...
// Michael Feeney mfeeney@fanshawec.ca
// (or FeeneyCodes in various places)

#include "cImageThingy.h"


class cVertex
{
public:
	cVertex()
	{
		this->x = this->y = this->z = 0.0f;
		this->nx = this->ny = this->nz = 0.0f;
		this->r = this->g = this->b = this->a = 1.0f;
		this->u = this->v = 0.0f;
	}
	cVertex(float x_, float y_, float z_, float nx_, float ny_, float nz_, float r_, float g_, float b_, float a_, float u_, float v_)
	{
		this->x = x_;		this->y = y_;		this->z = z_;
		this->r = r_;		this->g = g_;		this->b = b_;		this->a = a_;
		this->nx = nx_;		this->ny = ny_;		this->nz = nz_;
		this->u = u_;		this->v = v_;
	}
	cVertex(double x_, double y_, double z_, double nx_, double ny_, double nz_,
			unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_,
			double u_, double v_)
	{
		this->x = (float)x_;		this->y = (float)y_;		this->z = (float)z_;
		this->r = (float)r_ / 255.0f;
		this->g = (float)g_ / 255.0f;
		this->b = (float)b_ / 255.0f;
		this->a = (float)a_ / 255.0f;
		this->nx = (float)nx_;		this->ny = (float)ny_;		this->nz = (float)nz_;
		this->u = (float)u_;		this->v = (float)v_;
	}
	float x, y, z;
	float nx, ny, nz;
	float r, g, b, a;
	float u, v;
};

class cTriangle
{
public:
	cTriangle()
	{
		this->index[0] = this->index[1] = this->index[2] = 0;
	}
	cTriangle(unsigned int index0, unsigned int index1, unsigned int index2)
	{
		this->index[0] = index0;
		this->index[1] = index1;
		this->index[2] = index2;
	}
	unsigned int index[3];
};

class cCube
{
public:
	cCube() {};
	std::vector<cVertex> vecVertices;
	std::vector<cTriangle> vecTris;
};

const float CUBE_WIDTH = 10.0f;


void centreOnX(std::vector<cVertex>& vecVertices)
{
	if (vecVertices.empty())
	{
		return;
	}

	float minX = vecVertices[0].x;
	float maxX = vecVertices[0].x;

	for (unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++)
	{
		if (vecVertices[vertIndex].x < minX) { minX = vecVertices[vertIndex].x; }
		if (vecVertices[vertIndex].x > maxX) { maxX = vecVertices[vertIndex].x; }
	}

	float midX = (maxX - minX - CUBE_WIDTH) / 2.0f;

	for (unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++)
	{
		vecVertices[vertIndex].x -= midX;
	}

	return;
}

void centreOnX(std::vector<cVertex>& vecVertices, float minX, float maxX)
{
	if (vecVertices.empty())
	{
		return;
	}

	float midX = (maxX - minX - CUBE_WIDTH) / 2.0f;

	for (unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++)
	{
		vecVertices[vertIndex].x -= midX;
	}

	return;
}


void alightBaseToXZPlane(std::vector<cVertex>& vecVertices)
{
	if (vecVertices.empty())
	{
		return;
	}

	float minY = vecVertices[0].y;

	for (unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++)
	{
		if (vecVertices[vertIndex].y < minY) { minY = vecVertices[vertIndex].y; }
	}

	for (unsigned int vertIndex = 0; vertIndex != vecVertices.size(); vertIndex++)
	{
		vecVertices[vertIndex].y -= minY;
	}

	return;
}

void addCubeToVector(std::vector<cVertex>& vecVertices, 
					 std::vector<cTriangle>& vecTris, cCube& cube, 
					 float xOffset, float yOffset, float zOffset)
{

	for (unsigned int triIndex = 0; triIndex != cube.vecTris.size(); triIndex++)
	{
		unsigned int vertBaseIndex = (unsigned int)vecVertices.size();

		// Get triangle vertices
		cVertex vert0 = cube.vecVertices[(cube.vecTris[triIndex].index[0])];
		cVertex vert1 = cube.vecVertices[(cube.vecTris[triIndex].index[1])];
		cVertex vert2 = cube.vecVertices[(cube.vecTris[triIndex].index[2])];

		vert0.x += xOffset;
		vert0.y += yOffset;
		vert0.z += zOffset;

		vert1.x += xOffset;
		vert1.y += yOffset;
		vert1.z += zOffset;

		vert2.x += xOffset;
		vert2.y += yOffset;
		vert2.z += zOffset;

		cTriangle curTri;
		curTri.index[0] = vertBaseIndex;
		curTri.index[1] = vertBaseIndex + 1;
		curTri.index[2] = vertBaseIndex + 2;

		vecVertices.push_back(vert0);
		vecVertices.push_back(vert1);
		vecVertices.push_back(vert2);

		vecTris.push_back(curTri);

	}

	return;
}


void calcBoundingBoxMinMax(std::vector<cVertex>& vecVertices,
						    float boundingBoxminXYZ[], float boundingBoxmaxXYZ[])
{
	for (cVertex& curVert : vecVertices)
	{
		if (curVert.x < boundingBoxminXYZ[0] ) {	boundingBoxminXYZ[0] = curVert.x; }
		if (curVert.y < boundingBoxminXYZ[1] ) {	boundingBoxminXYZ[1] = curVert.y; }
		if (curVert.z < boundingBoxminXYZ[2] ) {	boundingBoxminXYZ[2] = curVert.z; }

		if (curVert.x > boundingBoxmaxXYZ[0] ) {	boundingBoxmaxXYZ[0] = curVert.x; }
		if (curVert.y > boundingBoxmaxXYZ[1] ) {	boundingBoxmaxXYZ[1] = curVert.y; }
		if (curVert.z > boundingBoxmaxXYZ[2] ) {	boundingBoxmaxXYZ[2] = curVert.z; }
	}

	return;
}

void calcBoundingBoxMinMax( cCube& cube, float xOffset, float yOffset, float zOffset,
						    float boundingBoxminXYZ[], float boundingBoxmaxXYZ[])
{
	for (unsigned int triIndex = 0; triIndex != cube.vecTris.size(); triIndex++)
	{
		// Get triangle vertices
		cVertex vert0 = cube.vecVertices[(cube.vecTris[triIndex].index[0])];
		cVertex vert1 = cube.vecVertices[(cube.vecTris[triIndex].index[1])];
		cVertex vert2 = cube.vecVertices[(cube.vecTris[triIndex].index[2])];

		vert0.x += xOffset;
		vert0.y += yOffset;
		vert0.z += zOffset;

		vert1.x += xOffset;
		vert1.y += yOffset;
		vert1.z += zOffset;

		vert2.x += xOffset;
		vert2.y += yOffset;
		vert2.z += zOffset;

		if ( vert0.x < boundingBoxminXYZ[0] ) {	boundingBoxminXYZ[0] = vert0.x; }
		if ( vert0.y < boundingBoxminXYZ[1] ) {	boundingBoxminXYZ[1] = vert0.y; }
		if ( vert0.z < boundingBoxminXYZ[2] ) {	boundingBoxminXYZ[2] = vert0.z; }

		if ( vert1.x < boundingBoxminXYZ[0] ) {	boundingBoxminXYZ[0] = vert1.x; }
		if ( vert1.y < boundingBoxminXYZ[1] ) {	boundingBoxminXYZ[1] = vert1.y; }
		if ( vert1.z < boundingBoxminXYZ[2] ) {	boundingBoxminXYZ[2] = vert1.z; }

		if ( vert2.x < boundingBoxminXYZ[0] ) {	boundingBoxminXYZ[0] = vert2.x; }
		if ( vert2.y < boundingBoxminXYZ[1] ) {	boundingBoxminXYZ[1] = vert2.y; }
		if ( vert2.z < boundingBoxminXYZ[2] ) {	boundingBoxminXYZ[2] = vert2.z; }


		if ( vert0.x > boundingBoxmaxXYZ[0] ) {	boundingBoxmaxXYZ[0] = vert0.x; }
		if ( vert0.y > boundingBoxmaxXYZ[1] ) {	boundingBoxmaxXYZ[1] = vert0.y; }
		if ( vert0.z > boundingBoxmaxXYZ[2] ) {	boundingBoxmaxXYZ[2] = vert0.z; }

		if ( vert1.x > boundingBoxmaxXYZ[0] ) {	boundingBoxmaxXYZ[0] = vert1.x; }
		if ( vert1.y > boundingBoxmaxXYZ[1] ) {	boundingBoxmaxXYZ[1] = vert1.y; }
		if ( vert1.z > boundingBoxmaxXYZ[2] ) {	boundingBoxmaxXYZ[2] = vert1.z; }

		if ( vert2.x > boundingBoxmaxXYZ[0] ) {	boundingBoxmaxXYZ[0] = vert2.x; }
		if ( vert2.y > boundingBoxmaxXYZ[1] ) {	boundingBoxmaxXYZ[1] = vert2.y; }
		if ( vert2.z > boundingBoxmaxXYZ[2] ) {	boundingBoxmaxXYZ[2] = vert2.z; }
	}

	return;
}

void printPlyFile(std::string inputFileName, std::vector<cVertex>& vecVertices, std::vector<cTriangle>& vecTris);

void setCubeColour(cCube& theCube, unsigned char charRed255, unsigned char charGreen255, unsigned char charBlue255);
void setCubeColourFloat(cCube& theCube, float fRed, float fGreen, float fBlue);

void calcBoundingBoxMinMax( cCube& cube, float xOffset, float yOffset, float zOffset,
						    float boundingBoxminXYZ[], float boundingBoxmaxXYZ[]);

// Return the same string if it can't figure it out
// Scans from the end looking for the 1st slash
std::string getExeNameFromFullPath(std::string fullpath);
std::string getFileNameNoExtension(std::string fullpath);

void printUsage(std::string exeName)
{
	std::cout
		<< "Usage and switches" << std::endl
		<< " - 1st param is sprite file name" << std::endl
		<< "   (You can also drop the sprite PNG file onto the exe)" << std::endl
		<< " - pixelSize:X" << std::endl
		<< "       number of pixels that make up 1 pixel in image" << std::endl
		<< "       (note: no space after the colon)" << std::endl
		<< "  *********** ISN'T VERY GOOD AT THE MOMENT ***************" << std::endl
		<< " - guessPixelSize" << std::endl
		<< "       Will try to determine the pixel side from the image." << std::endl
		<< "       (It does this by seeing how many pixels are the same colour in a row.)" << std::endl
		<< "  *********** DOESN'T WORK CORRECTLY AT THE MOMENT ***********" << std::endl
		<< std::endl
		<< "Default pixel size is 1 pixel." << std::endl
		<< std::endl
		<< " - noBackgroundColourBlocks" << std::endl
		<< "       Will NOT output blocks of the 'background' colour." << std::endl
		<< std::endl
		<< "To determine the 'background' colour, it'll take the most common pixel" << std::endl
		<< " colour that it finds in the image. Like if most are black, it'll assume" << std::endl
		<< " that's the background colour." << std::endl
		<< std::endl
		<< "Example: " << std::endl
		<< std::endl
		<< exeName << " defenderSprite.png guessPixelSize" << std::endl
		<< exeName << " defenderSprite.png pixelSize:7" << std::endl
		<< std::endl;

	return;
}

int main(int argc, char* argv[])
{
	std::string exeName = getExeNameFromFullPath(argv[0]);


	if (argc == 1 || argc > 4 )
	{
		printUsage(exeName);
		return -1;
	}


	// Sprite file name is 2nd param
	std::string spriteFileName(argv[1]);
	if (spriteFileName.empty())
	{
		printUsage(exeName);
		return -1;
	}

	unsigned int pixelSize = 1;
	bool bGuessPixelSize = false;
	bool bNoBackgroundColourBlocks = true;


	// Scan for other params
	for (unsigned int argIndex = 2; argIndex != argc; argIndex++)
	{
		std::string curParam = argv[argIndex];
		if (curParam.find("guessPixelSize") != std::string::npos)
		{
			bGuessPixelSize = true;
		}

		std::string param3 = argv[2];
		if (curParam.find("noBackgroundColourBlocks") != std::string::npos)
		{
			bNoBackgroundColourBlocks = false;
		}

		// pixelSize:X
		if (curParam.find("pixelSize") != std::string::npos)
		{
			std::size_t colonOffset = curParam.find(":");
			if (colonOffset == std::string::npos)
			{
				// no colon
				printUsage(exeName);
				return -1;
			}

			// Get number after colon
			std::string strPixelSize = curParam.substr(colonOffset + 1);
			// Is it a number?
			pixelSize = atoi(strPixelSize.c_str());
			if (pixelSize == 0)
			{
				// Didn't find a number
				printUsage(exeName);
				return -1;
			}
		}//if (std::find(..."pixelSize") 

	}//for (unsigned int argIndex


	// Make cube
	cCube theCube;
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, 0, -1, 0, 255, 255, 255, 255, 0.666667, 0.000000));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, 0, -1, 0, 255, 255, 255, 255, 0.666667, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 0, -1, 0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, -0, -1, -0, 255, 255, 255, 255, 0.333333, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, -0, 1, 0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, -0, 1, 0, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -0, 1, 0, 255, 255, 255, 255, 0.000000, 0.666667));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 0, 1, 0, 255, 255, 255, 255, 0.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 0, 0, -1, 255, 255, 255, 255, 1.000000, 0.000000));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, 0, 0, -1, 255, 255, 255, 255, 1.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, 0, 0, -1, 255, 255, 255, 255, 0.666667, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, -0, -0, -1, 255, 255, 255, 255, 0.666667, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, 1, 0, -0, 255, 255, 255, 255, 0.000000, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 0, -5, 1, 0, -0, 255, 255, 255, 255, 0.333333, 0.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, -5, 1, 0, -0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 1, 0, 0, 255, 255, 255, 255, 0.000000, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, 0, 0, 1, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(5, 0, 5, 0, 0, 1, 255, 255, 255, 255, 0.333333, 1.000000));
	theCube.vecVertices.push_back(cVertex(5, 10, 5, 0, 0, 1, 255, 255, 255, 255, 0.000000, 1.000000));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -0, 0, 1, 255, 255, 255, 255, 0.000000, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 0, -5, -1, -0, -0, 255, 255, 255, 255, 0.666667, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 0, 5, -1, -0, -0, 255, 255, 255, 255, 0.333333, 0.666667));
	theCube.vecVertices.push_back(cVertex(-5, 10, 5, -1, -0, -0, 255, 255, 255, 255, 0.333333, 0.333333));
	theCube.vecVertices.push_back(cVertex(-5, 10, -5, -1, -0, 0, 255, 255, 255, 255, 0.666667, 0.333333));

	theCube.vecTris.push_back(cTriangle(0, 1, 2));
	theCube.vecTris.push_back(cTriangle(0, 2, 3));
	theCube.vecTris.push_back(cTriangle(4, 5, 6));
	theCube.vecTris.push_back(cTriangle(4, 6, 7));
	theCube.vecTris.push_back(cTriangle(8, 9, 10));
	theCube.vecTris.push_back(cTriangle(8, 10, 11));
	theCube.vecTris.push_back(cTriangle(12, 13, 14));
	theCube.vecTris.push_back(cTriangle(12, 14, 15));
	theCube.vecTris.push_back(cTriangle(16, 17, 18));
	theCube.vecTris.push_back(cTriangle(16, 18, 19));
	theCube.vecTris.push_back(cTriangle(20, 21, 22));
	theCube.vecTris.push_back(cTriangle(20, 22, 23));



	cImageThingy theSpriteImage;

	if ( ! theSpriteImage.loadImage(spriteFileName) )
	{
		std::cout << "Error: " << theSpriteImage.getLastError();
		return -1;
	}

	if (bGuessPixelSize)
	{
		pixelSize = theSpriteImage.guessPixelSize();

		// Did it guess one?
		if ( pixelSize == 0 )
		{
			// Nope
			std::cout << "Can't guess pixel size." << std::endl;
			std::cout
				<< "This could be because: " << std::endl
				<< "- The image isn't cropped right to the edge" << std::endl
				<< "- There are too many colours" << std::endl
				<< "- The pixels are really large" << std::endl
				<< "...or something else?" << std::endl
				<< std::endl
				<< "For best results, scale the image to 1 pixel per pixel." << std::endl
				<< std::endl;
			return -1;
		}
	}//if (bGuessPixelSize)

	// Either the pixel size is guessed correctly or it's been set...
	// ...or it's just one pixel

	theSpriteImage.setPixelSizeAndProcess(pixelSize);



	for (unsigned int row = 0; row != theSpriteImage.getHeight(); row++)
	{
		for (unsigned int col = 0; col != theSpriteImage.getWidth(); col++)
		{
			sPixelRGBA curPixel = theSpriteImage.getPixel(row, col);
			std::cout
				<< (unsigned int)(curPixel.R) / 26
				<< (unsigned int)(curPixel.G) / 26
				<< (unsigned int)(curPixel.B) / 26;
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (unsigned int row = 0; row != theSpriteImage.getScaledHeight(); row++)
	{
		for (unsigned int col = 0; col != theSpriteImage.getScaledWidth(); col++)
		{
			sPixelRGBA curPixel = theSpriteImage.getPixelScaled(row, col);

			std::cout
				<< (unsigned int)(curPixel.R) / 26
				<< (unsigned int)(curPixel.G) / 26
				<< (unsigned int)(curPixel.B) / 26;
			std::cout << " ";
		}
		std::cout << std::endl;
	}


	std::vector<cVertex> vecVertices;
	std::vector<cTriangle> vecTriangles;

	float boundingBoxminXYZ[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
	float boundingBoxmaxXYZ[3] = { 0.0f, 0.0f, 0.0f };


//	for (unsigned int row = 0; row != theSpriteImage.getHeight(); row++)
	for (unsigned int row = 0; row != theSpriteImage.getScaledHeight(); row++)
	{
//		for (unsigned int col = 0; col != theSpriteImage.getWidth(); col++)
		for (unsigned int col = 0; col != theSpriteImage.getScaledWidth(); col++)
		{
			float row_offset = (float)(theSpriteImage.getScaledHeight() - row) * CUBE_WIDTH;
			float col_offset = (float)col * CUBE_WIDTH;

//			sPixelRGBA curPixel = theSpriteImage.getPixel(row, col);
			sPixelRGBA curPixel = theSpriteImage.getPixelScaled(row, col);

			setCubeColour(theCube, curPixel.R, curPixel.G, curPixel.B);



			// If it's black, DON'T add a cube
			if ( ! curPixel.isBlack() )
			{
				addCubeToVector(vecVertices, vecTriangles, theCube, col_offset, row_offset, 0.0f);
			}
		}
		std::cout << std::endl;
	}

	calcBoundingBoxMinMax(vecVertices, boundingBoxminXYZ, boundingBoxmaxXYZ);

	centreOnX(vecVertices, boundingBoxminXYZ[0], boundingBoxmaxXYZ[0]);
	alightBaseToXZPlane(vecVertices);
//	centreOnX(vecVertices);
//	alightBaseToXZPlane(vecVertices);

	printPlyFile(spriteFileName, vecVertices, vecTriangles);

	return 0;
}

void printPlyFile(std::string inputFileName, std::vector<cVertex>& vecVertices, std::vector<cTriangle>& vecTris)
{
	// Replace the "txt" extension with "ply"
	std::string plyFileName = inputFileName;

	std::size_t decimalPointIndex = plyFileName.find_last_of('.');

	plyFileName[decimalPointIndex + 1] = 'p';
	plyFileName[decimalPointIndex + 2] = 'l';
	plyFileName[decimalPointIndex + 3] = 'y';

	std::ofstream outFile(plyFileName.c_str());

	outFile << "ply" << std::endl;
	outFile << "format ascii 1.0" << std::endl;
	outFile << "comment VCGLIB generated" << std::endl;
	outFile << "element vertex " << vecVertices.size() << std::endl;
	outFile << "property float x" << std::endl;
	outFile << "property float y" << std::endl;
	outFile << "property float z" << std::endl;
	outFile << "property float nx" << std::endl;
	outFile << "property float ny" << std::endl;
	outFile << "property float nz" << std::endl;
	outFile << "property uchar red" << std::endl;
	outFile << "property uchar green" << std::endl;
	outFile << "property uchar blue" << std::endl;
	outFile << "property uchar alpha" << std::endl;
	outFile << "property float texture_u" << std::endl;
	outFile << "property float texture_v" << std::endl;
	outFile << "element face " << vecTris.size() << std::endl;
	outFile << "property list uchar int vertex_indices" << std::endl;
	outFile << "end_header" << std::endl;

	for (unsigned int index = 0; index != vecVertices.size(); index++)
	{
		outFile
			<< vecVertices[index].x << " "
			<< vecVertices[index].y << " "
			<< vecVertices[index].z << " "
			<< vecVertices[index].nx << " "
			<< vecVertices[index].ny << " "
			<< vecVertices[index].nz << " "
			<< (unsigned int)(vecVertices[index].r * 255.0f) << " "
			<< (unsigned int)(vecVertices[index].g * 255.0f) << " "
			<< (unsigned int)(vecVertices[index].b * 255.0f) << " "
			<< (unsigned int)(vecVertices[index].a * 255.0f) << " "
			<< vecVertices[index].u << " "
			<< vecVertices[index].v << std::endl;
	}//for ( unsigned int index = 0;

	for (unsigned int index = 0; index != vecTris.size(); index++)
	{
		outFile
			<< "3 "
			<< vecTris[index].index[0] << " "
			<< vecTris[index].index[1] << " "
			<< vecTris[index].index[2] << std::endl;
	}//for ( unsigned int index = 0


	outFile.close();

	std::cout << "Wrote to " << plyFileName << " OK." << std::endl;

	return;
}

void setCubeColour(cCube& theCube, unsigned char charRed255, unsigned char charGreen255, unsigned char charBlue255)
{
	setCubeColourFloat(theCube, (float)charRed255 / 255.0f, (float)charGreen255 / 255.0f, (float)charBlue255 / 255.0f);
	return;
}

void setCubeColourFloat(cCube& theCube, float fRed, float fGreen, float fBlue)
{
	for (cVertex &vert : theCube.vecVertices )
	{
		vert.r = fRed;
		vert.g = fGreen;
		vert.b = fBlue;
	}
	return;
}




// Return the full path if it can't find anything
// (because you might have passed just the exe with no slashes)
// Scans from the end looking for the 1st slash
std::string getExeNameFromFullPath(std::string fullpath)
{
	// C:\z_FS\00_GDP\2024-2025\GDP202425\6044_FramPat\Projects-Tests\Project #1\SpritePNGtoCubePixelHelper\x64\Debug\SpritePNGtoCubePixelHelper.exe

	// Looks like the forward slash is what is passed by windows

	unsigned int lastIndexSlash = INT_MAX;
	for (unsigned int index = 0; index != fullpath.size(); index++)
	{
		if (fullpath[index] == '\\')
		{
			lastIndexSlash = index;
		}
	}//for (unsigned int index

	// Find it? 
	if (lastIndexSlash == INT_MAX)
	{
		return fullpath;
	}

	// Chop out the exe name
	return fullpath.substr(lastIndexSlash + 1);
}

// Return the full path if it can't find anything
// (because you might have passed just the exe with no slashes)
// Scans from the end looking for the 1st slash
std::string getFileNameNoExtension(std::string fullpath)
{
	// C:\z_FS\00_GDP\2024-2025\GDP202425\6044_FramPat\Projects-Tests\Project #1\SpritePNGtoCubePixelHelper\x64\Debug\SpritePNGtoCubePixelHelper.exe

	std::string fileName = getExeNameFromFullPath(fullpath);

	// Find the "." character
	std::size_t periodIndex = fileName.find('.');

	// Find it? 
	if (periodIndex == INT_MAX)
	{
		return fullpath;
	}

	// Chop out the file extension (after the ".")
	return fileName.substr(0, periodIndex);
}