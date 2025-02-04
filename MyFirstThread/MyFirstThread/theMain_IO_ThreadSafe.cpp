#include <iostream>
#include <Windows.h>
// Gets rid of most of the bloated windows stuff
#define WIN32_LEAN_AND_MEAN

int g_totalWaitTime = 0;


DWORD WINAPI threadProc_01(LPVOID params)
{
	// int id		<-- what it is
	// (void*)&id	<-- what I passed

	int* p_id = (int*)params;
	int id = *p_id;		// Deref (make copy)

	for (int count = 0; count != 100; count++)
	{
		int waitTime = (rand() % 100) + 50;

		::g_totalWaitTime += waitTime;

		Sleep(waitTime);
		
		std::cout << "Hey! (from " << id << ")" << std::endl;
	}
	return 0;
}


int main()
{
	
	HANDLE hThread[10];
	DWORD ThreadId[10];
	int threadNumber[10];

	for (int id = 0; id < 10; id++)
	{
		threadNumber[id] = id;

		hThread[id] = CreateThread(
			NULL,				// security
			0,					// stack size
			threadProc_01,		// procedure
			(void*)&(threadNumber[id]),					// LPVOID lpParameter,
			0,					// 0, CREATE_SUSPENDED 
			&(ThreadId[id]) );	// LPDWORD lpThreadId
	}

	Sleep(5000);


	return 0;
}


