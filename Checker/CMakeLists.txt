cmake_minimum_required (VERSION 2.8)
project(Checker)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" HAS_CXX17)
if(NOT HAS_CXX17)
message(FATAL_ERROR "Unsupported c++ complier")
endif(NOT HAS_CXX17)

find_program(HAS_WGET wget)

if(NOT HAS_WGET)
message(FATAL_ERROR "No wget")
endif(NOT HAS_WGET)

find_program(HAS_UNZIP unzip)

if(NOT HAS_UNZIP)
message(FATAL_ERROR "No unzip")
endif(NOT HAS_UNZIP)

set (CHECKER_VERSION_MAJOR 2)
set (CHECKER_VERSION_MINOR 8)
set (CHECKER_VERSION_PATCH 2)
set (CHECKER_SRC_DIR "${PROJECT_SOURCE_DIR}")

option(BZOJ_JUDGER "bzoj-judger" ON)
option(LOJ_JUDGER "loj-judger" ON)
option(USE_SYZOJTOOLS "syzoj-tools for loj" OFF)

configure_file (
  "${PROJECT_SOURCE_DIR}/CheckerConfig.hpp.in"
  "${PROJECT_BINARY_DIR}/CheckerConfig.hpp"
)

include_directories(${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-O2 -std=c++17 -Wall -Wextra ${CMAKE_CXX_FLAGS}")
if (WIN32)
set(CMAKE_CXX_FLAGS "-D__WIN32 -DUNICODE -D_UNICODE ${CMAKE_CXX_FLAGS}")
aux_source_directory(Platforms/Windows PlatformSrc)
elseif (UNIX)
aux_source_directory(Platforms/Linux PlatformSrc)
else ()
message(FATAL_ERROR "Unsupported system")
endif (WIN32)

set (JudgerSrc Adapters/DefaultJudger.cpp)
if(BZOJ_JUDGER)
set (JudgerSrc ${JudgerSrc} Adapters/BZOJJudger.cpp)
endif(BZOJ_JUDGER)

if(LOJ_JUDGER)
set (JudgerSrc ${JudgerSrc} Adapters/LOJJudger.cpp)
endif(LOJ_JUDGER)

set (SharedSrc Checker.cpp Common.cpp Judger.cpp OJAdapter.cpp OJAPI.cpp 
RunnerShared.cpp Scanner.cpp Timer.cpp)

link_libraries(stdc++fs)
add_executable(Checker ${SharedSrc} ${JudgerSrc} ${PlatformSrc})
