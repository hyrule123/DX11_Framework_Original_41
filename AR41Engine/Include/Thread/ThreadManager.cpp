#include "ThreadManager.h"

DEFINITION_SINGLE(CThreadManager)

CThreadManager::CThreadManager()
{
}

CThreadManager::~CThreadManager()
{
	auto	iter = m_mapThread.begin();
	auto	iterEnd = m_mapThread.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_mapThread.clear();
}

bool CThreadManager::Init()
{
	return true;
}

CThread* CThreadManager::FindThread(const std::string& Name)
{
	auto	iter = m_mapThread.find(Name);

	if (iter == m_mapThread.end())
		return nullptr;

	return iter->second;
}
