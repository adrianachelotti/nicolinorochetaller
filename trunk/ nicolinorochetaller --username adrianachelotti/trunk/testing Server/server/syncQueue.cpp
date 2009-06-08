// syncQueue.cpp: implementation of the syncQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "syncQueue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

syncQueue::syncQueue()
{
	this->semaforo = CreateSemaphore(NULL, 1, 20, NULL);
	cout << "se crea el semaforo dentro de la cola" << endl;
}

//////////////////////////////////////////////////////////////////////

syncQueue::~syncQueue()
{
	CloseHandle(this->semaforo);
	cout << "se destruye el semaforo dentro de la cola" << endl;
}




///////////////////////////////////////////////////////////////////////
string syncQueue::pop(){

	string ret;
	
	DWORD dwWaitResult; 
    
	BOOL bContinue=TRUE;
	
    while(bContinue)
    {
        // Try to enter the semaphore gate.

        dwWaitResult = WaitForSingleObject( 
            semaforo,   // handle to semaphore
            0L);           // zero-second time-out interval

        switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
			// el semaforo deja pasar
			ret = this->q.front();
			this->q.pop_front();
			bContinue=FALSE;   

            // Release the semaphore when task is finished

            if (!ReleaseSemaphore( 
                    semaforo,  // handle to semaphore
                    1,            // increase count by one
                    NULL) )       // not interested in previous count
            {
                printf("ReleaseSemaphore error: %d\n", GetLastError());
            }
            break; 

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
				Sleep(100);
                break; 
        }

    }
	
    return ret;
}


///////////////////////////////////////////////////////////////////////

int syncQueue::items(){

	int ret;
		
	DWORD dwWaitResult; 
    
	BOOL bContinue=TRUE;
	
    while(bContinue)
    {
        // Try to enter the semaphore gate.

        dwWaitResult = WaitForSingleObject( 
            semaforo,   // handle to semaphore
            0L);           // zero-second time-out interval

        switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
			// el semaforo deja pasar
			ret = this->q.size();
			bContinue=FALSE;   

            // Release the semaphore when task is finished

            if (!ReleaseSemaphore( 
                    semaforo,  // handle to semaphore
                    1,            // increase count by one
                    NULL) )       // not interested in previous count
            {
                printf("ReleaseSemaphore error: %d\n", GetLastError());
            }
            break; 

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
				Sleep(100);
                break; 
        }

    }
	
    return ret;
	
}

	
	


///////////////////////////////////////////////////////////////////////


void syncQueue::push(string x){

	
	DWORD dwWaitResult; 
    
	BOOL bContinue=TRUE;
	
    while(bContinue)
    {
        // Try to enter the semaphore gate.

        dwWaitResult = WaitForSingleObject( 
            semaforo,   // handle to semaphore
            0L);           // zero-second time-out interval

        switch (dwWaitResult) 
        { 
            // The semaphore object was signaled.
            case WAIT_OBJECT_0: 
			// el semaforo deja pasar
			this->q.push_back(x);
			bContinue=FALSE;   

            // Release the semaphore when task is finished

            if (!ReleaseSemaphore( 
                    semaforo,  // handle to semaphore
                    1,            // increase count by one
                    NULL) )       // not interested in previous count
            {
                //printf("ReleaseSemaphore error: %d\n", GetLastError());
            }
            break; 

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT: 
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
				Sleep(100);
                break; 
        }

    }
	
    return;
	
}