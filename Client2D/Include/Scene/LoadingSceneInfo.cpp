#include "LoadingSceneInfo.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/LoadingUI.h"
#include "Thread/ThreadManager.h"
#include "Thread/LoadingThread.h"
#include "Thread/ThreadQueue.h"
#include "Thread/DataStream.h"

CLoadingSceneInfo::CLoadingSceneInfo()
{
}

CLoadingSceneInfo::~CLoadingSceneInfo()
{
}

bool CLoadingSceneInfo::Init()
{
	m_Owner->GetViewport()->CreateUIWindow<CLoadingUI>("LoadingUI");

    return true;
}

void CLoadingSceneInfo::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);

	// Queue�� �����Ͱ� ���� ��� �޾ƿͼ� ó���Ѵ�.
	if (!m_LoadingQueue->empty())
	{
		int	Header, Size;
		unsigned char	Data[1024] = {};

		m_LoadingQueue->pop(&Header, &Size, Data);

		CDataStream	stream;
		stream.SetBuffer(Data);
	}

	if (m_LoadingThread->IsLoadComplete())
	{
		CSceneManager::GetInst()->ChangeNextScene();
	}
}

void CLoadingSceneInfo::SceneChangeComplete()
{
	// �ε� ������ ����
	m_LoadingThread = CThreadManager::GetInst()->Create<CLoadingThread>("Loading");

	m_LoadingThread->SetLoadingSceneFileName("Main.scn");
	//m_LoadingThread->SetLoadingScenePathName(SCENE_PATH);

	m_LoadingQueue = m_LoadingThread->GetQueue();

	m_LoadingThread->Start();

	//CSceneManager::GetInst()->GetNextScene()->Load("Main");
}
