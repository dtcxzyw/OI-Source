#include <cstdio>
const int size = 10000000;
bool flag[size + 5];
int main() {
    flag[1] = true;
    int pd[] = { 2, 3, 5, 7, 11, 13 };
    for(auto x : pd)
        for(int i = x + x; i <= size; i += x)
            flag[i] = true;
    int cnt = 0;
    for(int i = 1; i <= size; ++i)
        cnt += flag[i];
    printf("%lf\n", static_cast<double>(cnt) / size);
    return 0;
}
