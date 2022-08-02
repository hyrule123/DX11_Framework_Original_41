
#include "CameraManager.h"
#include "../Component/CameraComponent.h"

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::SetCurrentCamera(CCameraComponent* Camera)
{
	m_CurrentCamera = Camera;
}

void CCameraManager::SetUICamera(CCameraComponent* Camera)
{
	m_UICamera = Camera;
}

void CCameraManager::Start()
{
}

bool CCameraManager::Init()
{
	return true;
}

void CCameraManager::Update(float DeltaTime)
{
}

void CCameraManager::PostUpdate(float DeltaTime)
{
}
