#include "stdafx.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		return OnCreate(hWnd, wParam, lParam);
	case WM_CLOSE:
	case WM_DESTROY:
		return OnDestroy(hWnd, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hWnd;
	WNDCLASSEX wcex;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = "MyWindowClass";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);

	hWnd = CreateWindow("MyWindowClass", "MyWindow", WS_OVERLAPPEDWINDOW, 0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		ShowWindow(hWnd, nShowCmd);
		UpdateWindow(hWnd);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				Run(g_pd3dDevice);
		}
	}
	return 0;
}