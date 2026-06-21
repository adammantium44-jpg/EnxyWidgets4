#pragma once
#include "Config.h"
#include "PrismaUI_API.h"

class HUD {
public:
    static HUD& Get() {
        static HUD instance;
        return instance;
    }
    void Init();
    void SetVisible(bool show);

private:
    PRISMA_UI_API::IVPrismaUI1* _api = nullptr;
    PrismaView _hudView = 0;
};