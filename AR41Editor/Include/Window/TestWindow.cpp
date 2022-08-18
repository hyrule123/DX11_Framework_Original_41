
#include "TestWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"

CTestWindow::CTestWindow()
{
}

CTestWindow::~CTestWindow()
{
}

bool CTestWindow::Init()
{
	CEditorButton* Btn = CreateWidget<CEditorButton>("버튼");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	CEditorSameLine* SameLine = CreateWidget<CEditorSameLine>("Line");

	//SameLine->SetOffsetX(100.f);
	SameLine->SetSpacing(50.f);

	Btn = CreateWidget<CEditorButton>("TestButton1");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	CEditorLabel* Label = CreateWidget<CEditorLabel>("흑마법사");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);

	SameLine = CreateWidget<CEditorSameLine>("Line");

	CEditorImage* Image = CreateWidget<CEditorImage>("Image");

	Image->SetTexture("BlackMagicion", TEXT("teemo.png"));

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
