cmake_minimum_required (VERSION 2.8)
project(Checker)
set (CHECKER_VERSION_MAJOR 2)
set (CHECKER_VERSION_MINOR 8)
set (CHECKER_VERSION_PATCH 1)

option(BZOJ_JUDGER "bzoj-judger" ON)
option(LOJ_JUDGER "loj-judger" ON)
option(USE_SYZOJTOOLS "syzoj-tools for loj" OFF)

add_definitions(-O2 -std=c++17 -lstdc++fs -Wall -Wextra)

set (SHAREDSRC Adapters/DefaultJudger.cpp Checker.cpp Common.cpp
Judger.cpp OJAdapter.cpp OJAPI.cpp PerfAnalyzer.cpp RunnerShared.cpp
Scanner.cpp Timer.cpp)

set (ADAPTERSRC )

if (BZOJ_JUDGER)
set (ADAPTERSRC ${ADAPTERSRC} Adapters/BZOJJudger.cpp)
endif (BZOJ_JUDGER)

if (LOJ_JUDGER)
set (ADAPTERSRC ${ADAPTERSRC} Adapters/LOJJudger.cpp)
endif (LOJ_JUDGER)

if (WIN32)
add_definitions(-D__WIN32 -DUNICODE -D_UNICODE)
set (PLATFORMSRC Platforms/PlatformWindows.cpp RunnerWindows.cpp)
elseif (UNIX)
set (PLATFORMSRC Platforms/PlatformLinux.cpp RunnerLinux.cpp)
else ()
message(FATAL_ERROR "Unsupported system")
endif (WIN32)

configure_file (
  "${PROJECT_SOURCE_DIR}/CheckerConfig.hpp.in"
  "${PROJECT_BINARY_DIR}/CheckerConfig.hpp"
)

add_executable(Checker ${SHAREDSRC} ${PLATFORMSRC} ${ADAPTERSRC})
