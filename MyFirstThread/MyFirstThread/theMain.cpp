#include <vector>
#include <iostream>
#include <Windows.h>	// for CreateThread
#include <process.h>	// for _beginthreadex

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

// Function we call has to be in a specific format:
// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms686736(v=vs.85)
DWORD WINAPI getAverageThreadProc(LPVOID lpParameter)
{
	std::cout << "Hello from the thread!" << std::endl;
	// TODO: Amazing code here
	return 0;
}

int main(int argc, char* argv[])
{
	std::vector< float > theNums;

	std::cout << "Adding numbers to vector...";

	for (unsigned int count = 0; count != 10'000'000; count++)
	{
		theNums.push_back(g_getRandomFloat(-1000.0f, 1000.0f));
	}

	std::cout << "done." << std::endl;

	std::cout << "Getting average...";

//	float average = getAverage(theNums);
	float average = 0.0f;

	DWORD threadId = 0;

	HANDLE hThread = CreateThread(
		NULL,	// If lpThreadAttributes is NULL, the thread gets a default security descriptor.
		0,		// If this parameter is zero, the new thread uses the default size
//		getAverage, <-- Not allowed. Must be a certain signature
		getAverageThreadProc, // pointer to the application-defined function to be executed by the thread.
		NULL,	// LPVOID lpParameter,
		0,		// 0 = start right away (or CREATE_SUSPENDED) 
		&threadId);		// LPDWORD lpThreadId

	// Start up the thread now...
//	ResumeThread(hThread);		// if we CreateThread() as CREATE_SUSPENDED

	std::cout << "done." << std::endl;
	std::cout << "The average: " << average << std::endl;


	return 0;
}