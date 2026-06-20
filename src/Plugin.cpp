// plugin.cpp
#include "PCH.h"
#include "Logger.h"
#include "UIManager.h"
#include "Config.h"

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        using namespace Enxytemp;
        UIManager::PrismaUI = static_cast<PRISMA_UI_API::IVPrismaUI1*>(
            PRISMA_UI_API::RequestPluginAPI(PRISMA_UI_API::InterfaceVersion::V1));

        if (UIManager::PrismaUI) {
            RE::BSInputDeviceManager::GetSingleton()->AddEventSink(Config::InputHandler::GetSingleton());
            UIManager::Initialize();
            Logger::Info("PrismaUI Connected");
        }
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    Enxytemp::Logger::Setup();
    SKSE::GetMessagingInterface()->RegisterListener(SKSEMessageHandler);
    return true;
}
