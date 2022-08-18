
#include "Texture.h"
#include "../../PathManager.h"
#include "../../Device.h"

#ifdef _DEBUG

#pragma comment(lib, "DirectXTex_Debug.lib")

#else

#pragma comment(lib, "DirectXTex.lib")

#endif // _DEBUG

CTexture::CTexture()	:
	m_Scene(nullptr),
	m_ImageType(EImageType::Atlas)
{
	SetTypeID<CTexture>();
}

CTexture::~CTexture()
{
	size_t	Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTextureInfo[i]);
	}
}

bool CTexture::LoadTexture(const std::string& Name, const TCHAR* FileName, 
	const std::string& PathName)
{
	TCHAR	FullPath[MAX_PATH] = {};

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(Name, FullPath);
}

bool CTexture::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	SetName(Name);

	TextureResourceInfo* Info = new TextureResourceInfo;

	int	PathLength = lstrlen(FullPath);

	for (int i = PathLength - 1; i >= 0; --i)
	{
		// D:\41th\DirectX\Client\Bin\Texture\Test.png
		if ((FullPath[i] == '\\' || FullPath[i] == '/') && i >= 4)
		{
			if ((FullPath[i - 1] == 'n' || FullPath[i - 1] == 'N') &&
				(FullPath[i - 2] == 'i' || FullPath[i - 2] == 'I') &&
				(FullPath[i - 3] == 'b' || FullPath[i - 3] == 'B') &&
				(FullPath[i - 4] == '\\' || FullPath[i - 4] == '/'))
			{
				lstrcpy(Info->FileName, &FullPath[i + 1]);
				break;
			}
		}
	}

	strcpy_s(Info->PathName, strlen(ROOT_PATH) + 1, ROOT_PATH);

	// .dds, .tga, ������ ���˿� ���� �ε� �Լ��� �ٸ���.
	TCHAR	_FileExt[_MAX_EXT] = {};

	_wsplitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, _FileExt, _MAX_EXT);

	char	FileExt[_MAX_EXT] = {};

#ifdef UNICODE

	int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, FileExt, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FileExt, _FileExt);

#endif // UNICODE

	// Ȯ���ڸ� �빮�ڷ� ������ش�.
	_strupr_s(FileExt);

	DirectX::ScratchImage* Image = new DirectX::ScratchImage;

	if (strcmp(FileExt, ".DDS") == 0)
	{
		if (FAILED(DirectX::LoadFromDDSFile(FullPath, DirectX::DDS_FLAGS_NONE, nullptr,
			*Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else if (strcmp(FileExt, ".TGA") == 0)
	{
		if (FAILED(DirectX::LoadFromTGAFile(FullPath, nullptr, *Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	else
	{
		if (FAILED(DirectX::LoadFromWICFile(FullPath, DirectX::WIC_FLAGS_NONE, nullptr,
			*Image)))
		{
			SAFE_DELETE(Info);
			SAFE_DELETE(Image);
			return false;
		}
	}

	Info->Image = Image;

	m_vecTextureInfo.push_back(Info);

	return CreateResource(0);
}

bool CTexture::LoadTexture(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	std::vector<const TCHAR*>	vecFullPath;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	size_t	Size = vecFileName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		TCHAR* FullPath = new TCHAR[MAX_PATH];

		memset(FullPath, 0, sizeof(TCHAR) * MAX_PATH);

		if (Path)
			lstrcpy(FullPath, Path->Path);

		lstrcat(FullPath, vecFileName[i]);

		vecFullPath.push_back(FullPath);
	}
	
	bool Result = LoadTextureFullPath(Name, vecFullPath);

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE_ARRAY(vecFullPath[i]);
	}

	return Result;
}

bool CTexture::LoadTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	SetName(Name);

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		TextureResourceInfo* Info = new TextureResourceInfo;

		int	PathLength = lstrlen(vecFullPath[i]);

		for (int j = PathLength - 1; j >= 0; --j)
		{
			// D:\41th\DirectX\Client\Bin\Texture\Test.png
			if ((vecFullPath[i][j] == '\\' || vecFullPath[i][j] == '/') && j >= 4)
			{
				if ((vecFullPath[i][j - 1] == 'n' || vecFullPath[i][j - 1] == 'N') &&
					(vecFullPath[i][j - 2] == 'i' || vecFullPath[i][j - 2] == 'I') &&
					(vecFullPath[i][j - 3] == 'b' || vecFullPath[i][j - 3] == 'B') &&
					(vecFullPath[i][j - 4] == '\\' || vecFullPath[i][j - 4] == '/'))
				{
					lstrcpy(Info->FileName, &vecFullPath[i][j + 1]);
					break;
				}
			}
		}

		strcpy_s(Info->PathName, strlen(ROOT_PATH) + 1, ROOT_PATH);

		// .dds, .tga, ������ ���˿� ���� �ε� �Լ��� �ٸ���.
		TCHAR	_FileExt[_MAX_EXT] = {};

		_wsplitpath_s(vecFullPath[i], nullptr, 0, nullptr, 0, nullptr, 0, _FileExt, _MAX_EXT);

		char	FileExt[_MAX_EXT] = {};

#ifdef UNICODE

		int	ConvertLength = WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, nullptr, 0, nullptr, nullptr);
		WideCharToMultiByte(CP_ACP, 0, _FileExt, -1, FileExt, ConvertLength, nullptr, nullptr);

#else

		strcpy_s(FileExt, _FileExt);

#endif // UNICODE

		// Ȯ���ڸ� �빮�ڷ� ������ش�.
		_strupr_s(FileExt);

		DirectX::ScratchImage* Image = new DirectX::ScratchImage;

		if (strcmp(FileExt, ".DDS") == 0)
		{
			if (FAILED(DirectX::LoadFromDDSFile(vecFullPath[i], DirectX::DDS_FLAGS_NONE, nullptr,
				*Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else if (strcmp(FileExt, ".TGA") == 0)
		{
			if (FAILED(DirectX::LoadFromTGAFile(vecFullPath[i], nullptr, *Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		else
		{
			if (FAILED(DirectX::LoadFromWICFile(vecFullPath[i], DirectX::WIC_FLAGS_NONE, nullptr,
				*Image)))
			{
				SAFE_DELETE(Info);
				SAFE_DELETE(Image);
				return false;
			}
		}

		Info->Image = Image;

		m_vecTextureInfo.push_back(Info);

		if (!CreateResource((int)i))
			return false;
	}

	return true;
}

bool CTexture::CreateResource(int Index)
{
	if (FAILED(DirectX::CreateShaderResourceView(CDevice::GetInst()->GetDevice(),
		m_vecTextureInfo[Index]->Image->GetImages(),
		m_vecTextureInfo[Index]->Image->GetImageCount(),
		m_vecTextureInfo[Index]->Image->GetMetadata(),
		&m_vecTextureInfo[Index]->SRV)))
		return false;

	m_vecTextureInfo[Index]->Width = (unsigned int)m_vecTextureInfo[Index]->Image->GetImages()[0].width;
	m_vecTextureInfo[Index]->Height = (unsigned int)m_vecTextureInfo[Index]->Image->GetImages()[0].height;

	return true;
}

void CTexture::SetShader(int Register, int ShaderBufferType, int Index)
{
	if (m_ImageType != EImageType::Array)
	{
		if (ShaderBufferType & (int)EShaderBufferType::Vertex)
			CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);

		if (ShaderBufferType & (int)EShaderBufferType::Pixel)
			CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);

		if (ShaderBufferType & (int)EShaderBufferType::Hull)
			CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);

		if (ShaderBufferType & (int)EShaderBufferType::Domain)
			CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);

		if (ShaderBufferType & (int)EShaderBufferType::Geometry)
			CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);

		if (ShaderBufferType & (int)EShaderBufferType::Compute)
			CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &m_vecTextureInfo[Index]->SRV);
	}

	else
	{
	}
}

void CTexture::ResetShader(int Register, int ShaderBufferType, int Index)
{
	ID3D11ShaderResourceView* SRV = nullptr;

	if (ShaderBufferType & (int)EShaderBufferType::Vertex)
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &SRV);

	if (ShaderBufferType & (int)EShaderBufferType::Pixel)
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &SRV);

	if (ShaderBufferType & (int)EShaderBufferType::Hull)
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &SRV);

	if (ShaderBufferType & (int)EShaderBufferType::Domain)
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &SRV);

	if (ShaderBufferType & (int)EShaderBufferType::Geometry)
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &SRV);

	if (ShaderBufferType & (int)EShaderBufferType::Compute)
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &SRV);
}