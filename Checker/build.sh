#!/bin/bash
g++ Common.cpp DefaultJudger.cpp Judger.cpp OJAdapter.cpp \
PerfAnalyzer.cpp Runner.cpp Scanner.cpp Checker.cpp LOJJudger.cpp \
-o ../bin/checker.out -O0 -std=c++17 -lstdc++fs -Wall -Wextra
