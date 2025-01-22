#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct sPoint
{
	float x, y, z;
};

struct sTriangle
{
	unsigned int vertIndex[3];
};

class cMeshInfo
{
public:

	unsigned int numberOfVertices = 0;
	unsigned int numberOfTriangles = 0;

	std::vector<sPoint> vecVertices;
	std::vector<sTriangle> vecTriangles;
};

bool readPlyFile(std::string fileName, cMeshInfo& meshInfo)
{

		// Read all the text until I get to the word "vertex"
//    std::ifstream plyFile("assets/models/bun_zipper_res3.ply");
	std::ifstream plyFile(fileName.c_str());     // May also see .c_str() "c style string, char*"

	if (!plyFile.is_open())
	{
		return false;
	}

	std::string token = "";

	if (!plyFile.is_open())
	{
		return false;
	}

	//element vertex 1889
	while (token != "vertex")
	{
		plyFile >> token;
	};
	// Next info is the number of vertices
	//int numberOfVertices = 0;
	plyFile >> meshInfo.numberOfVertices;


	//element face 3851
	while (token != "face")
	{
		plyFile >> token;
	};
	// Next info is the number of vertices
	//int numberOfTriangles = 0;
	plyFile >> meshInfo.numberOfTriangles;

	//end_header
	// -0.0369122 0.127512 0.00276757 0.850855 0.5 
	while (token != "end_header")
	{
		plyFile >> token;
	};


	// end_header
	// -0.0369122 0.127512 0.00276757 0.850855 0.5
	for (unsigned index = 0; index != meshInfo.numberOfVertices; index++)
	{
		sPoint newPoint;
		plyFile >> newPoint.x;
		plyFile >> newPoint.y;
		plyFile >> newPoint.z;

		meshInfo.vecVertices.push_back(newPoint);
	}

	for (unsigned int index = 0; index != meshInfo.numberOfTriangles; index++)
	{
		sTriangle newTriangle;

		int discard = 0;
		plyFile >> discard;
		plyFile >> newTriangle.vertIndex[0];
		plyFile >> newTriangle.vertIndex[1];
		plyFile >> newTriangle.vertIndex[2];

		meshInfo.vecTriangles.push_back(newTriangle);
	}


	return true;
}


struct sLine
{
	sPoint startXYZ;
	sPoint endXYZ;
};

float calcDistance(sPoint A, sPoint B)
{
	float deltaX = A.x - B.x;
	float deltaY = A.y - B.y;
	float deltaZ = A.z - B.z;

	return sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}

unsigned int getClosestPoint(sPoint testPoint, cMeshInfo& meshInfo)
{
	unsigned int closestPointIndex = 0;
	float minDist = FLT_MAX;

	for (unsigned int index = 0; index != meshInfo.vecVertices.size(); index++)
	{
		sPoint closestPointSoFar = meshInfo.vecVertices[closestPointIndex];

		float testDistance = calcDistance(testPoint, closestPointSoFar);
		if (testDistance < minDist)
		{
			closestPointIndex = index;
		}
	}

	return closestPointIndex;
}

bool generatePathList(sPoint start, sPoint target, cMeshInfo& meshInfo, std::vector<sLine>& pathList)
{
	// TODO: Amazing code
	unsigned int closeIndex = 0;
	for (unsigned int count = 0; count != 1000; count++)
	{
		closeIndex = getClosestPoint(start, meshInfo);
	}

	return true;
}

// 239, 0, 25.93537 -> 240, 0, 25.76735 
// 240, 0, 25.76735 -> 240, 1, 38.00343
//...


void DrawPathOfLines(std::vector<sLine>& pathList)
{
	for (sLine nextLine : pathList)
	{
//		DrawColouredArrowLine(nextLine.startXYZ, nextLine.endXYZ);
	}
}

int main()
{

	cMeshInfo newMesh;

	if ( ! readPlyFile("basicTerrain.ply", newMesh))
	{
		std::cout << "ERROR: Didn't read file" << std::endl;
		return -1;
	}

	// Grid is 256 x 256
	sPoint start;		start.x = 11.3f; start.y = 8.8f;
	sPoint end;			end.x = 245.1f;	end.y = 255.75f;

	std::vector<sLine> pathList;

	generatePathList(start, end, newMesh, pathList);

	DrawPathOfLines(pathList);



	return 0;
}