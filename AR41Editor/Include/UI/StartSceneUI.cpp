#include "StartSceneUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"

CStartSceneUI::CStartSceneUI()
{
    m_WindowTypeName = "StartSceneUI";
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

    m_Title = CreateWidget<CUIText>("Title");

    m_Title->SetSize(300.f, 100.f);
    m_Title->SetPos(200.f, 500.f);

    m_Title->SetFontSize(50.f);
    m_Title->SetText(TEXT("TEXT TEST"));
    m_Title->SetColor(255, 255, 0);
    m_Title->SetTransparency(true);
    m_Title->SetOpacity(1.f);

    m_Title->SetShadowEnable(true);
    m_Title->SetShadowOffset(5.f, 5.f);
    m_Title->SetShadowColor(255, 255, 255);
    m_Title->SetShadowTransparency(true);
    m_Title->SetShadowOpacity(1.f);

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
    CUIWindow::Save(File);
}

void CStartSceneUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_Button = FindWidget<CUIButton>("Button");
    m_Title = FindWidget<CUIText>("Title");

    m_Title->SetText(TEXT("망나니의 대모험"));
    m_Title->SetColor(255, 255, 0);
    m_Title->SetTransparency(true);
    m_Title->SetOpacity(0.8f);

    m_Title->SetShadowEnable(true);
    m_Title->SetShadowColor(128, 128, 128);
    m_Title->SetShadowTransparency(true);
    m_Title->SetShadowOpacity(0.5f);
}
