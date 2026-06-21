#include "HUD.h"
#include "Logger.h"

void HUD::Init() {
    _api =
        static_cast<PRISMA_UI_API::IVPrismaUI1*>(PRISMA_UI_API::RequestPluginAPI(PRISMA_UI_API::InterfaceVersion::V1));
    if (!_api) return;

    _hudView = _api->CreateView(Config::HUDRootPath);  // Pake Config
    _api->Hide(_hudView);
    Log::Info("HUDManager: Initialized with path: " + std::string(Config::HUDRootPath));
}

void HUD::SetVisible(bool show) {
    if (!_api || !_hudView) return;
    if (show)
        _api->Show(_hudView);
    else
        _api->Hide(_hudView);
}