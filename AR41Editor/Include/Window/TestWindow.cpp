
#include "TestWindow.h"
#include "Editor/EditorButton.h"

CTestWindow::CTestWindow()
{
}

CTestWindow::~CTestWindow()
{
}

bool CTestWindow::Init()
{
	CEditorButton* Btn = CreateWidget<CEditorButton>("TestButton");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	return true;
}

void CTestWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CTestWindow::TestButtonCallback()
{
	MessageBox(0, TEXT("Button"), TEXT("Button"), MB_OK);
}
