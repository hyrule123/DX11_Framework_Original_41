
#include "Material.h"
#include "../ResourceManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../Shader/MaterialConstantBuffer.h"
#include "../Shader/Shader.h"
#include "../../Render/RenderManager.h"

CMaterial::CMaterial()	:
	m_BaseColor(Vector4::White),
	m_AmbientColor(0.2f, 0.2f, 0.2f, 1.f),
	m_SpecularColor(Vector4::White),
	m_EmissiveColor(Vector4::Black),
	m_Opacity(1.f)
{
	SetTypeID<CMaterial>();

	m_CBuffer = new CMaterialConstantBuffer;

	m_CBuffer->Init();

	m_CBuffer->SetBaseColor(m_BaseColor);
	m_CBuffer->SetAmbientColor(m_AmbientColor);
	m_CBuffer->SetSpecularColor(m_SpecularColor);
	m_CBuffer->SetEmissiveColor(m_EmissiveColor);
	m_CBuffer->SetOpacity(m_Opacity);
}

CMaterial::CMaterial(const CMaterial& Material)	:
	CRef(Material)
{
	m_Shader = Material.m_Shader;
	m_BaseColor = Material.m_BaseColor;
	m_AmbientColor = Material.m_AmbientColor;
	m_SpecularColor = Material.m_SpecularColor;
	m_EmissiveColor = Material.m_EmissiveColor;
	m_Opacity = Material.m_Opacity;

	m_CBuffer = Material.m_CBuffer->Clone();

	auto	iter = Material.m_vecTextureInfo.begin();
	auto	iterEnd = Material.m_vecTextureInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		MaterialTextureInfo* Info = new MaterialTextureInfo;

		Info->Name = (*iter)->Name;
		Info->SamplerType = (*iter)->SamplerType;
		Info->Texture = (*iter)->Texture;
		Info->Register = (*iter)->Register;
		Info->ShaderBufferType = (*iter)->ShaderBufferType;

		m_vecTextureInfo.push_back(Info);
	}

	m_Scene = nullptr;
}

CMaterial::~CMaterial()
{
	auto	iter = m_vecTextureInfo.begin();
	auto	iterEnd = m_vecTextureInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	SAFE_DELETE(m_CBuffer);
}

void CMaterial::SetBaseColor(const Vector4& Color)
{
	m_BaseColor = Color;

	m_CBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetBaseColor(float r, float g, float b, float a)
{
	m_BaseColor = Vector4(r, g, b, a);

	m_CBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetBaseColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_BaseColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_CBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetAmbientColor(const Vector4& Color)
{
	m_AmbientColor = Color;

	m_CBuffer->SetAmbientColor(m_AmbientColor);
}

void CMaterial::SetAmbientColor(float r, float g, float b, float a)
{
	m_AmbientColor = Vector4(r, g, b, a);

	m_CBuffer->SetAmbientColor(m_AmbientColor);
}

void CMaterial::SetAmbientColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_AmbientColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_CBuffer->SetAmbientColor(m_AmbientColor);
}

void CMaterial::SetSpecularColor(const Vector4& Color)
{
	m_SpecularColor = Color;

	m_CBuffer->SetSpecularColor(m_SpecularColor);
}

void CMaterial::SetSpecularColor(float r, float g, float b, float a)
{
	m_SpecularColor = Vector4(r, g, b, a);

	m_CBuffer->SetSpecularColor(m_SpecularColor);
}

void CMaterial::SetSpecularColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_SpecularColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_CBuffer->SetSpecularColor(m_SpecularColor);
}

void CMaterial::SetEmissiveColor(const Vector4& Color)
{
	m_EmissiveColor = Color;

	m_CBuffer->SetEmissiveColor(m_EmissiveColor);
}

void CMaterial::SetEmissiveColor(float r, float g, float b, float a)
{
	m_EmissiveColor = Vector4(r, g, b, a);

	m_CBuffer->SetEmissiveColor(m_EmissiveColor);
}

void CMaterial::SetEmissiveColorUnsignedChar(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_EmissiveColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_CBuffer->SetEmissiveColor(m_EmissiveColor);
}

void CMaterial::SetOpacity(float Opacity)
{
	m_Opacity = Opacity;

	m_CBuffer->SetOpacity(m_Opacity);
}

void CMaterial::AddOpacity(float Opacity)
{
	m_Opacity += Opacity;

	m_CBuffer->SetOpacity(m_Opacity);
}

void CMaterial::AddTexture(int Register, int ShaderBufferType, 
	const std::string& Name, CTexture* Texture)
{
	MaterialTextureInfo* Info = new MaterialTextureInfo;

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;
	Info->Texture = Texture;

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::AddTexture(int Register, int ShaderBufferType, 
	const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	MaterialTextureInfo* Info = new MaterialTextureInfo;

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::AddTextureFullPath(int Register, int ShaderBufferType, 
	const std::string& Name, const TCHAR* FullPath)
{
	MaterialTextureInfo* Info = new MaterialTextureInfo;

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureFullPath(Name, FullPath))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::AddTexture(int Register, int ShaderBufferType, 
	const std::string& Name, const std::vector<const TCHAR*>& vecFileName, 
	const std::string& PathName)
{
	MaterialTextureInfo* Info = new MaterialTextureInfo;

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, vecFileName, PathName))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::AddTextureFullPath(int Register, int ShaderBufferType, 
	const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	MaterialTextureInfo* Info = new MaterialTextureInfo;

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureFullPath(Name, vecFullPath))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::SetTexture(int Index, int Register, int ShaderBufferType,
	const std::string& Name, CTexture* Texture)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;
	Info->Texture = Texture;
}

void CMaterial::SetTexture(int Index, int Register, int ShaderBufferType, 
	const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::SetTextureFullPath(int Index, int Register, int ShaderBufferType, const std::string& Name, const TCHAR* FullPath)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureFullPath(Name, FullPath))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::SetTexture(int Index, int Register, int ShaderBufferType, 
	const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
	const std::string& PathName)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, vecFileName, PathName))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::SetTextureFullPath(int Index, int Register, 
	int ShaderBufferType, const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->Register = Register;
	Info->ShaderBufferType = ShaderBufferType;
	Info->Name = Name;

	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTextureFullPath(Name, vecFullPath))
			return;

		Info->Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
			return;

		Info->Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	m_vecTextureInfo.push_back(Info);
}

void CMaterial::SetTextureSamplerType(int Index, ESamplerType Type)
{
	if (Index < 0 || Index >= (int)m_vecTextureInfo.size())
		return;

	MaterialTextureInfo* Info = m_vecTextureInfo[Index];

	Info->SamplerType = Type;
}

void CMaterial::SetRenderState(const std::string& Name)
{
	CRenderState* RenderState = CRenderManager::GetInst()->FindRenderState<CRenderState>(Name);

	if (!RenderState)
		return;

	m_RenderState[(int)RenderState->GetType()] = RenderState;
}

void CMaterial::SetShader(const std::string& Name)
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

void CMaterial::SetMaterial()
{
	if (m_Shader)
		m_Shader->SetShader();

	for (int i = 0; i < 3; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->SetState();
	}

	m_CBuffer->UpdateBuffer();

	size_t	Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTextureInfo[i]->Texture->SetShader(m_vecTextureInfo[i]->Register,
			m_vecTextureInfo[i]->ShaderBufferType, 0);
	}
}

void CMaterial::ResetMaterial()
{
	for (int i = 0; i < 3; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->ResetState();
	}

	size_t	Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTextureInfo[i]->Texture->ResetShader(m_vecTextureInfo[i]->Register,
			m_vecTextureInfo[i]->ShaderBufferType);
	}
}

CMaterial* CMaterial::Clone() const
{
	return new CMaterial(*this);
}