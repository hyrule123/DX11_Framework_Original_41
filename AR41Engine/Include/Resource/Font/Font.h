#pragma once

#include "../../Ref.h"

class CFont :
    public CRef
{
    friend class CFontManager;

private:
    CFont();
    ~CFont();

private:
    IDWriteTextFormat* m_Format;

public:
    bool LoadFont(IDWriteFactory5* WriteFactory, const std::string& Name, const TCHAR* FontName,
        int Weight, float FontSize, const TCHAR* LocalName, int Stretch);
};

