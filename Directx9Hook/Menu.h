#pragma once
#include <d3d9.h>

#define KEY_OPENMENU VK_INSERT
#define FindHandleByWindowName 0
#define WindowName "Don't Starve"

extern bool MenuOpen;
extern bool IsRunning;

extern WNDPROC oWndProc;
extern LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitImGui(LPDIRECT3DDEVICE9 pDevice);
void DrawMenu();
