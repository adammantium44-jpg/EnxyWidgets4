// Config.h
#pragma once
#include "PCH.h"

namespace Enxytemp::Config {
    inline bool g_uiVisible = false;
    inline uint32_t hotkey = 0x40; // F6

    class InputHandler : public RE::BSTEventSink<RE::InputEvent*> {
    public:
        static InputHandler* GetSingleton();
        RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_events, RE::BSTEventSource<RE::InputEvent*>*) override;
    };
}
