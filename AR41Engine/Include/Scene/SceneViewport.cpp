#include "SceneViewport.h"
#include "../GameObject/GameObject.h"
#include "Scene.h"

CSceneViewport::CSceneViewport()
{
}

CSceneViewport::~CSceneViewport()
{
}

void CSceneViewport::LoadComplete()
{
}

void CSceneViewport::Start()
{
	size_t	Size = m_vecWindow.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWindow[i]->Start();
	}

	// ZOrder ������ ���� �����Ѵ�.
}

bool CSceneViewport::Init()
{
	return true;
}

void CSceneViewport::Update(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CSceneViewport::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CSceneViewport::Render()
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}

void CSceneViewport::Save(FILE* File)
{
}

void CSceneViewport::Load(FILE* File)
{
}
