#include "StartSceneUI.h"
#include "UI/UIButton.h"

CStartSceneUI::CStartSceneUI()
{
}

CStartSceneUI::CStartSceneUI(const CStartSceneUI& Window) :
    CUIWindow(Window)
{
    m_Button = FindWidget<CUIButton>("Button");
}

CStartSceneUI::~CStartSceneUI()
{
}

void CStartSceneUI::Start()
{
    CUIWindow::Start();
}

bool CStartSceneUI::Init()
{
    CUIWindow::Init();

    m_Button = CreateWidget<CUIButton>("Button");

    m_Button->SetSize(100.f, 100.f);
    m_Button->SetPos(300.f, 300.f);
    m_Button->SetTint(255, 0, 0, 255);

    m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("Start.png"));


    m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "Demasia.mp3");
    m_Button->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "TeemoSmile.mp3");

    m_Button->SetCallback<CStartSceneUI>(EButtonEventState::Hovered, this, &CStartSceneUI::ButtonCallbackHover);
    m_Button->SetCallback<CStartSceneUI>(EButtonEventState::Click, this, &CStartSceneUI::ButtonCallbackClick);

    return true;
}

void CStartSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CStartSceneUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CStartSceneUI::Render()
{
    CUIWindow::Render();
}

CStartSceneUI* CStartSceneUI::Clone()
{
    return new CStartSceneUI(*this);
}

void CStartSceneUI::Save(FILE* File)
{
}

void CStartSceneUI::Load(FILE* File)
{
}


