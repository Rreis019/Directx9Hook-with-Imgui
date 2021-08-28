// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include "dx.h"
#include "hook.h"
#include "log.h"
#include "Drawings.h"
#include "Menu.h"

#include "..\ImGui\imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx9.h"

//data
void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene;
extern LPDIRECT3DDEVICE9 pDevice = NULL;

WNDPROC oWndProc;

bool IsRunning = true;
//fonts
ID3DXFont* pfont = nullptr;

void AddFonts()
{
    D3DXCreateFont(pDevice, 30, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Tahoma", &pfont);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    if (uMsg == WM_KEYUP && wParam == VK_INSERT)
        MenuOpen = !MenuOpen;

    if (MenuOpen)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        
        //Block Input game(mouse left)
        switch (uMsg) {

        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
            return 1L;
        }
    }
       
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}




void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
    if (!pDevice)
    {
        pDevice = o_pDevice;
        D3DXCreateLine(pDevice, &m_Line);
        InitImGui(pDevice);
        AddFonts();
        log("Directx9 Started\n")
    }

    if(MenuOpen)
        DrawMenu();

    DrawFilledRectangle(20, 20, 40, 40, 255, 255, 255, 255);
    DrawBorderBox(70, 20, 40, 40, 2, 255, 255, 255, 255);
    DrawString((char*)"ola", 20, 60, 255, 0, 0, pfont, false, false);
    DrawLine(120, 20, 120 + 40, 60, 2, D3DCOLOR_ARGB(255, 255, 0, 0));


   oEndScene(o_pDevice);
}

DWORD WINAPI MainThread(HMODULE hmodule)
{
    //Abre console tiver debug mode
#if !NDEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
#endif
    log("Debug Mode\n")

    //Hook directx
    if (GetDevice(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    }else { log("Failed to hook Directx9\n") }


    while (IsRunning)
    {
        if (GetAsyncKeyState(VK_END))
            IsRunning = false;
        Sleep(50);
    }


    //Unhook
    Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
    SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)oWndProc);


    //Release
    m_Line->Release();

    //Destroy Imgui
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    //Destroy Console
    #if !NDEBUG
        fclose(f);
        FreeConsole();
    #endif

    //Uninject
    FreeLibraryAndExitThread(hmodule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
        return true;
    }
}

