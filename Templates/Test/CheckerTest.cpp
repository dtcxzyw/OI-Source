#include <cstdio>
#include <vector>
int main() {
    int n;
    scanf("%d", &n);
    switch(n) {
        // AC
        case 1:
            printf("%d\n", n);
            break;
        // WA
        case 2:
            puts("Fu*k");
            break;
        // TLE
        case 3: {
            while(true)
                ;
        } break;
        // MLE 256MB
        case 4: {
            std::vector<int> A(1 << 26);
            for(int i = 0; i < A.size(); ++i)
                A[i] = i;
        } break;
        // RE Nonzero Exit Code
        case 5:
            return 82;
            break;
        // RE Segmentation Fault
        case 6: {
            int* ptr = nullptr;
            printf("%d\n", *ptr);
        } break;
        // RE Floating Point Error
        case 7:
            printf("%d\n", 10 / (n - 7));
            break;
        // RE Exception
        default:
            throw;
            break;
    }
    return 0;
}
