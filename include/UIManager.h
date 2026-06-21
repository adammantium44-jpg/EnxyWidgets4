#pragma once
#include "PrismaUI_API.h"

class UIManager {
public:
    static UIManager& Get() {
        static UIManager instance;
        return instance;
    }

    void Init();
    void Toggle();
    void HandleInput(uint32_t keyCode);

private:
    PRISMA_UI_API::IVPrismaUI1* _api = nullptr;
    PrismaView _menuView = 0;
    bool _visible = false;
};