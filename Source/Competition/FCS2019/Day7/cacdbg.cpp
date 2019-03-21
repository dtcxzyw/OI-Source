#include <cstdio>
#include <cstdlib>
int main() {
    freopen("data/sample-C.2.in", "r", stdin);
    freopen("G.dot", "w", stdout);
    puts("graph G{");
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d--%d;\n", u, v);
        if(i >= 100)
            break;
    }
    puts("}");
    system("dot G.dot -T png -o G.png");
    return 0;
}
