#pragma once

#include "Editor\EditorWindow.h"

class CAnimation2DWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CAnimation2DWindow();
	virtual ~CAnimation2DWindow();

private:
	class CEditorListBox* m_Animation2DClassList;
	class CEditorListBox* m_Animation2DSequenceList;

public:

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void LoadAnimation2DClassList();
	void LoadAnimation2DSequenceList();
};

