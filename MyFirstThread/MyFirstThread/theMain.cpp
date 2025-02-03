#include <vector>
#include <iostream>

// https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float g_getRandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float getAverage(std::vector< float > theNums)
{
	float theTotal = 0.0f;
	for (float theNum : theNums)
	{
		theTotal += theNum;
	}

	theTotal /= (float)theNums.size();
	return theTotal;
}


int main(int argc, char* argv[])
{
	std::vector< float > theNums;

	std::cout << "Adding numbers...";

	for (unsigned int count = 0; count != 10'000'000; count++)
	{
		theNums.push_back(g_getRandomFloat(-1000.0f, 1000.0f));
	}

	std::cout << "done." << std::endl;


	float average = getAverage(theNums);

	std::cout << "The average: " << average << std::endl;


	return 0;
}