#include <cstdio>
int main() {
    for(int i = 20;; ++i) {
        bool flag = true;
        for(int j = 1; j <= 20; ++j)
            if(i % j) {
                flag = false;
                break;
            }
        if(flag) {
            printf("%d\n", i);
            break;
        }
    }
    printf("%d\n", 16 * 9 * 5 * 7 * 11 * 13 * 17 * 19);
    return 0;
}
