#include <cstdio>
const int size = 10005;
char str[size];
int count[26];
int main() {
    int limit;
    scanf("%s%d", str, &limit);
    for(int i = 0; str[i]; ++i)
        ++count[i];
    return 0;
}
