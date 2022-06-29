#ifndef __DRAW_H__
#define __DRAW_H__

#include "../../resources/fonts/enforce.h"

// styles
namespace D
{
    void SetupFonts();

    void Setup();
}

namespace F
{
    inline ImFont* normal;
    inline ImFont* logo;
}

#endif
