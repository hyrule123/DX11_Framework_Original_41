#pragma once

#include "Editor\EditorWindow.h"

struct AnimFrameInfo
{
	class CEditorInput* StartX;
	class CEditorSameLine* SameLine1;
	class CEditorInput* StartY;
	class CEditorSameLine* SameLine2;
	class CEditorInput* EndX;
	class CEditorSameLine* SameLine3;
	class CEditorInput* EndY;
};

class CDetailWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CDetailWindow();
	virtual ~CDetailWindow();

protected:
	std::vector<class CEditorWidget*>	m_vecSceneComponent;
	std::vector<class CEditorWidget*>	m_vecSpriteComponent;
	std::vector<class CEditorWidget*>	m_vecCameraComponent;
	std::vector<class CEditorWidget*>	m_vecTargetArmComponent;
	std::vector<class CEditorWidget*>	m_vecAnimComponent;
	CSharedPtr<class CSceneComponent> m_SelectComponent;

	std::vector<AnimFrameInfo> m_AnimFrameInfo;

public:
	void SetSelectComponent(class CSceneComponent* Component);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateSceneComponentWidget();
	void CreateSpriteComponentWidget();
	void CreateCameraComponentWidget();
	void CreateTargetArmComponentWidget();
	void ChangeWidget(class CSceneComponent* Component);

private:
	void LoadButtonClick();
	void SetAnimation(bool& B);
	void LoadAnimation(class CSceneComponent* Component);
};

