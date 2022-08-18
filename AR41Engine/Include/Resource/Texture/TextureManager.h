#pragma once

#include "../../EngineInfo.h"

class CTextureManager
{
	friend class CResourceManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	m_mapTexture;

public:
	bool Init();
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	bool LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);
};

