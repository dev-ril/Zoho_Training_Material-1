#include <iostream>
#include <windows.h>
#include <stack>

#define THREAD_SIZE 20 
#define PRODUCER_SIZE 10
#define CONSUMER_SIZE 10
#define BUFFERSIZE 5

using namespace std;

CONDITION_VARIABLE cv;
CRITICAL_SECTION cs;

stack <int> items;

DWORD WINAPI producer(LPVOID id)
{
	EnterCriticalSection(&cs);

	int product = 0;

	//Checking whether buffer is full
	while (items.size() == BUFFERSIZE)
	{
		SleepConditionVariableCS(&cv, &cs, INFINITE);
	}

	product = items.size();
	items.push(++product);

	cout << "Producer " << (int)id << " produced " << product << "\n" << endl;

	Sleep(1000);
	
	LeaveCriticalSection(&cs);
	WakeAllConditionVariable(&cv);

	return 0;
}

DWORD WINAPI consumer(LPVOID id)
{
	EnterCriticalSection(&cs);
	int product;

	//Checking whether buffer is empty
	while (items.size()==0)
	{
		SleepConditionVariableCS(&cv,&cs,INFINITE);
	}

	product = items.top();
	items.pop();

	cout << "Consumer " << (int)id << " consumed " << product << "\n" << endl;
	Sleep(1000);


	LeaveCriticalSection(&cs);
	WakeAllConditionVariable(&cv);

	return 0;
}

int main()
{
	HANDLE producers_and_consumers[THREAD_SIZE];
	DWORD threadId;

	InitializeConditionVariable (&cv);
	InitializeCriticalSection(&cs);

	int j = 0;

	cout << "PRODUCER - CONSUMER PROBLEM USING WINDOWS THREADS\n" << endl;

	//Creating producer threads
	for (int i = 0; i < PRODUCER_SIZE; i++)
	{
		producers_and_consumers[j] = CreateThread(NULL, 0, &producer, (void *)(i+1), 0, &threadId);
		if (producers_and_consumers[j] == NULL)
		{
			printf("Thread creation failed. Error: %d\n", GetLastError());
			return 1;
		}
		j++;
	}
	
	//Creating consumer threads
	for (int i = 0; i < CONSUMER_SIZE; i++)
	{
		producers_and_consumers[j] = CreateThread(NULL, 0, &consumer, (void*)(i+1), 0, &threadId);
		if (producers_and_consumers[j] == NULL)
		{
			printf("Thread creation failed. Error: %d\n", GetLastError());
			return 1;
		}
		j++;
	}

	WakeAllConditionVariable(&cv);
	
	//Waiting for all threads to complete
	WaitForMultipleObjects(THREAD_SIZE ,producers_and_consumers ,TRUE ,INFINITE);

	// Closing thread handles
	for (int i = 1; i < THREAD_SIZE; i++)
	{
		CloseHandle(producers_and_consumers[i]);
	}
	cout << "All threads closed" << endl;
	return 0;
}
