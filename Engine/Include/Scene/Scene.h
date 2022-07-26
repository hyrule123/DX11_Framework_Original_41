#pragma once

#include "SceneInfo.h"
#include "SceneResource.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	bool		m_Change;
	bool		m_Start;
	CSceneInfo* m_SceneInfo;
	CSceneResource* m_Resource;

public:
	CSceneInfo* GetSceneInfo()	const
	{
		return m_SceneInfo;
	}

	CSceneResource* GetResource()	const
	{
		return m_Resource;
	}


public:
	void Start();
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);

public:
	template <typename T>
	bool CreateSceneInfo()
	{
		SAFE_DELETE(m_SceneInfo);

		m_SceneInfo = new T;

		m_SceneInfo->m_Owner = this;

		if (!m_SceneInfo->Init())
		{
			SAFE_DELETE(m_SceneInfo);
			return false;
		}

		return true;
	}
};

