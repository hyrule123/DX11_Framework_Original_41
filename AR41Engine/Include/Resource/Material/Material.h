#pragma once

#include "../../Ref.h"
#include "../Texture/Texture.h"
#include "../../Render/RenderState.h"

struct MaterialTextureInfo
{
    std::string     Name;
    ESamplerType    SamplerType;
    CSharedPtr<CTexture>  Texture;
    int             Register;
    int             ShaderBufferType;

    MaterialTextureInfo() :
        SamplerType(ESamplerType::Linear),
        Register(0),
        ShaderBufferType((int)EShaderBufferType::Pixel)
    {
    }
};

class CMaterial :
    public CRef
{
    friend class CMaterialManager;
    friend class CMesh;
    friend class CPrimitiveComponent;

protected:
    CMaterial();
    CMaterial(const CMaterial& Material);
    virtual ~CMaterial();

private:
    class CScene* m_Scene;

public:
    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

protected:
    CSharedPtr<class CShader>   m_Shader;
    std::vector<MaterialTextureInfo*>   m_vecTextureInfo;
    Vector4     m_BaseColor;
    Vector4     m_AmbientColor;
    Vector4     m_SpecularColor;
    Vector4     m_EmissiveColor;    // ��ü������ ���� �߻��ϴ� ��ü�� ���
    float       m_Opacity;          // ��������.
    class CMaterialConstantBuffer* m_CBuffer;
    CSharedPtr<CRenderState>    m_RenderState[3];

public:
    void SetBaseColor(const Vector4& Color);
    void SetBaseColor(float r, float g, float b, float a);
    void SetBaseColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a);
    void SetAmbientColor(const Vector4& Color);
    void SetAmbientColor(float r, float g, float b, float a);
    void SetAmbientColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a);
    void SetSpecularColor(const Vector4& Color);
    void SetSpecularColor(float r, float g, float b, float a);
    void SetSpecularColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a);
    void SetEmissiveColor(const Vector4& Color);
    void SetEmissiveColor(float r, float g, float b, float a);
    void SetEmissiveColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a);
    void SetOpacity(float Opacity);
    void AddOpacity(float Opacity);

    // === Texture �߰� ===
    void AddTexture(int Register, int ShaderBufferType, const std::string& Name,
        class CTexture* Texture);
    void AddTexture(int Register, int ShaderBufferType, const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void AddTextureFullPath(int Register, int ShaderBufferType,
        const std::string& Name, const TCHAR* FullPath);
    void AddTexture(int Register, int ShaderBufferType, const std::string& Name,
        const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void AddTextureFullPath(int Register, int ShaderBufferType,
        const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);

    // === �߰��Ǿ� �ִ� Texture ���� ===
    void SetTexture(int Index, int Register, int ShaderBufferType, const std::string& Name,
        class CTexture* Texture);
    void SetTexture(int Index, int Register, int ShaderBufferType, const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(int Index, int Register, int ShaderBufferType,
        const std::string& Name, const TCHAR* FullPath);
    void SetTexture(int Index, int Register, int ShaderBufferType, const std::string& Name,
        const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(int Index, int Register, int ShaderBufferType,
        const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);

    void SetTextureSamplerType(int Index, ESamplerType Type);

public:
    void SetRenderState(const std::string& Name);

public:
    void SetShader(const std::string& Name);
    void SetMaterial();
    void ResetMaterial();
    CMaterial* Clone()  const;

};
