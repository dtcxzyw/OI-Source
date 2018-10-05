// P3375
#include <cstdio>
const int size = 1000005;
char P[size], str[size];
int nxt[size];
int cook() {
    int p = 0, i;
    nxt[1] = 0;
    for(i = 1; P[i]; ++i) {
        while(p && P[p] != P[i])
            p = nxt[p];
        if(P[p] == P[i])
            ++p;
        nxt[i + 1] = p;
    }
    return i;
}
void match(int len) {
    int p = 0;
    for(int i = 0; str[i]; ++i) {
        while(p && P[p] != str[i])
            p = nxt[p];
        if(P[p] == str[i])
            ++p;
        if(p == len)
            printf("%d\n", i - len + 2);
    }
}
int main() {
    scanf("%s%s", str, P);
    int siz = cook();
    match(siz);
    for(int i = 1; i <= siz; ++i)
        printf("%d ", nxt[i]);
    putchar('\n');
    return 0;
}
