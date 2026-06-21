#include "HUD.h"
#include "Logger.h"

void HUD::Init(PRISMA_UI_API::IVPrismaUI1* api) {
    _api = api;  // Pakai API yang sudah ada
    if (!_api) return;

    _hudView = _api->CreateView(Config::HUDRootPath);
    _api->Hide(_hudView);
}

void HUD::SetVisible(bool show) {
    if (!_api || !_hudView) return;
    if (show)
        _api->Show(_hudView);
    else
        _api->Hide(_hudView);
}