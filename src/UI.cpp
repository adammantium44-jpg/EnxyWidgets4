#include "Ui.h"

#include "Config.h"
#include "PCH.h"

void InitializeUI() {
    InGameLog(">>> InitializeUI START");
    if (!PrismaUI) return;

    g_view = PrismaUI->CreateView("EnxyAbilities/setting.html");
    if (PrismaUI->IsValid(g_view)) {
        PrismaUI->Hide(g_view);
        InGameLog(">>> UI INITIALIZED");
    }
}

void ToggleUI() {
    if (!PrismaUI || !PrismaUI->IsValid(g_view)) return;
    if (g_uiVisible) {
        PrismaUI->Hide(g_view);
        PrismaUI->Unfocus(g_view);
        g_uiVisible = false;
    } else {
        PrismaUI->Show(g_view);
        PrismaUI->Focus(g_view, false);
        g_uiVisible = true;
    }
}