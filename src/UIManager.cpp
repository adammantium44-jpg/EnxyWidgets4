#include "UIManager.h"
#include "HUD.h" // Jangan lupa include ini
#include "Config.h"
#include "Logger.h"


void UIManager::HandleInput(uint32_t keyCode) {
    if (keyCode == Config::ToggleKey) {
        Toggle();
    }
}

// ... sisanya fungsi Init() dan Toggle() yang tadi ...

void UIManager::Init() {
    _api = PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>();
    if (!_api) {
        Log::Error("PrismaUI API Failed");
        return;
    }

    _menuView = _api->CreateView(Config::UIRootPath);
    _api->Hide(_menuView);

    // KUNCI: RegisterJSListener untuk menangkap pesan dari JS
    _api->RegisterJSListener(_menuView, "toggleHUD", [](const char* argument) {
        std::string arg(argument);
        // Kalau JS kirim "true", maka show. Kalau "false", maka hide.
        HUD::Get().SetVisible(arg == "true");
    });

    Log::Info("UI Initialized & Listener Registered");
}

void UIManager::Toggle() {
    if (!_api || !_api->IsValid(_menuView)) return;

    _visible = !_visible;
    if (_visible) {
        _api->Show(_menuView);
        _api->Focus(_menuView, false);
    } else {
        _api->Hide(_menuView);
        _api->Unfocus(_menuView);
    }
}