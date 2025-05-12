#include <spdlog/sinks/basic_file_sink.h>

#include "Utility.h"
#include "EventProcessor.h"

void SKSEMessageHandler(SKSE::MessagingInterface::Message* message) {
    auto eventProcessor = EventProcessor::GetSingleton();
    switch (message->type) {
        case (SKSE::MessagingInterface::kDataLoaded):
            RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(eventProcessor);
            break;
        case (SKSE::MessagingInterface::kInputLoaded):
            RE::BSInputDeviceManager::GetSingleton()->AddEventSink<RE::InputEvent*>(eventProcessor);
            SKSE::GetModCallbackEventSource()->AddEventSink(eventProcessor);
            break;
        case SKSE::MessagingInterface::kPostLoadGame:
        case SKSE::MessagingInterface::kPostLoad:
        case SKSE::MessagingInterface::kNewGame:
        case SKSE::MessagingInterface::kSaveGame:
        default: 
            break;
    }
}

extern "C" [[maybe_unused]] __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    SetupLog();
    spdlog::set_level(spdlog::level::debug);

    SKSE::GetMessagingInterface()->RegisterListener(SKSEMessageHandler);

    logger::info("Loading Menu successfully loaded.");

    return true;
}