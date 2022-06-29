#include "../include.hpp"
#include "../core/menu.h"
#include "draw.h"

void D::Setup()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(0, 0);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildRounding = 2.f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 1.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 1.f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 0.f;
	style.GrabRounding = 4.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 1.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.5f);
	style.MouseCursorScale = 0.75f;

	style.Colors[ImGuiCol_TextActive] = ImColor(255, 255, 255, 255);
	style.Colors[ImGuiCol_Text] = ImColor(200, 200, 200, 175);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.75f, 0.75f, 0.75f, 0.85f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.22f, 0.00f, 0.40f, 0.85f);

	style.Colors[ImGuiCol_WindowBg] = ImColor(9, 9, 9, 255);
	style.Colors[ImGuiCol_ChildBg] = ImColor(0.0352941176470588f, 0.0352941176470588f, 0.0352941176470588f, W::flAlpha[0]);

	style.Colors[ImGuiCol_Border] = ImColor(0.1568627450980392f, 0.1568627450980392f, 0.1568627450980392f, W::flAlpha[0]);
	style.Colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);

	style.Colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(0, 0, 0, 0);

	style.Colors[ImGuiCol_ControlBg] = ImColor(20, 20, 20, 255);
	style.Colors[ImGuiCol_ControlBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_ControlBgActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.10f);

	style.Colors[ImGuiCol_TitleBg] = ImColor(195, 0, 82, 51);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.00f, 0.40f, 0.50f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.22f, 0.00f, 0.40f, 0.20f);

	style.Colors[ImGuiCol_MenuBarBg] = ImColor(20, 20, 20, 255);

	style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(136, 0, 57);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(97, 0, 41, 255);

	style.Colors[ImGuiCol_CheckMark] = ImColor(195, 0, 82, 255);

	style.Colors[ImGuiCol_SliderGrab] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(97, 0, 41, 255);

	style.Colors[ImGuiCol_Button] = ImColor(20, 20, 20, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(50, 50, 50, 255);

	style.Colors[ImGuiCol_Header] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(40, 40, 40, 255);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(40, 40, 40, 150);

	style.Colors[ImGuiCol_Separator] = ImColor(30, 30, 30, 255);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(195, 0, 82, 255);

	style.Colors[ImGuiCol_ResizeGrip] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.70f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.22f, 0.00f, 0.40f, 1.00f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.12f, 0.80f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 0.80f);
	style.Colors[ImGuiCol_TabActive] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.30f, 0.30f, 0.30f, 0.70f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImColor(195, 0, 82, 153);

	style.Colors[ImGuiCol_PlotLines] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImColor(195, 0, 82, 127);
	style.Colors[ImGuiCol_PlotHistogram] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImColor(195, 0, 82, 127);

	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.30f, 0.20f, 0.40f, 0.80f);
	style.Colors[ImGuiCol_Triangle] = ImColor(195, 0, 82, 255);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.25f);
}

void D::SetupFonts()
{
	ImGuiIO& io = ImGui::GetIO();

	F::normal = io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Verdana.ttf"), 14, NULL, io.Fonts->GetGlyphRangesCyrillic());

	F::logo = io.Fonts->AddFontFromMemoryCompressedTTF(logofont_compressed_data, logofont_compressed_size, 12, 0, io.Fonts->GetGlyphRangesCyrillic());
}






