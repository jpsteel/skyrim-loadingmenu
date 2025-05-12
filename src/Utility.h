#ifndef UTILITY_H
#define UTILITY_H

namespace logger = SKSE::log;

void SetupLog();
void FadeOutGame(bool a_fadingOut, bool a_blackFade, float a_fadeDuration, bool a_arg4, float a_secsBeforeFade);
RE::BSFixedString GetLocationName(RE::BGSLocation* location);

#endif  // UTILITY_H