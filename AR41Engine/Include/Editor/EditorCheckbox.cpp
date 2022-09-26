#include "EditorCheckbox.h"

CEditorCheckbox::CEditorCheckbox():
	m_ReadOnly(),
	m_Checked(),
	m_CheckCallbackFunc()
{
}

CEditorCheckbox::~CEditorCheckbox()
{
}

bool CEditorCheckbox::Init()
{
	//CEditorWidget::Init();

	return true;
}

void CEditorCheckbox::Render()
{
	bool PrevCheck = m_Checked;
	if (m_ReadOnly)
	{
		//지역변수를 인자로 주면 임의로 변경이 불가능함.
		ImGui::Checkbox(m_NameUTF8.c_str(), &PrevCheck);
	}
	else
	{
		ImGui::Checkbox(m_NameUTF8.c_str(), &m_Checked);
	}
	

	if (!m_ReadOnly && (m_Checked != PrevCheck))
	{
		if (m_CheckCallbackFunc)
			m_CheckCallbackFunc(m_Checked);
	}
}


