#pragma once
#include "EditorWidget.h"
class CEditorLabel :
    public CEditorWidget
{
	friend class CEditorWindow;

protected:
	CEditorLabel();
	virtual ~CEditorLabel();

private:
	ImVec2	m_Align;

public:
	void SetAlign(float x, float y)
	{
		m_Align.x = x;
		m_Align.y = y;
	}

public:
	virtual bool Init();
	virtual void Render();
};

