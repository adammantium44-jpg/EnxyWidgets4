// UIManager.cpp
#include "PCH.h"
#include "UIManager.h"
#include "Logger.h"
#include "Config.h"

void Enxytemp::UIManager::Initialize() {
    if (!PrismaUI) return;
    g_view = PrismaUI->CreateView("EnxyAbilities/setting.html");

    if (!PrismaUI->IsValid(g_view)) {
        Logger::InGameLog(">>> VIEW INVALID");
        return;
    }
    PrismaUI->Hide(g_view);
    Logger::Info("UI initialized");
}

void Enxytemp::UIManager::Toggle() {
    if (!PrismaUI || !PrismaUI->IsValid(g_view)) return;

    if (Enxytemp::Config::g_uiVisible) {
        PrismaUI->Hide(g_view);
        PrismaUI->Unfocus(g_view);
        Enxytemp::Config::g_uiVisible = false;
        Logger::InGameLog("UI HIDDEN");
    } else {
        PrismaUI->Show(g_view);
        PrismaUI->Focus(g_view, false);
        Enxytemp::Config::g_uiVisible = true;
        Logger::InGameLog("UI SHOWN");
    }
}
