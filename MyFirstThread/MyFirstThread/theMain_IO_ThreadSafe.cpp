#include <iostream>
#include <Windows.h>
// Gets rid of most of the bloated windows stuff
#define WIN32_LEAN_AND_MEAN


// We want to protect this data.
// Only ONE thread at a time is using this data
int g_totalWaitTime = 0;
CRITICAL_SECTION g_CS_TotalWaitTime;


struct sData
{
	int ID;
	int totalTime = 0;
};


DWORD WINAPI threadProc_01(LPVOID params)
{
	// int id		<-- what it is
	// (void*)&id	<-- what I passed

	sData* pData = (sData*)params;

	for (int count = 0; count != 100; count++)
	{
		int waitTime = (rand() % 100) + 50;

//		std::cout << waitTime << std::endl;

		// Global total 
		//
		//EnterCriticalSection(&g_CS_TotalWaitTime);
		// 
		// Note: Returns type "BOOL" *not* type "bool" 
		// (BOOL is really an int)
		if (TryEnterCriticalSection(&g_CS_TotalWaitTime) == TRUE)
		{
			::g_totalWaitTime += waitTime;

			LeaveCriticalSection(&g_CS_TotalWaitTime);
		}
		//
		//
		

		// it's own total
		pData->totalTime += waitTime;

		Sleep(waitTime);
		
//		EnterCriticalSection(&g_CS_TotalWaitTime);
		std::cout << "Hey! (from " << pData->ID << ")" << std::endl;
//		LeaveCriticalSection(&g_CS_TotalWaitTime);
	}
	return 0;
}


int main()
{

	HANDLE hThread[10];
	DWORD ThreadId[10];
	sData paramData[10];

	// Set this up
	InitializeCriticalSection(&g_CS_TotalWaitTime);

	for (int id = 0; id < 1000; id++)
	{
		paramData[id].ID = id;
		paramData[id].totalTime = 0;

		hThread[id] = CreateThread(
			NULL,				// security
			0,					// stack size
			threadProc_01,		// procedure
			(void*)&(paramData[id]),					// LPVOID lpParameter,
			0,					// 0, CREATE_SUSPENDED 
			&(ThreadId[id]));	// LPDWORD lpThreadId
	}

	//	WaitForSingleObject(hThread[0], INFINITE);
	WaitForMultipleObjects(
		10,
		hThread,
		TRUE,
		5000);
//	MAXIMUM_WAIT_OBJECTS

	//Sleep(5000);

	//int localTotalTime = 0;
	//for (int id = 0; id < 10; id++)
	//{
	//	localTotalTime += paramData[id].totalTime;
	//}

	DeleteCriticalSection(&g_CS_TotalWaitTime);

	return 0;
}


