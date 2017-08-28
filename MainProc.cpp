#include "stdafx.h"

int OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	InitVB();
	return 0;
}
int OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);

	return 0;
}