#ifndef __MENU_H__
#define __MENU_H__

namespace W
{
	void Load();
	void Draw();
	void Render();

	inline bool bStart = true;
	inline bool bRun = false;
	inline int iCurrentTab = 0;
	inline int iOldCurrentTab = 0;
	inline int iNewCurrentTab = 0;

	inline bool bClamped = false;
	inline int iY = 38, iX = 140;

	inline float flAlpha[3] = { 1.f, 1.f, 0.f };

	inline bool bTest = false;
	inline bool bLoad = false;
}

namespace T
{
	void CSGO();
	void Settings();
}

#endif 

