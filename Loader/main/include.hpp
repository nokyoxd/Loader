#ifndef __INCLUDE_HPP__
#define __INCLUDE_HPP__

/****************************************************/ //-- includes
/* used: */
#include <iostream>

/* used: */
#include <sstream>

/* used: */
#include <fstream>

/* used: */
#include <string>

/* used: */
#include <thread>

/* used: */
#include <d3d9.h>

/* used: */
#include <Windows.h>

/* used: */
#include <dwmapi.h>

/* used: */
#include <format>

/****************************************************/ //-- File includes

/* ImGui */
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../dependencies/imgui/win32/imgui_impl_win32.h"

/* Fonts, styles */
#include "utilities/draw.h"

/*****************************************************************************************************/
inline std::string szVersion = "1.0.0";					// Version of your program
inline std::string szName = "Enforce";						// Name of your program
inline std::string szClassName = "Enforce class";			// Class name of your program
/*****************************************************************************************************/

#endif // __INCLUDE_HPP__