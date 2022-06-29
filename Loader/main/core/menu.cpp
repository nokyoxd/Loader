#include "../include.hpp"
#include "menu.h"
#include "ui.h"
#include "../utilities/draw.h"

void W::Draw()
{
	ImDrawList* pWindowDrawList = ImGui::GetWindowDrawList();
	const ImVec2 pos = ImGui::GetWindowPos();

	// Render window background
	pWindowDrawList->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + UI::iWidth, pos.y + 20), ImColor(0.0352941176470588f, 0.0352941176470588f, 0.0352941176470588f, 0.8627450980392157f), 3.5f, ImDrawCornerFlags_Top);
	pWindowDrawList->AddRectFilled(ImVec2(pos.x, pos.y + 20), ImVec2(pos.x + UI::iWidth, pos.y + UI::iHeight), ImColor(0.0352941176470588f, 0.0352941176470588f, 0.0352941176470588f, 1.f), 3.5f, ImDrawCornerFlags_Bot);

	// Render top border bar
	pWindowDrawList->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + UI::iWidth, pos.y + 20), ImColor(0.196078431372549f, 0.196078431372549f, 0.196078431372549f, 0.5882352941176471f), 3.5f, ImDrawCornerFlags_Top);

	// Render window border
	pWindowDrawList->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + UI::iWidth, pos.y + UI::iHeight), ImColor(0.f, 0.f, 0.f, 0.5882352941176471f), 3.5f, ImDrawCornerFlags_All);
	pWindowDrawList->AddRect(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + UI::iWidth - 1, pos.y + UI::iHeight - 1), ImColor(0.196078431372549f, 0.196078431372549f, 0.196078431372549f, 0.5882352941176471f), 3.5f, ImDrawCornerFlags_All);

	// Render top bar line
	pWindowDrawList->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 19), ImVec2(pos.x + UI::iWidth / 2, pos.y + 21), ImColor(0.f, 0.f, 0.f, 0.f), ImColor(0.7647058823529412f, 0.f, 0.3215686274509804f, 1.f), ImColor(0.7647058823529412f, 0.f, 0.3215686274509804f, 1.f * flAlpha[1]), ImColor(0.f, 0.f, 0.f, 0.f));
	pWindowDrawList->AddRectFilledMultiColor(ImVec2(pos.x + UI::iWidth / 2, pos.y + 19), ImVec2(pos.x + UI::iWidth, pos.y + 21), ImColor(0.7647058823529412f, 0.f, 0.3215686274509804f, 1.f), ImColor(0.f, 0.f, 0.f, 0.f), ImColor(0.f, 0.f, 0.f, 0.f), ImColor(0.7647058823529412f, 0.f, 0.3215686274509804f, 1.f * flAlpha[1]));

	// Render frames
	pWindowDrawList->AddRectFilled(ImVec2(pos.x + 10, pos.y + 28), ImVec2(pos.x + 120, pos.y + 285), ImColor(0.0470588235294118f, 0.0470588235294118f, 0.0470588235294118f, 1.f * flAlpha[1]), 1.5f, ImDrawCornerFlags_All);
	pWindowDrawList->AddRectFilled(ImVec2(pos.x + 130, pos.y + 28), ImVec2(pos.x + 430, pos.y + 285), ImColor(0.0470588235294118f, 0.0470588235294118f, 0.0470588235294118f, 1.f * flAlpha[1]), 1.5f, ImDrawCornerFlags_All);

	// Render frames border
	pWindowDrawList->AddRect(ImVec2(pos.x + 10, pos.y + 28), ImVec2(pos.x + 120, pos.y + 285), ImColor(0.196078431372549f, 0.196078431372549f, 0.196078431372549f, 0.5882352941176471f * flAlpha[1]), 1.5f, ImDrawCornerFlags_All);
	pWindowDrawList->AddRect(ImVec2(pos.x + 130, pos.y + 28), ImVec2(pos.x + 430, pos.y + 285), ImColor(0.196078431372549f, 0.196078431372549f, 0.196078431372549f, 0.5882352941176471f * flAlpha[1]), 1.5f, ImDrawCornerFlags_All);
}

void W::Render()
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ UI::iWidth, UI::iHeight });
	ImGui::Begin(szName.c_str(), &UI::bOpen, ImGuiWindowFlags_WindowFlags);
	{
		Draw();

		ImGui::PushFont(F::logo);
		ImGui::SetCursorPos(ImVec2(8, 4));
		ImGui::TextColored(ImColor(255, 255, 255, 255), ("enforce"));
		ImGui::PopFont();

		if (!bLoad)
		{
			// Tab buttons
			ImGui::SetCursorPos(ImVec2(10, 40));
			if (ImGui::Category(("CS:GO"), ImVec2(110, 30), W::iNewCurrentTab == 0, 18, 7))
				W::iNewCurrentTab = 0;

			ImGui::SetCursorPos(ImVec2(10, 70));
			if (ImGui::Category(("Settings"), ImVec2(110, 30), W::iNewCurrentTab == 1, 18, 7))
				W::iNewCurrentTab = 1;
		}

		// Animations
		ImGuiStyle& style = ImGui::GetStyle();

		// Window animation
		if (style.Alpha != 1.f)
		{
			style.Alpha = std::clamp(style.Alpha + 0.05f, 0.f, 1.f);
		}

		// Tab switch animation
		if (iNewCurrentTab != iOldCurrentTab)
		{
			if (!bClamped)
			{
				iY = std::clamp(iY + 2, 38, 60);
				flAlpha[0] = std::clamp(flAlpha[0] - 0.2f, 0.f, 1.f);
				if (iY >= 60 && flAlpha[0] <= 0.f)
				{
					bClamped = true;
				}
			}
			else if (bClamped)
			{
				iCurrentTab = iNewCurrentTab;
				iY = std::clamp(iY - 2, 38, 60);
				flAlpha[0] = std::clamp(flAlpha[0] + 0.045f, 0.f, 1.f);
				if (iY == 38 && flAlpha[0] == 1.f)
				{
					bClamped = false;
					iOldCurrentTab = iNewCurrentTab;
				}
			}
		}


		if (!bLoad)
		{
			// Tab switching
			switch (W::iCurrentTab)
			{
			case 0:
				T::CSGO();
				break;
			case 1:
				T::Settings();
				break;
			}
		}

		Load();
	}
	ImGui::End();
}

void W::Load()
{
	if (W::bTest)
	{
		bLoad = true;

		if (flAlpha[1] != 0.f)
		{
			flAlpha[1] = std::clamp(flAlpha[1] - 0.05f, 0.f, 1.f);
		}
		else
		{
			if (flAlpha[2] != 0.55f)
			{
				flAlpha[2] = std::clamp(flAlpha[2] + 0.15f, 0.f, 0.55f);
			}

			ImDrawList* pWindowDrawList = ImGui::GetWindowDrawList();
			const ImVec2 pos = ImGui::GetWindowPos();

			pWindowDrawList->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(UI::iWidth, UI::iHeight), ImColor(0.0352941176470588f, 0.0352941176470588f, 0.0352941176470588f, flAlpha[2]), 3.5f, ImDrawCornerFlags_All);

			if (flAlpha[2] == 0.55f)
			{
				ImGui::SetCursorPos(ImVec2(UI::iWidth / 2 - 12.5, UI::iHeight / 2 - 12.5));
				ImGui::Spinner(("spin##spinner"), 15.f, 3, ImColor(195, 0, 82, 255));
			}
		}
	}
}

void T::CSGO()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	ImGui::SetCursorPos(ImVec2(W::iX, W::iY));
	ImGui::BeginChild(("##main.csgo"), ImVec2(280, 237), true);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
		float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;


		static char status[100] = "> Welcome, user. \n> Days left: X. \n> User ID: 1. \n> Cheat status: Undetected.";
		ImGui::InputTextMultiline(("##status"), status, 10, ImVec2(-1, 90), ImGuiInputTextFlags_ReadOnly);
		static bool bInsecure = false;
		ImGui::SetCursorPos(ImVec2(10, 185));
		ImGui::Checkbox(("-insecure"), &bInsecure);
		if (ImGui::Button(("Load"), ImVec2(-1, 25)))
			W::bTest = !W::bTest;


		ImGui::PopStyleVar();
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
}

void T::Settings()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	ImGui::SetCursorPos(ImVec2(W::iX, W::iY));
	ImGui::BeginChild(("##main.settings"), ImVec2(280, 237), true);
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, -1));
		float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;



		ImGui::PopStyleVar();
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
}