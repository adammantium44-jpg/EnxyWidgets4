#include "Config.h"  
#include "Ui.h"

void InitializeHooking() {  
    // Logika hooking Anda jika ada  
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {  
    Enxy::InitializeLogging();  
      
    auto messaging = SKSE::GetMessagingInterface();  
    messaging->RegisterListener([](SKSE::MessagingInterface::Message* message) {  
        if (message->type == SKSE::MessagingInterface::kDataLoaded) {  
            Enxy::UI::Initialize();  
            InitializeHooking();  
        }  
    });

    return true;  
}  