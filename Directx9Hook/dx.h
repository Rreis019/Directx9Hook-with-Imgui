#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

typedef HRESULT(APIENTRY* tEndScene) (LPDIRECT3DDEVICE9 pDevice);

extern HWND window;

bool GetDevice(void** pTable, size_t size);
void GetWindowSize(int& WindowWidth, int& WindowHeight);
HWND GetProcessWindow();
extern LPDIRECT3DDEVICE9 pDevice;
