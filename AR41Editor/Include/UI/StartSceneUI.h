#pragma once
#include "UI\UIWindow.h"
class CStartSceneUI :
    public CUIWindow
{
	friend class CSceneViewport;

protected:
	CStartSceneUI();
	CStartSceneUI(const CStartSceneUI& Window);
	virtual ~CStartSceneUI();

protected:
	CSharedPtr<class CUIButton>	m_Button;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CStartSceneUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);


private:
	inline void ButtonCallbackHover();
	inline void ButtonCallbackClick();
};

void CStartSceneUI::ButtonCallbackHover()
{
	std::string str = "Button Hovered\n";
	OutputDebugStringA(str.c_str());
}

void CStartSceneUI::ButtonCallbackClick()
{
	std::string str = "Button Clicked\n";
	OutputDebugStringA(str.c_str());
}
