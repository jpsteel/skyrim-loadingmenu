#include "Utility.h"

#include <Windows.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "SKSE/API.h"
#include "SKSE/Interfaces.h"

namespace logger = SKSE::log;

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", "LoadingMenuOverhaul");
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
}

void FadeOutGame(bool a_fadingOut, bool a_blackFade, float a_fadeDuration, bool a_arg4, float a_secsBeforeFade) {
    using func_t = decltype(&FadeOutGame);
    REL::Relocation<func_t> func{RELOCATION_ID(0, 52847)};
    return func(a_fadingOut, a_blackFade, a_fadeDuration, a_arg4, a_secsBeforeFade);
}

RE::BSFixedString GetLocationName(RE::BGSLocation* location) {
    RE::BSFixedString name = location->GetName();
    if (name == "") {
        if (location->parentLoc) {
            logger::info("No location name, looking for parent location");
            GetLocationName(location->parentLoc);
        }
    }
    return name;
}