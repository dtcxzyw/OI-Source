// CF126B
#include <cstdio>
const int size = 1000005;
char P[size];
int Z[size];
int main() {
    scanf("%s", P);
    int i = 1, L = 0, R = 0;
    while(P[i]) {
        if(i > R) {
            L = R = i;
            while(P[R - L] == P[R])
                ++R;
            Z[i] = R - L;
            --R;
        } else {
            if(Z[i - L] < R - i + 1)
                Z[i] = Z[i - L];
            else {
                L = i;
                while(P[R - L] == P[R])
                    ++R;
                Z[i] = R - L;
                --R;
            }
        }
        ++i;
    }
    int siz = i, maxz = 0;
    for(int i = 1; i < siz; ++i) {
        int len = siz - i;
        if(Z[i] == len && maxz >= len) {
            puts(P + i);
            return 0;
        }
        if(Z[i] > maxz)
            maxz = Z[i];
    }
    puts("Just a legend");
    return 0;
}
