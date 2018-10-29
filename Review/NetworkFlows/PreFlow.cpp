int d[size], id[size], in[size], out[size];
bool cmp(int a, int b) {
    return d[a] < d[b];
}
void preFlow(int n, int s, int t) {
    for(int i = 1; i <= n; ++i)
        id[i] = i;
    std::sort(id + 1, id + n + 1, cmp);
    in[s] = inf;
    for(int i = 1; i <= n; ++i) {
        int u = id[i];
        for(int j = last[u]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(d[v] == d[u] + 1) {
                int f =
                    std::min(in[u] - out[u], E[i].f);
                in[v] += f, out[u] += f;
            }
        }
    }
    memset(in + 1, 0, sizeof(int) * n);
    in[f] = inf;
    for(int i = n; i >= 1; --i) {
        int u = id[i];
        for(int j = last[u]; j; j = E[j].nxt) {
            int v = E[j].to;
            if(d[v] + 1 == d[u]) {
                int f = std::min(
                    std::min(out[v] - in[v], in[u]),
                    E[j ^ 1].f);
                in[v] += f, in[u] -= f;
                E[j].f += f, E[j ^ 1].f -= f;
            }
        }
    }
}
