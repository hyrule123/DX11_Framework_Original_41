#include "Thread.h"

CThread::CThread()
{
}

CThread::~CThread()
{
}

bool CThread::Init(bool Suspend)
{
    m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction,
        (void*)this, 0, nullptr);

    if (Suspend)
        SuspendThread(m_Thread);

    return true;
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
    CThread* Thread = (CThread*)Arg;

    Thread->Run();

    return 0;
}
