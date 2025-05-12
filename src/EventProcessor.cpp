#include "EventProcessor.h"
#include "Utility.h"

RE::BSEventNotifyControl EventProcessor::ProcessEvent(const RE::MenuOpenCloseEvent* event,
                                                      RE::BSTEventSource<RE::MenuOpenCloseEvent>*) {
    if (!event) {
        return RE::BSEventNotifyControl::kContinue;
    }
    
    return RE::BSEventNotifyControl::kContinue;
}

RE::BSEventNotifyControl EventProcessor::ProcessEvent(RE::InputEvent* const* eventPtr,
                                                      RE::BSTEventSource<RE::InputEvent*>*) {
    if (!eventPtr || !*eventPtr || !RE::Main::GetSingleton()->gameActive) {
        return RE::BSEventNotifyControl::kContinue;
    }

    return RE::BSEventNotifyControl::kContinue;
}

RE::BSEventNotifyControl EventProcessor::ProcessEvent(const SKSE::ModCallbackEvent* event,
                                                      RE::BSTEventSource<SKSE::ModCallbackEvent>* eventSource) {
    if (!event) {
        return RE::BSEventNotifyControl::kContinue;
    }

    if (event->eventName == "PlaySound") {
        RE::PlaySound(event->strArg.c_str());
    } 
    else if (event->eventName == "RequestLocationText") {
        RE::BSFixedString locationName = "";
        auto ui = RE::UI::GetSingleton();
        if (auto loadingMenu = ui->GetMenu<RE::LoadingMenu>()) {
            if (auto location = loadingMenu->GetRuntimeData().currentLocation) {
                logger::info("Looking for location name...");
                locationName = GetLocationName(location);
            } else {
                logger::info("No location (LCTN) found");
            }
        }

        logger::info("Location: {}", locationName.c_str());
        std::array<RE::GFxValue, 1> locInfo;
        locInfo[0] = locationName;
        if (auto menu = ui->GetMenu(RE::LoadingMenu::MENU_NAME)) {
            menu->uiMovie->Invoke("_root.Menu_mc.SetLocationText", nullptr, locInfo.data(), locInfo.size());
        }
    } 
    else if (event->eventName == "RequestUseGamepad") {
        auto ui = RE::UI::GetSingleton();
        std::array<RE::GFxValue, 1> gamepadArgs;
        int gamepad = RE::BSInputDeviceManager::GetSingleton()->IsGamepadEnabled();
        gamepadArgs[0] = gamepad;
        if (auto menu = ui->GetMenu(RE::LoadingMenu::MENU_NAME)) {
            menu->uiMovie->Invoke("_root.Menu_mc.SetButtonArt", nullptr, gamepadArgs.data(), gamepadArgs.size());
        }
    }

    return RE::BSEventNotifyControl::kContinue;
}