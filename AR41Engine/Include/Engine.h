#pragma once

#include "EngineInfo.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_WindowRS;
	float		m_ClearColor[4];
	static bool	m_Loop;
	class CTimer* m_Timer;
	static bool		m_EditorMode;
	static std::function<bool(HWND, UINT, WPARAM, LPARAM)>	m_WndProcFunc;

public:
	static bool GetEditorMode()
	{
		return m_EditorMode;
	}

	static void EnableEditor()
	{
		m_EditorMode = true;
	}

	Resolution GetWindowResolution()	const
	{
		return m_WindowRS;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Title,
		const TCHAR* ClassName, int IconID, int SmallIconID,
		unsigned int WindowWidth,
		unsigned int WindowHeight, 
		unsigned int DeviceWidth, unsigned int DeviceHeight,
		bool WindowMode = true, int MenuID = 0);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);


private:
	void Register(const TCHAR* ClassName, int IconID, int SmallIconID, int MenuID);
	bool Create(const TCHAR* Title, const TCHAR* ClassName);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	template <typename T>
	static void SetWndProcCallback(T* Obj, bool(T::* Func)(HWND, UINT, WPARAM, LPARAM))
	{
		m_WndProcFunc = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4);
	}

	DECLARE_SINGLE(CEngine)
};

