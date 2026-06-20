#pragma once
#include "PrismaUI_API.h"

namespace Enxytemp::UIManager {
    inline PRISMA_UI_API::IVPrismaUI1* PrismaUI = nullptr;
    inline PrismaView g_view = 0;

    void Initialize();
    void Toggle();
}
