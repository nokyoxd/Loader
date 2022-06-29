#include "../include.hpp"
#include "ui.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR     pCmdLine,
	int       nShowCmd
)
{

	// Window creation && destruction
	UI::createMain();

	return 0;
}
