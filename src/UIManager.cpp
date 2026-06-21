#include "UIManager.h"

#include "Config.h"
#include "HUD.h"
#include "Logger.h"

// Fungsi statis ini yang bakal dipanggil oleh PrismaUI
void UIManager::OnToggleHUD(const char* argument) {
    std::string arg(argument);
    HUD::Get().SetVisible(arg == "true");
}

void UIManager::Init() {
    _api = PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>();
    if (!_api) {
        Log::Error("PrismaUI API Failed");
        return;
    }

    _menuView = _api->CreateView(Config::UIRootPath);
    _api->Hide(_menuView);

    // Sekarang pakai pointer fungsi statis, tanpa [this]
    _api->RegisterJSListener(_menuView, "toggleHUD", &UIManager::OnToggleHUD);

    Log::Info("UI Initialized & Listener Registered");
}

void UIManager::HandleInput(uint32_t keyCode) {
    if (keyCode == Config::ToggleKey) {
        Toggle();
    }
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