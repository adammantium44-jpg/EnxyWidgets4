#include "Config.h"
#include "HUD.h"
#include "UIManager.h"
#include "Logger.h"  // Pakai lowercase sesuai nama file headermu yang isi SetupLog()

// Global variable untuk menyimpan alamat fungsi vanilla asli (untuk kebutuhan Hook)
static uintptr_t g_VanillaFuncPtr = 0;

// ==========================================
// 1. INPUT HANDLER (BSTEventSink)
// ==========================================
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

// ==========================================
// 2. LOW-LEVEL HOOK (Stealer Hook)
// ==========================================
static void hk_StealerHook(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent** a_events) {
    // Memanggil fungsi original vanilla di rantai eksekusi
    auto OriginalFunc = (decltype(hk_StealerHook)*)g_VanillaFuncPtr;
    return OriginalFunc(a_dispatcher, a_events);
}

// Fungsi yang diekspor agar plugin lain (Blocker) bisa meminta pointer vanilla asli
extern "C" __declspec(dllexport) uintptr_t GetVanillaFunctionPointer() { return g_VanillaFuncPtr; }

// ==========================================
// 3. SKSE MESSAGE HANDLER
// ==========================================
static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        auto api = PRISMA_UI_API::RequestPluginAPI<PRISMA_UI_API::IVPrismaUI1>();

        UIManager::Get().Init();
        HUD::Get().Init(api);

        // Daftarkan input handler ke device manager Skyrim
        RE::BSInputDeviceManager::GetSingleton()->AddEventSink(InputHandler::GetSingleton());
        logger::info("InputHandler Event Sink successfully registered.");
    }

    if (message->type == SKSE::MessagingInterface::kNewGame ||
        message->type == SKSE::MessagingInterface::kPostLoadGame) {
        // Post-load logic bisa ditaruh di sini jika dibutuhkan
        logger::info("Game loaded / New Game started.");
    }
}

// ==========================================
// 4. MAIN ENTRY POINT (SKSEPlugin_Load)
// ==========================================
bool SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    // 1. Wajib inisialisasi SKSE paling pertama agar internal logger bekerja!
    SKSE::Init(skse);

    // 2. Setup file log EnxyWidget4
    SetupLog();
    logger::info("--- ENXYWIDGET4 PLUGIN LOADED ---");

    // 3. Alokasikan trampoline untuk menulis hook (5 bytes untuk panggilan dekat)
    SKSE::AllocTrampoline(14);

    // Lokasi Address: BSInputDeviceManager::PollInputDevices
    REL::RelocationID hookLocation(67315, 68617);
    uintptr_t hookAddress = hookLocation.address() + REL::Relocate(0x7B, 0x7B, 0x81);

    // Pasang hook ke trampoline, simpan fungsi asli ke g_VanillaFuncPtr
    auto& trampoline = SKSE::GetTrampoline();
    g_VanillaFuncPtr = trampoline.write_call<5>(hookAddress, hk_StealerHook);
    logger::info("Trampoline hook successfully installed.");

    // 4. Daftarkan Listener Message SKSE
    SKSE::GetMessagingInterface()->RegisterListener(SKSEMessageHandler);

    return true;
}