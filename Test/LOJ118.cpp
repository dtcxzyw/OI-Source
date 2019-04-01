#include <cstdio>
#define CXXREGEX
#ifdef CXXREGEX
#include <regex>
char pat[128], buf[128];
int main() {
    while(scanf("%s%s", pat, buf) != EOF) {
        puts(std::regex_match(
                 buf,
                 std::regex(
                     pat,
                     std::regex_constants::ECMAScript |
                         std::regex_constants::nosubs |
                         std::regex_constants::
                             optimize |
                         std::regex_constants::
                             __polynomial)) ?
                 "Yes" :
                 "No");
    }
    return 0;
}
#endif
#ifdef GLIBCREGEX
#include <regex.h>
char pat[128], buf[128];
int main() {
    while(scanf("%s%s", pat, buf) != EOF) {
        regex_t reg;
        regcomp(&reg, pat, REG_EXTENDED);
        regmatch_t p;
        puts(regexec(&reg, buf, 1, &p, 0) == 0 &&
                     p.rm_so == 0 &&
                     buf[p.rm_eo] == '\0' ?
                 "Yes" :
                 "No");
    }
    return 0;
}
#endif
