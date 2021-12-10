#pragma once
#include "Windows.h"
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc1, hdc2;
	auto greeting = _T("Hello, Windows desktop!");
	auto testMsg = _T("WOWOWOWO!");

	switch (message)
	{
	case WM_LBUTTONDOWN:
		
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, _T("chicken"));
		}
		break;
	case WM_KEYUP:
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(69);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPreviousInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{

	//register window
	//init wcex
	WNDCLASSEX wcex = {0};

	//create class name, note _T is the long string needed for input
	static const auto pClassName = _T("hw3d");

	//default params
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	//register
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("hw3d"),
			NULL);

		return 1;
	}

	static const auto szTitle = _T("hw3d");


	// The parameters to CreateWindowEx explained:
	// WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
	// szWindowClass: the name of the application (MUST BE SAME NAME AS BEFORE)
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		pClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//win creation test
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindowEx failed!"),
			_T("hw3d"),
			NULL);

		return 1;
	}


	//display window
	//ShowWindow(hWnd, SW_SHOW);

	nCmdShow = SW_SHOW;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	//message pump
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}
