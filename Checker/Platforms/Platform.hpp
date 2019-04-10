#pragma once
#include "../Common.hpp"
#include "../Runner.hpp"
#ifdef __WIN32
#include "PlatformWindows.hpp"
#else
#include "PlatformLinux.hpp"
#endif
void initPlatform();
void platformInfo();
fs::path selfPath();
void reportJudgeError(const RunResult& res);
