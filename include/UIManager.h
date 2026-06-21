#pragma once
#include "PrismaUI_API.h"

class UIManager {
public:
    // Singleton agar gampang dipanggil dari mana saja
    static UIManager& Get() {
        static UIManager instance;
        return instance;
    }

    // Fungsi-fungsi yang harus terdaftar
    void Init();
    void Toggle();
    void HandleInput(uint32_t keyCode);  // <--- Ini yang tadi error
    bool IsMenuOpen() const { return _visible; }
    static void OnSetConfig(const char* argument);

private:
    PRISMA_UI_API::IVPrismaUI1* _api = nullptr;
    PrismaView _menuView = 0;
    bool _visible = false;
};