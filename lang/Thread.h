


#ifndef __Windows_lang_Thread
#define __Windows_lang_Thread


#include <windows.h>

//===========================================================
//===========================================================
DWORD WINAPI ThreadFunc(LPVOID lpvoid);
class Thread
{
    friend DWORD WINAPI ThreadFunc(LPVOID lpvoid);
private:
    int _iSuspendCount;
    
    Thread(const Thread& reference);
    Thread& operator=(const Thread& reference);
    
protected:
    HANDLE _hThread;
    static CRITICAL_SECTION cs;
    
public:
    Thread();
    virtual ~Thread();
    
    void start();
    static void sleep(int millis);
    //void wait();
    //void notify();
    //void lock();
    //void unlock();
    
    virtual void run();
};
CRITICAL_SECTION Thread::cs;
//===========================================================
//===========================================================
Thread::Thread()
{
    InitializeCriticalSection(&cs);
    _iSuspendCount = -1;
    _hThread =0;
}
Thread::~Thread(){}
void Thread::run(){}
//===========================================================
//===========================================================
void Thread::start()
{
    _hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)this, 0, NULL);
    _iSuspendCount = 0;
}

void Thread::sleep(int millis)
{
    Sleep(millis);
}

/*
void Thread::wait()
{
    if(!_iSuspendCount)      //Thread is running
    {
        SuspendThread(_hThread);
        _iSuspendCount++;
    }
}

void Thread::notify()
{
    if(_iSuspendCount >0)    //Thread is waiting
    {
        ResumeThread(_hThread);
        _iSuspendCount--;
    }
}

void Thread::lock()
{
    EnterCriticalSection(&cs);
}
void Thread::unlock()
{
    LeaveCriticalSection(&cs);
}
*/

DWORD WINAPI ThreadFunc(LPVOID lpvoid)
{
    Thread *ptThread;
    ptThread = static_cast<Thread*>(lpvoid);
    ptThread->run();
    
    CloseHandle(ptThread->_hThread);
    
    return 0;
}

//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Thread



