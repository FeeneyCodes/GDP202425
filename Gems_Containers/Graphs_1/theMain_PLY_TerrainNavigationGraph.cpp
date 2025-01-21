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



int main()
{

	cMeshInfo newMesh;

	if ( ! readPlyFile("basicTerrain.ply", newMesh))
	{
		std::cout << "ERROR: Didn't read file" << std::endl;
		return -1;
	}



	



	return 0;
}