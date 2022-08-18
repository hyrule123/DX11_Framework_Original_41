
#include "EditorGUIManager.h"
#include "../Device.h"
#include "../PathManager.h"

DEFINITION_SINGLE(CEditorGUIManager)

CEditorGUIManager::CEditorGUIManager()	:
	m_Context(nullptr),
	m_Font(nullptr)
{
}

CEditorGUIManager::~CEditorGUIManager()
{
	auto	iter = m_mapWindow.begin();
	auto	iterEnd = m_mapWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool CEditorGUIManager::Init(HWND hWnd)
{
	// IMGUI Context�� �����Ѵ�.
	m_Context = ImGui::CreateContext();

	// ����� ��ü�� ���´�.
	ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(CDevice::GetInst()->GetDevice(), CDevice::GetInst()->GetContext());

	return true;
}

void CEditorGUIManager::Update(float DeltaTime)
{
	if (m_mapWindow.empty())
		return;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	// ���⿡�� IMGUI ������
	auto	iter = m_mapWindow.begin();
	auto	iterEnd = m_mapWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->Update(DeltaTime);
	}


	// ������ �׸��� �Ǹ� IMGUI ���� ������ ���ۿ� �׷��� �༮���� �� �ִ�.
	// ���� �������� �ϱ� ���� ���۸� ������ش�.
	ImGui::Render();
}

void CEditorGUIManager::Render()
{
	if (m_mapWindow.empty())
		return;

	// Rendering
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void CEditorGUIManager::SetFont(const std::string& Name, const char* FileName,
	float Size, int OverH, int OverV, float Spacing, const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	if (Path)
		strcpy_s(FullPath, Path->PathMultibyte);

	strcat_s(FullPath, FileName);

	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig	config;
	config.OversampleH = OverH;
	config.OversampleV = OverV;
	config.GlyphExtraSpacing.x = Spacing;
	config.PixelSnapH = 1;

	m_Font = io.Fonts->AddFontFromFileTTF(FullPath, Size, &config, io.Fonts->GetGlyphRangesKorean());
}

void CEditorGUIManager::EnableFont()
{
	ImGui::PushFont(m_Font);
}

void CEditorGUIManager::DisableFont()
{
	ImGui::PopFont();
}
