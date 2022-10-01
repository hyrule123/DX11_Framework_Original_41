#include "UIWidget.h"

CUIWidget::CUIWidget()  :
    m_ZOrder(0),
    m_Angle(0.f),
    m_Opacity(1.f),
    m_Start(false)
{
}

CUIWidget::CUIWidget(const CUIWidget& Widget)   :
    CRef(Widget)
{
    m_ZOrder = Widget.m_ZOrder;
}

CUIWidget::~CUIWidget()
{
}

void CUIWidget::SetShader(const std::string& Name)
{
}

void CUIWidget::Start()
{
}

bool CUIWidget::Init()
{
    return true;
}

void CUIWidget::Update(float DeltaTime)
{
}

void CUIWidget::PostUpdate(float DeltaTime)
{
}

void CUIWidget::Render()
{
}

CUIWidget* CUIWidget::Clone()
{
    return nullptr;
}

void CUIWidget::Save(FILE* File)
{
}

void CUIWidget::Load(FILE* File)
{
}
