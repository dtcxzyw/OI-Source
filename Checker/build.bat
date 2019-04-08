x86_64-w64-mingw32-g++ Common.cpp  Judger.cpp OJAdapter.cpp OJAPI.cpp Timer.cpp ^
PerfAnalyzer.cpp RunnerShared.cpp Scanner.cpp Checker.cpp RunnerWindows.cpp ^
Adapters/BZOJJudger.cpp Adapters/LOJJudger.cpp Adapters/DefaultJudger.cpp ^
-o ../bin/checker.out -O2 -std=c++17 -lstdc++fs -Wall -Wextra -D__WIN32
