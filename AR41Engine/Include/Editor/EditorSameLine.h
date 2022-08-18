#pragma once
#include "EditorWidget.h"
class CEditorSameLine :
    public CEditorWidget
{
	friend class CEditorWindow;

protected:
	CEditorSameLine();
	virtual ~CEditorSameLine();

private:
	// Offset�� ���� ������ ���� �������κ��� ��������� ��ġ�� ǥ���� �������� ��Ÿ����.
	float	m_OffsetX;

	// ������ �������κ��� �󸶳� ���������� �����Ѵ�.
	float	m_Spacing;

public:
	void SetOffsetX(float x)
	{
		m_OffsetX = x;
	}

	void SetSpacing(float Spacing)
	{
		m_Spacing = Spacing;
	}

public:
	virtual bool Init();
	virtual void Render();
};

