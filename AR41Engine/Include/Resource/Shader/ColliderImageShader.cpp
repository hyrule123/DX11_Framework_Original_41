#include "ColliderImageShader.h"

CColliderImageShader::CColliderImageShader()
{
}

CColliderImageShader::~CColliderImageShader()
{
}

bool CColliderImageShader::Init()
{
	if (FAILED(LoadVertexShader("ColliderImageVS", TEXT("Collider.fx"), SHADER_PATH)))
		return false;

	if (FAILED(LoadPixelShader("ColliderImagePS", TEXT("Collider.fx"), SHADER_PATH)))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
		return false;

	return true;
}
