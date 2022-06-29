#include "../include.hpp"
#include "ui.h"
#include "menu.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (UI::device && wideParameter != SIZE_MINIMIZED)
		{
			UI::presentParameters.BackBufferWidth = LOWORD(longParameter);
			UI::presentParameters.BackBufferHeight = HIWORD(longParameter);
			UI::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		// Disable ALT application menu
		if ((wideParameter & 0xfff0) == SC_KEYMENU)
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		// Set click points
		UI::position = MAKEPOINTS(longParameter); 
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(UI::window, &rect);

			rect.left += points.x - UI::position.x;
			rect.top += points.y - UI::position.y;

			if (UI::position.x >= 0 &&
				UI::position.x <= UI::iWidth &&
				UI::position.y >= 0 && UI::position.y <= 19)
				SetWindowPos(
					UI::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void UI::createMain() noexcept
{
	// hWindow, Device, ImGui creation
	CreateHWindow(szName.c_str(), szClassName.c_str());
	CreateDevice();
	CreateImGui();

	// Reset Alpha for animation
	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 0.f;

	while (bOpen)
	{
		// Load custom style preset
		D::Setup();

		BeginRender();
		W::Render();
		EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// ImGui, Device, hWindow destruction
	DestroyImGui();
	DestroyDevice();
	DestroyHWindow();
}

bool UI::CreateHWindow(const char* szWindowName, const char* szClassName) noexcept
{
	// Get screen x, y size and calculate algorithm
	int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 2 - iWidth / 2;
	int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2 - iHeight / 2;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = szClassName;
	windowClass.hIconSm = 0;

	// Register class
	RegisterClassEx(&windowClass);

	// Create window
	window = CreateWindow(
		windowClass.lpszClassName,
		szWindowName,
		WS_POPUP,
		dwWidth,
		dwHeight,
		iWidth,
		iHeight,
		0,
		0,
		windowClass.hInstance,
		0
	);

	// Add margin to window
	MARGINS margins = { -1 };
	DwmExtendFrameIntoClientArea(window, &margins);

	// Show window and update it
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);

	return true;
}

void UI::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool UI::CreateDevice() noexcept
{
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d9)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void UI::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void UI::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d9)
	{
		d3d9->Release();
		d3d9 = nullptr;
	}
}

bool UI::CreateImGui() noexcept
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = NULL;

	// Load default style preset
	ImGui::StyleColorsDark();
	// Setup fonts from ttfs
	D::SetupFonts();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	return true;
}

void UI::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void UI::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			bOpen = !bOpen;
			return;
		}
	}

	// Start the ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void UI::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}