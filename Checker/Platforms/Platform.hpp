#pragma once
#include "../Common.hpp"
#ifdef __WIN32
#include "PlatformWindows.hpp"
#endif
void initPlatform();
void platformInfo();
fs::path selfPath();
