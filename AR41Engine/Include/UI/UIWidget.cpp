#include "UIWidget.h"
#include "../Resource/Mesh/Mesh.h"
#include "../Resource/Shader/Shader.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Component/CameraComponent.h"
#include "../Scene/CameraManager.h"
#include "UIWindow.h"

CUIConstantBuffer* CUIWidget::m_CBuffer = nullptr;
CAnimation2DConstantBuffer* CUIWidget::m_AnimCBuffer = nullptr;

CUIWidget::CUIWidget()  :
    m_ZOrder(0),
    m_Angle(0.f),
    m_Opacity(1.f),
    m_Start(false),
    m_Tint(1.f, 1.f, 1.f, 1.f)
{
}

CUIWidget::CUIWidget(const CUIWidget& Widget)   :
    CRef(Widget)
{
    m_ZOrder = Widget.m_ZOrder;
    m_Pos = Widget.m_Pos;
    m_RenderPos = Widget.m_RenderPos;
    m_Size = Widget.m_Size;
    m_Angle = Widget.m_Angle;
    m_Opacity = Widget.m_Opacity;
    m_Mesh = Widget.m_Mesh;
    m_Shader = Widget.m_Shader;
    m_Tint = Widget.m_Tint;
    m_MeshSize = Widget.m_MeshSize;
}

CUIWidget::~CUIWidget()
{
}

void CUIWidget::SetShader(const std::string& Name)
{
    if (m_Scene)
    {
        m_Shader = m_Scene->GetResource()->FindShader(Name);
    }

    else
    {
        m_Shader = CResourceManager::GetInst()->FindShader(Name);
    }
}

void CUIWidget::SetMesh(const std::string& Name)
{
    if (m_Scene)
    {
        m_Mesh = m_Scene->GetResource()->FindMesh(Name);
    }

    else
    {
        m_Mesh = CResourceManager::GetInst()->FindMesh(Name);
    }

    Vector3 MeshSize = m_Mesh->GetMax() - m_Mesh->GetMin();

    m_MeshSize = Vector2(MeshSize.x, MeshSize.y);
}

void CUIWidget::Start()
{
}

bool CUIWidget::Init()
{
    if (m_Scene)
    {
        m_Mesh = m_Scene->GetResource()->FindMesh("LBUVRect");
        m_Shader = m_Scene->GetResource()->FindShader("UIShader");
    }

    else
    {
        m_Mesh = CResourceManager::GetInst()->FindMesh("LBUVRect");
        m_Shader = CResourceManager::GetInst()->FindShader("UIShader");
    }

    Vector3 MeshSize = m_Mesh->GetMax() - m_Mesh->GetMin();

    m_MeshSize = Vector2(MeshSize.x, MeshSize.y);

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
    // ������۸� ä���ش�.
    m_CBuffer->SetMeshSize(m_MeshSize);
    m_CBuffer->SetOpacity(m_Opacity);
    m_CBuffer->SetPivot(m_Pivot);
    m_CBuffer->SetTint(m_Tint);

    CCameraComponent* Camera = m_Scene->GetCameraManager()->GetUICamera();

    Matrix  matProj = Camera->GetProjMatrix();

    // ��µ� ��ġ������ ������ش�. m_Pos�� ������ ������ �ִ� ������κ��� ������� ��ġ
    // ������ �����ȴ�. �׷��Ƿ� ���� ��µ� ��ġ�� ��������ġ + m_Pos �� �ȴ�.
    m_RenderPos = m_Owner->GetPos() + m_Pos;

    Matrix  matScale, matRot, matTranslate;

    matScale.Scaling(m_Size);
    matRot.RotationZ(m_Angle);
    matTranslate.Translation(m_RenderPos);

    Matrix  matWorld = matScale * matRot * matTranslate;

    Matrix  matWVP = matWorld * matProj;
    
    m_CBuffer->SetWVP(matWVP);

    m_CBuffer->UpdateBuffer();

    m_AnimCBuffer->UpdateBuffer();

    m_Shader->SetShader();

    m_Mesh->Render();
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
