#include <cstdio>
int main() {
    for(int i = 1; i < 1000; ++i)
        for(int j = i + 1; i + j < 1000; ++j) {
            int k = 1000 - i - j;
            if(i * i + j * j == k * k) {
                printf("%d\n", i * j * k);
                break;
            }
        }
    return 0;
}
