#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>
const char* const key[] = {
    "continue", "true", "decltype", "try", "if",
    "return", "typedef", "auto", "delete", "inline",
    "short", "typeid", "bool", "do", "int", "typename",
    "break", "double", "long", "long long", "sizeof",
    "union", "case", "mutable", "static", "unsigned",
    "catch", "else", "namespace", "using", "char",
    "enum", "new", "static_cast", "struct", "void",
    "nullptr", "switch", "class", "operator",
    "template", "const", "false", "private", "while",
    "float", "const_cast", "for", "public", "throw",
    "Impl", "ans", "merge", "read", "addEdge", "split",
    "size", "siz", "modify", "query", "build", "DFS",
    "dinic", "MCMF", "dp", "mod", "powm", "solve",
    "check", "col", "dfn", "low", "write", "output",
    "input", "FFT", "init", "pre", "NTT", "alloc",
    "create", "icnt", "ecnt", "ccnt", "cnt", "id",
    "find", "getRandom", "splay", "push", "update",
    "topSort", "extend", "gcd", "lucas", "inv", "fac",
    "std", "sort", "unique", "lower", "upper",
    "_bound", "root", "fa", "getLCA", "son", "len",
    "fabs", "sqrt", "vector", "map", "set", "multi",
    "priority_queue", "unordered_", "prev", "next",
    "nxt", "iterator", "freopen", "getchar", "scanf",
    "printf", "string", "push_back", "pop_back",
    "insert", "erase", "count", "clear", "reserve",
    "stream", "arr", "top", "psiz", "gauss", "queue",
    "cstdio", "cstring", "cmath", "climits", "cstdlib",
    "algorithm", "cctype", "MST", "bid", "begin",
    "end", "Node", "val", "src", "sum", "delta", "sub",
    "memcpy", "memset", "scan", "last", "cur", "bit",
    "dst", "move", "calc", "swap", "exgcd",
    "convexHull", "Vec", "Line", "cross", "dot",
    "length", "area", "HPI", "dir", "ori", "tmp",
    "Circle", "dis", "#include", "#define", "angle",
    "[i]", "%mod", "phi", "pos", "aug", "intersect",
    "random_shuffle", "next_permutation",
    "nth_element", "push_heap", "pop_heap", "Yes",
    "No", "No Solution", "maxv", "minv", "?:", "equal",
    "inf", "eps", "reset", "pair", "first", "second",
    "time", "clock", "eval", "heap", "hash", "LUT",
    "clone", "old", "link", "Mat", "asInt64", "foo",
    "Int64", "mulm", "main", "point", "SSSP", "color",
    "clamp", "rotate", "access", "down", "simplex",
    "pivot", "gen", "makeRoot", "isRoot", "test",
    "slope", "fail", "match", "divide", "info", "BFS",
    "IterT", "DFT", "IDFT", "buildChain", "buildTree",
    "copy", "rev", "Seq", "timeStamp", "getPos", "cut",
    "lca", "pushDown", "#ifdef", "#endif", "rebuild",
    "strtod", "buf", "ctime", "inplace_merge"
                              ""
};
constexpr int size = std::extent<decltype(key)>::value,
              cnt = 10, fac = 273;
int id[size];
using Clock = std::chrono::high_resolution_clock;
int main() {
    std::random_device dev;
    for(int i = 0; i < size; ++i)
        id[i] = i;
    std::shuffle(id, id + size, dev);
    int count = 0;
    auto beg = Clock::now();
    std::cout.precision(0);
    for(int i = 0; i < size; i += cnt) {
        int end = std::min(size, i + cnt);
        std::string str;
        for(int j = i; j < end; ++j) {
            str += key[id[j]];
            str.push_back(' ');
        }
        str.pop_back();
        auto limit = 1000000LL * str.size() * fac;
        Clock::duration t;
        while(true) {
            std::cout << "P " << str << std::endl
                      << "A ";
            auto beg = Clock::now();
            std::string input;
            std::getline(std::cin, input);
            count += input.size();
            t = Clock::now() - beg;
            if(input == str && t.count() <= limit)
                break;
            std::cout << (input != str ? "WA" : "TLE")
                      << std::endl;
        }
        auto mt = t.count() * 1e-9 / 60;
        std::cout << "group " << i / cnt << " ("
                  << std::fixed << (100.0 * end / size)
                  << "%) " << (str.size() / mt)
                  << " char/min" << std::endl;
        {
            auto t = (Clock::now() - beg).count() *
                1e-9 / 60;
            std::cout << std::fixed << (count / t)
                      << " char/min" << std::endl;
        }
    }
    while(true)
        ;
    return 0;
}
