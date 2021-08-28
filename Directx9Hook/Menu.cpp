#include "Menu.h"
#include "dx.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include "log.h"

#define FindHandleByWindowName 0

bool MenuOpen = true;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
    ImGui::CreateContext();


    ImGuiIO& io = ImGui::GetIO();


    #if FindHandleByWindowName
        window = FindWindowA(NULL, "Don't Starve");
    #else
        D3DDEVICE_CREATION_PARAMETERS CP;
        pDevice->GetCreationParameters(&CP);
       window = CP.hFocusWindow;
    #endif // 0

    if (window == NULL)
        log("Failed to get window handle")

    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);

    if(oWndProc == NULL)
        log("failed to hook wndproc")

    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    io.MouseDrawCursor = false;
    // io.ConfigFlags = ImGuiConfigFlags_NoMouse;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

void DrawMenu()
{
    //NewFrame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("[Insert] to hide menu");
    ImGui::SetWindowSize(ImVec2(180, 65));
    if (ImGui::Button("Detach",ImVec2(120,30)))
        IsRunning = false;

    ImGui::End();


    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

}
