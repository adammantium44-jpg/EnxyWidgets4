#include "Config.h"
#include "PCH.h"
#include "Ui.h"
#include "Widget.h"

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        PrismaUI = static_cast<PRISMA_UI_API::IVPrismaUI1*>(
            PRISMA_UI_API::RequestPluginAPI(PRISMA_UI_API::InterfaceVersion::V1));
        if (PrismaUI) {
            auto input = RE::BSInputDeviceManager::GetSingleton();
            if (input) input->AddEventSink(InputHandler::GetSingleton());
            InitializeUI();
        }
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    auto messaging = SKSE::GetMessagingInterface();
    if (messaging) messaging->RegisterListener(SKSEMessageHandler);
    return true;
}