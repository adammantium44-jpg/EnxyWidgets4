#include "Widget.h"

#include "Ui.h"

InputHandler* InputHandler::GetSingleton() {
    static InputHandler instance;
    return &instance;
}

RE::BSEventNotifyControl InputHandler::ProcessEvent(RE::InputEvent* const* a_events,
                                                    RE::BSTEventSource<RE::InputEvent*>*) {
    if (!a_events) return RE::BSEventNotifyControl::kContinue;
    for (auto event = *a_events; event; event = event->next) {
        auto button = event->AsButtonEvent();
        if (button && button->IsDown() && button->GetDevice() == RE::INPUT_DEVICE::kKeyboard &&
            button->GetIDCode() == 0x41) {
            ToggleUI();
        }
    }
    return RE::BSEventNotifyControl::kContinue;
}