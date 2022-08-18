#pragma once

#include "Editor.h"

class CEditorManager
{
public:
	CEditorManager();
	~CEditorManager();

public:
	bool Init(HINSTANCE hInst);
	int Run();
};

