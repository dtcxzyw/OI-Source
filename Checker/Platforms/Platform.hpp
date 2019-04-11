#pragma once
#include "../Common.hpp"
#include "../Runner.hpp"
#ifdef __WIN32
#include "Windows/PlatformWindows.hpp"
#else
#include "Linux/PerfAnalyzer.hpp"
#include "Linux/PlatformLinux.hpp"
#endif
void initPlatform();
void platformInfo();
void reportJudgeError(const RunResult& res);
int getConsoleWidth();
