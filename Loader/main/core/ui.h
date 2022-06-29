#ifndef __UI_H__
#define __UI_H__

namespace UI
{
	// Exit bool
	inline bool bOpen = true;

	// Window size
	const int iWidth = 440;
	const int iHeight = 295;

	// Winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	// Points for window movement
	inline POINTS position = { };

	// DirectX state vars
	inline PDIRECT3D9 d3d9 = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	// Window, Device, ImGui creation & destruction
	void createMain() noexcept;

	// Window creation & destruction
	bool CreateHWindow(const char* szWindowName, const char* szClassName) noexcept;
	void DestroyHWindow() noexcept;

	// Device creation & destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// ImGui creation & destruction
	bool CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
}

#endif