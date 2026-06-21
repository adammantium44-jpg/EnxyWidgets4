#include "Config.h"
#include "Logger.h"
#include "UIManager.h"
#include "HUD.h"

// Kita buat class simple di sini saja biar gak ribet
class InputHandler : public RE::BSTEventSink<RE::InputEvent*> {
public:
    static InputHandler* GetSingleton() {
        static InputHandler instance;
        return &instance;
    }

    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_events,
                                          RE::BSTEventSource<RE::InputEvent*>*) override {
        for (auto event = *a_events; event; event = event->next) {
            auto button = event->AsButtonEvent();
            if (button && button->IsDown() && button->GetDevice() == RE::INPUT_DEVICE::kKeyboard) {
                UIManager::Get().HandleInput(button->GetIDCode());
            }
        }
        return RE::BSEventNotifyControl::kContinue;
    }
};

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {

        auto api = PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>();

        UIManager::Get().Init();
        HUD::Get().Init(api);
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink(InputHandler::GetSingleton());
    }
}

// ... entry point SKSEPluginLoad ...
SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    Log::Setup("EnxyWidget4");  // Cukup panggil ini
    SKSE::Init(skse);
    // TAMBAHKAN INI UNTUK TES
    SKSE::log::info("--- SKSE PLUGIN LOADED - TES AWAL ---");
    SKSE::GetMessagingInterface()->RegisterListener(SKSEMessageHandler);
    return true;
}