#include "UIProgressBar.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Sound/Sound.h"
#include "../Input.h"

CUIProgressBar::CUIProgressBar()    :
    m_Min(0.f),
    m_Max(1.f),
    m_Value(0.5f),
    m_BarDir(EProgressBarDir::RightToLeft)
{
    m_WidgetTypeName = "UIProgressBar";
}

CUIProgressBar::CUIProgressBar(const CUIProgressBar& ProgressBar) :
    CUIWidget(ProgressBar)
{
    for (int i = 0; i < (int)EProgressBarTextureType::Max; ++i)
    {
        m_TextureInfo[i] = ProgressBar.m_TextureInfo[i];
    }

    m_Min = ProgressBar.m_Min;
    m_Max = ProgressBar.m_Max;
    m_Value = ProgressBar.m_Value;
    m_BarDir = ProgressBar.m_BarDir;
}

CUIProgressBar::~CUIProgressBar()
{
}

void CUIProgressBar::SetTexture(EProgressBarTextureType Type, CTexture* Texture)
{
    m_TextureInfo[(int)Type].Texture = Texture;
}

bool CUIProgressBar::SetTexture(EProgressBarTextureType Type, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
    if (m_Scene)
    {
        if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
            return false;

        m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(Name);
    }

    else
    {
        if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
            return false;

        m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(Name);
    }

    return true;
}

bool CUIProgressBar::SetTextureFullPath(EProgressBarTextureType Type, const std::string& Name, const TCHAR* FullPath)
{
    if (m_Scene)
    {
        if (!m_Scene->GetResource()->LoadTextureFullPath(Name, FullPath))
            return false;

        m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(Name);
    }

    else
    {
        if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
            return false;

        m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(Name);
    }

    return true;
}

bool CUIProgressBar::SetTexture(EProgressBarTextureType Type, const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
    const std::string& PathName)
{
    if (m_Scene)
    {
        if (!m_Scene->GetResource()->LoadTexture(Name, vecFileName, PathName))
            return false;

        m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(Name);
    }

    else
    {
        if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
            return false;

        m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(Name);
    }

    return true;
}

bool CUIProgressBar::SetTextureFullPath(EProgressBarTextureType Type, const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
    if (m_Scene)
    {
        if (!m_Scene->GetResource()->LoadTextureFullPath(Name, vecFullPath))
            return false;

        m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(Name);
    }

    else
    {
        if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
            return false;

        m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(Name);
    }

    return true;
}

void CUIProgressBar::SetImageTint(EProgressBarTextureType Type, const Vector4& Tint)
{
    m_TextureInfo[(int)Type].Tint = Tint;
}

void CUIProgressBar::SetImageTint(EProgressBarTextureType Type, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    m_TextureInfo[(int)Type].Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CUIProgressBar::AddFrameData(EProgressBarTextureType Type, const Vector2& Start, const Vector2& End)
{
    Animation2DFrameData    Frame;
    Frame.Start = Start;
    Frame.End = End;

    m_TextureInfo[(int)Type].vecFrameData.push_back(Frame);

    m_TextureInfo[(int)Type].FrameTime = m_TextureInfo[(int)Type].vecFrameData.size() / m_TextureInfo[(int)Type].PlayTime;
}

void CUIProgressBar::SetPlayTime(EProgressBarTextureType Type, float PlayTime)
{
    m_TextureInfo[(int)Type].PlayTime = PlayTime;

    m_TextureInfo[(int)Type].FrameTime = m_TextureInfo[(int)Type].vecFrameData.size() / m_TextureInfo[(int)Type].PlayTime;
}

void CUIProgressBar::SetPlayScale(EProgressBarTextureType Type, float PlayScale)
{
    m_TextureInfo[(int)Type].PlayScale = PlayScale;
}

void CUIProgressBar::SetProgressBarMin(float Min)
{
    m_Min = Min;
}

void CUIProgressBar::SetProgressBarMax(float Max)
{
    m_Max = Max;
}

void CUIProgressBar::SetValue(float Value)
{
    m_Value = Value;

    if (m_Value < m_Min)
        m_Value = m_Min;

    else if (m_Value > m_Max)
        m_Value = m_Max;
}

void CUIProgressBar::AddValue(float Value)
{
    m_Value += Value;

    if (m_Value < m_Min)
        m_Value = m_Min;

    else if (m_Value > m_Max)
        m_Value = m_Max;
}

void CUIProgressBar::Start()
{
    CUIWidget::Start();
}

bool CUIProgressBar::Init()
{
    if (!CUIWidget::Init())
        return false;

    return true;
}

void CUIProgressBar::Update(float DeltaTime)
{
    CUIWidget::Update(DeltaTime);

    for (int i = 0; i < (int)EProgressBarTextureType::Max; ++i)
    {
        if (!m_TextureInfo[i].vecFrameData.empty())
        {
            m_TextureInfo[i].Time += DeltaTime;

            if (m_TextureInfo[i].Time >= m_TextureInfo[i].FrameTime)
            {
                m_TextureInfo[i].Time -= m_TextureInfo[i].FrameTime;

                ++m_TextureInfo[i].Frame;

                if (m_TextureInfo[i].Frame == m_TextureInfo[i].vecFrameData.size())
                    m_TextureInfo[i].Frame = 0;
            }
        }
    }


}

void CUIProgressBar::PostUpdate(float DeltaTime)
{
    CUIWidget::PostUpdate(DeltaTime);
}

void CUIProgressBar::Render()
{
    // 상수버퍼를 채워준다.
    bool TextureEnable = m_TextureInfo[(int)EProgressBarTextureType::Back].Texture ? true : false;

    m_CBuffer->SetTextureEnable(TextureEnable);

    if (TextureEnable)
    {
        int TextureFrame = 0;

        if (m_TextureInfo[(int)EProgressBarTextureType::Back].Texture->GetImageType() == EImageType::Frame)
            TextureFrame = m_TextureInfo[(int)EProgressBarTextureType::Back].Frame;

        m_TextureInfo[(int)EProgressBarTextureType::Back].Texture->SetShader(0, (int)EShaderBufferType::Pixel, TextureFrame);
    }

    m_Tint = m_TextureInfo[(int)EProgressBarTextureType::Back].Tint;

    CUIWidget::Render();
}

CUIProgressBar* CUIProgressBar::Clone()
{
    return new CUIProgressBar(*this);
}

void CUIProgressBar::Save(FILE* File)
{
    CUIWidget::Save(File);

    for (int Type = (int)EProgressBarTextureType::Back; Type < (int)EProgressBarTextureType::Max; ++Type)
    {
        fwrite(&m_TextureInfo[(int)Type].Tint, sizeof(Vector4), 1, File);

        fwrite(&m_TextureInfo[(int)Type].FrameTime, sizeof(float), 1, File);
        fwrite(&m_TextureInfo[(int)Type].PlayTime, sizeof(float), 1, File);
        fwrite(&m_TextureInfo[(int)Type].PlayScale, sizeof(float), 1, File);

        int FrameCount = (int)m_TextureInfo[(int)Type].vecFrameData.size();
        fwrite(&FrameCount, sizeof(int), 1, File);

        if (FrameCount > 0)
            fwrite(&m_TextureInfo[(int)Type].vecFrameData[0], sizeof(Animation2DFrameData), FrameCount, File);

        m_TextureInfo[(int)Type].Texture->Save(File);
    }
}

void CUIProgressBar::Load(FILE* File)
{
    CUIWidget::Load(File);

    for (int Type = (int)EProgressBarTextureType::Back; Type < (int)EProgressBarTextureType::Max; ++Type)
    {
        fread(&m_TextureInfo[(int)Type].Tint, sizeof(Vector4), 1, File);

        fread(&m_TextureInfo[(int)Type].FrameTime, sizeof(float), 1, File);
        fread(&m_TextureInfo[(int)Type].PlayTime, sizeof(float), 1, File);
        fread(&m_TextureInfo[(int)Type].PlayScale, sizeof(float), 1, File);

        int FrameCount = 0;
        fread(&FrameCount, sizeof(int), 1, File);

        m_TextureInfo[(int)Type].vecFrameData.resize((size_t)FrameCount);

        if (FrameCount > 0)
            fread(&m_TextureInfo[(int)Type].vecFrameData[0], sizeof(Animation2DFrameData), FrameCount, File);

        char    TexName[256] = {};

        int Length = 0;

        fread(&Length, sizeof(int), 1, File);
        fread(TexName, 1, Length, File);

        int	TextureSRVCount = 0;

        fread(&TextureSRVCount, sizeof(int), 1, File);

        if (TextureSRVCount == 1)
        {
            TCHAR	FileName[MAX_PATH] = {};
            char	PathName[MAX_PATH] = {};

            fread(FileName, sizeof(TCHAR), MAX_PATH, File);
            fread(PathName, sizeof(char), MAX_PATH, File);

            if (m_Scene)
            {
                m_Scene->GetResource()->LoadTexture(TexName, FileName, PathName);

                m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(TexName);
            }

            else
            {
                CResourceManager::GetInst()->LoadTexture(TexName, FileName, PathName);

                m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(TexName);
            }
        }

        else
        {
            std::vector<const TCHAR*>	vecFileName;
            std::string	ResultPathName;

            for (int i = 0; i < TextureSRVCount; ++i)
            {
                TCHAR* FileName = new TCHAR[MAX_PATH];
                char	PathName[MAX_PATH] = {};

                fread(FileName, sizeof(TCHAR), MAX_PATH, File);
                fread(PathName, sizeof(char), MAX_PATH, File);

                ResultPathName = PathName;

                vecFileName.push_back(FileName);
            }

            if (m_Scene)
            {
                m_Scene->GetResource()->LoadTexture(TexName, vecFileName, ResultPathName);

                m_TextureInfo[(int)Type].Texture = m_Scene->GetResource()->FindTexture(TexName);
            }

            else
            {
                CResourceManager::GetInst()->LoadTexture(TexName, vecFileName, ResultPathName);

                m_TextureInfo[(int)Type].Texture = CResourceManager::GetInst()->FindTexture(TexName);
            }

            for (int i = 0; i < TextureSRVCount; ++i)
            {
                SAFE_DELETE_ARRAY(vecFileName[i]);
            }
        }
    }


}


