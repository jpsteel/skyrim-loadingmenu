#ifndef EVENT_PROCESSOR_H
#define EVENT_PROCESSOR_H

#include <unordered_map>

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

class EventProcessor : public RE::BSTEventSink<RE::InputEvent*>, public RE::BSTEventSink<RE::MenuOpenCloseEvent>, public RE::BSTEventSink<SKSE::ModCallbackEvent> {
public:
    static EventProcessor* GetSingleton() {
        static EventProcessor instance;
        return &instance;
    }

    RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* eventPtr,
                                          RE::BSTEventSource<RE::InputEvent*>*) override;
    RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event,
                                          RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;
    RE::BSEventNotifyControl ProcessEvent(const SKSE::ModCallbackEvent* event,
                                          RE::BSTEventSource<SKSE::ModCallbackEvent>* eventSource) override;
};

#endif  // EVENT_PROCESSOR_H