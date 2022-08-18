#pragma once

#include "EditorInfo.h"

class CEditorWidget
{
	friend class CEditorWindow;

protected:
	CEditorWidget();
	virtual ~CEditorWidget();

protected:
	std::string		m_Name;
	class CEditorWindow* m_Owner;
	ImVec2			m_Size;
	ImColor			m_Color;

public:
	const std::string& GetName()	const
	{
		return  m_Name;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	void SetHideName(const std::string& Name)
	{
		m_Name = "##" + Name;
	}

	void SetSize(const ImVec2& Size)
	{
		m_Size = Size;
	}

	void SetSize(const Vector2& Size)
	{
		m_Size.x = Size.x;
		m_Size.y = Size.y;
	}

	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetSizeX(float x)
	{
		m_Size.x = x;
	}

	void SetSizeY(float y)
	{
		m_Size.y = y;
	}

	void SetColor(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a)
	{
		m_Color.Value.x = r / 255.f;
		m_Color.Value.y = g / 255.f;
		m_Color.Value.z = b / 255.f;
		m_Color.Value.w = a / 255.f;
	}

public:
	virtual bool Init() = 0;
	virtual void Render() = 0;
};

