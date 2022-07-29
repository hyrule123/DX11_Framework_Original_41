#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "Scene/MainSceneInfo.h"

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
    CEngine::DestroyInst();
}

bool CClientManager::Init(HINSTANCE hInst)
{
    if (!CEngine::GetInst()->Init(hInst, TEXT("Client2D"), TEXT("Client2D"), IDI_ICON1,
        IDI_ICON1, 1280, 720, 1280, 720, true))
    {
        return false;
    }

    // SceneInfo »ý¼º
    CSceneManager::GetInst()->CreateSceneInfo<CMainSceneInfo>();

    return true;
}

int CClientManager::Run()
{
    return CEngine::GetInst()->Run();
}
