#include "Window.h"

#include <string>

Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{

	case WM_CREATE:

		//Event fired when the window will be created
		window->onCreate();
		break;

	case WM_DESTROY:

		//Event fired when the window is destroyed
		window->onDestroy();
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
}
bool Window::init()
{
	//Const Lib
	//const wchar_t* MyWindowClass = (wchar_t*)"MyWindowClass";
	//const wchar_t* empty = (wchar_t*)"";
	//const wchar_t* appName = (wchar_t*)"DirectX Application";


	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = LPCWSTR("MyWindowClass");
	wc.lpszMenuName = LPCWSTR("");
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;


	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;

	if (!window)
		window = this;

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, LPCWSTR("MyWindowClass"), LPCWSTR("DirectX Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	//show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	

	//set this flag to true indicate that the window is  initialized an running 

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	window->onUpdate();

	Sleep(0);

	return true;
}

bool Window::release()
{
	//Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{
}
