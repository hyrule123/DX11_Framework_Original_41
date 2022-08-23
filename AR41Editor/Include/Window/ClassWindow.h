#pragma once
#include "Editor\EditorWindow.h"
class CClassWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CClassWindow();
	virtual ~CClassWindow();

private:
	class CEditorListBox* m_ObjectList;
	class CEditorListBox* m_ComponentList;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void ObjectClickCallback(int Index, const std::string& Item);
	void ComponentClickCallback(int Index, const std::string& Item);
};

