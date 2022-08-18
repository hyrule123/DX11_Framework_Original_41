
#include "TextureManager.h"
#include "Texture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Init()
{
	return true;
}

bool CTextureManager::LoadTexture(const std::string& Name, const TCHAR* FileName, 
	const std::string& PathName)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTexture(Name, FileName, PathName))
	{
		SAFE_DELETE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTextureFullPath(Name, FullPath))
	{
		SAFE_DELETE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CTextureManager::LoadTexture(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTexture(Name, vecFileName, PathName))
	{
		SAFE_DELETE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTextureFullPath(Name, vecFullPath))
	{
		SAFE_DELETE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

CTexture* CTextureManager::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

void CTextureManager::ReleaseTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter != m_mapTexture.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapTexture.erase(iter);
	}
}
