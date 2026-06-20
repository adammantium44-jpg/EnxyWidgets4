#include "Config.h"

#include "PCH.h"

PRISMA_UI_API::IVPrismaUI1* PrismaUI = nullptr;
bool g_uiVisible = false;
PrismaView g_view = 0;

void InGameLog(const char* msg) {
    if (RE::ConsoleLog::GetSingleton()) {
        RE::ConsoleLog::GetSingleton()->Print(msg);
    }
}