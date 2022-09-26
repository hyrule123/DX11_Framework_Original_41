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
		//���������� ���ڷ� �ָ� ���Ƿ� ������ �Ұ�����.
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


