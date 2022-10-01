#include "UIButton.h"

CUIButton::CUIButton()
{
}

CUIButton::CUIButton(const CUIButton& Button)   :
    CUIWidget(Button)
{
}

CUIButton::~CUIButton()
{
}

void CUIButton::Start()
{
}

bool CUIButton::Init()
{
    return false;
}

void CUIButton::Update(float DeltaTime)
{
}

void CUIButton::PostUpdate(float DeltaTime)
{
}

void CUIButton::Render()
{
}

CUIButton* CUIButton::Clone()
{
    return nullptr;
}

void CUIButton::Save(FILE* File)
{
}

void CUIButton::Load(FILE* File)
{
}
