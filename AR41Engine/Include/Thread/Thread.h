#pragma once

#include "../EngineInfo.h"

class CThread
{
	friend class CThreadManager;

protected:
	CThread();
	virtual ~CThread() = 0;

protected:
	HANDLE	m_Thread;

public:
	virtual bool Init(bool Suspend);
	virtual void Run() = 0;

private:
	static unsigned int __stdcall ThreadFunction(void* Arg);

};

