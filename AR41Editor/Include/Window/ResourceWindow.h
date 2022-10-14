#pragma once

#include "Editor\EditorWindow.h"

class CResourceWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CResourceWindow();
	virtual ~CResourceWindow();

private:
	class CEditorListBox* m_TextureList;
	class CEditorListBox* m_SoundList;
	class CEditorListBox* m_FontList;

	class CEditorImage* m_TextureImageBox;

public:

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void LoadTextureList();
	void TextureClickCallback(int Index, const std::string& Item);
};

