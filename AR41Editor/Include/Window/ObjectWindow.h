#pragma once

#include "Editor\EditorWindow.h"
#include "Editor/EditorTree.h"
#include "GameObject/GameObject.h"

class CObjectWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CObjectWindow();
	virtual ~CObjectWindow();

private:
	CEditorTree<CGameObject*>* m_Tree;

public:
	void AddItem(class CGameObject* Object, const std::string& Name, const std::string& ParentName = "Root");

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void TreeCallback(CEditorTreeItem<CGameObject*>* Node, const std::string& Item);
};

