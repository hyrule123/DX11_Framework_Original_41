
#include "Engine.h"
#include "resource.h"

#ifdef _DEBUG

#pragma comment(lib, "AR41Engine_Debug.lib")

#else

#pragma comment(lib, "AR41Engine.lib")

#endif // _DEBUG


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    if (!CEngine::GetInst()->Init(hInstance, TEXT("Client2D"), TEXT("Client2D"), IDI_ICON1,
        IDI_ICON1, 1280, 720, 1280, 720, true))
    {
        CEngine::DestroyInst();
        return 0;
    }

    int Ret = CEngine::GetInst()->Run();

    CEngine::DestroyInst();

    return Ret;
}
