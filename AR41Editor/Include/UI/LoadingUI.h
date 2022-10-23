#pragma once

#include "UI\UIWindow.h"

class CLoadingUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CLoadingUI();
	CLoadingUI(const CLoadingUI& Window);
	virtual ~CLoadingUI();

protected:
	CSharedPtr<class CUIImage>	m_Back;
	CSharedPtr<class CUIProgressBar>	m_LoadingBar;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLoadingUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

