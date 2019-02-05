#include <cstdio>
const int size = 1000000;
bool flag[size + 5];
bool check(int x) {
    for(int i = 1; 2 * i * i <= x; ++i) {
        int val = x - 2 * i * i;
        if(!flag[val])
            return true;
    }
    return false;
}
int main() {
    flag[0] = flag[1] = true;
    for(int i = 2; i < size; ++i)
        if(!flag[i])
            for(int j = i * 2; j < size; j += i)
                flag[j] = true;
    for(int i = 3; i < size; i += 2)
        if(flag[i] && !check(i)) {
            printf("%d\n", i);
            break;
        }
    return 0;
}
