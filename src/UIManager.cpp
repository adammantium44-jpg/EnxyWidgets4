#include "UIManager.h"

#include "Config.h"
#include "HUD.h"
#include "logger.h"  // Include header log kamu yang isi SetupLog() tadi

void UIManager::HandleInput(uint32_t keyCode) {
    if (keyCode == Config::ToggleKey) {
        logger::info("Toggle key pressed!");
        Toggle();
    }
}

void UIManager::OnSetConfig(const char* argument) {
    std::string cmd(argument);
    size_t pos = cmd.find(':');
    if (pos != std::string::npos) {
        std::string key = cmd.substr(0, pos);
        std::string val = cmd.substr(pos + 1);

        // Pakai {} karena logger::info kamu dapet support std::format dari spdlog
        logger::info("Config received: {} = {}", key, val);
    }
}

void UIManager::Init() {
    _api = PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>();
    if (!_api) {
        logger::error("PrismaUI API FAILED to initialize!");
        return;
    }

    _menuView = _api->CreateView(Config::UIRootPath);
    _api->RegisterJSListener(_menuView, "setConfig", &UIManager::OnSetConfig);
    _api->Hide(_menuView);

    logger::info("UIManager Initialized successfully.");
}

void UIManager::Toggle() {
    if (!_api || !_api->IsValid(_menuView)) return;

    _visible = !_visible;
    if (_visible) {
        logger::info("Showing Menu UI");
        _api->Show(_menuView);
        _api->Focus(_menuView, false);
    } else {
        logger::info("Hiding Menu UI");
        _api->Hide(_menuView);
        _api->Unfocus(_menuView);
    }
}