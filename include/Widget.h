#pragma once
#include "PCH.h"

class InputHandler : public RE::BSTEventSink<RE::InputEvent*> {
public:
    static InputHandler* GetSingleton();
    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_events,
                                          RE::BSTEventSource<RE::InputEvent*>*) override;
};