#include "FontManager.h"

CFontManager::CFontManager()    :
    m_WriteFactory(nullptr)
{
}

CFontManager::~CFontManager()
{
    {
        auto    iter = m_mapFont.begin();
        auto    iterEnd = m_mapFont.end();

        for (; iter != iterEnd; ++iter)
        {
            SAFE_RELEASE(iter->second);
        }
    }

    {
        auto    iter = m_mapFontCollection.begin();
        auto    iterEnd = m_mapFontCollection.end();

        for (; iter != iterEnd; ++iter)
        {
            SAFE_RELEASE(iter->second);
        }
    }

    {
        auto    iter = m_mapFontColor.begin();
        auto    iterEnd = m_mapFontColor.end();

        for (; iter != iterEnd; ++iter)
        {
            SAFE_RELEASE(iter->second);
        }
    }

    SAFE_RELEASE(m_WriteFactory);
}

bool CFontManager::Init()
{
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_WriteFactory),
        (IUnknown**)&m_WriteFactory)))
        return false;

    return true;
}

bool CFontManager::CreateFontCollection(const std::string& Name, const TCHAR* FileName,
    const std::string& PathName)
{
    CFontCollection* FontCollection = FindFontCollection(Name);

    if (FontCollection)
        return true;

    FontCollection = new CFontCollection;

    if (!FontCollection->CreateFontCollection(m_WriteFactory, Name, FileName, PathName))
    {
        SAFE_DELETE(FontCollection);
        return false;
    }


    m_mapFontCollection.insert(std::make_pair(Name, FontCollection));

    return true;
}

bool CFontManager::LoadFont(const std::string& Name, const TCHAR* FontName, int Weight,
    float FontSize, const TCHAR* LocalName, int Stretch)
{
    CFont* Font = FindFont(Name);

    if (Font)
        return true;

    Font = new CFont;

    if (!Font->LoadFont(m_WriteFactory, Name, FontName, Weight, FontSize, LocalName, Stretch))
    {
        SAFE_DELETE(Font);
        return false;
    }


    m_mapFont.insert(std::make_pair(Name, Font));

    return true;
}

bool CFontManager::CreateFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return false;
}

bool CFontManager::CreateFontColor(float r, float g, float b, float a)
{
    return false;
}

bool CFontManager::CreateFontColor(const Vector4& Color)
{
    return false;
}

bool CFontManager::CreateFontColor(unsigned int Color)
{
    return false;
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return nullptr;
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(float r, float g, float b, float a)
{
    return nullptr;
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(const Vector4& Color)
{
    return nullptr;
}

ID2D1SolidColorBrush* CFontManager::FindFontColor(unsigned int Color)
{
    return nullptr;
}

unsigned int CFontManager::CreateFontColorKey(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return 0;
}

unsigned int CFontManager::CreateFontColorKey(float r, float g, float b, float a)
{
    return 0;
}

unsigned int CFontManager::CreateFontColorKey(const Vector4& Color)
{
    return 0;
}

CFont* CFontManager::FindFont(const std::string& Name)
{
    auto    iter = m_mapFont.find(Name);

    if (iter == m_mapFont.end())
        return nullptr;

    return iter->second;
}

CFontCollection* CFontManager::FindFontCollection(const std::string& Name)
{
    auto    iter = m_mapFontCollection.find(Name);

    if (iter == m_mapFontCollection.end())
        return nullptr;

    return iter->second;
}
