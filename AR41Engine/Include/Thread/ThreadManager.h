#pragma once

#include "Thread.h"

class CThreadManager
{
private:
	std::unordered_map<std::string, CThread*>	m_mapThread;

public:
	bool Init();
	CThread* FindThread(const std::string& Name);

public:
	template <typename T>
	T* Create(const std::string& Name, bool Suspend = false)
	{
		T* Thread = (T*)FindThread(Name);

		if (Thread)
			return Thread;

		Thread = new T;

		if (!Thread->Init(Suspend))
		{
			SAFE_DELETE(Thread);
			return nullptr;
		}

		m_mapThread.insert(std::make_pair(Name, Thread));

		return Thread;
	}

	DECLARE_SINGLE(CThreadManager)
};

