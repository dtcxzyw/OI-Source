#include <cstdio>
#include <algorithm>
int read(){
    int res=0,c;
    do c=getchar();
    while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}
const int size=300005,mod=998244353;
struct Edge{
    int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u];
    last[u]=cnt;
}
int d[size],p[size][20],val[size][51];
void DFS(int u){
    for(int i=1;i<20;++i)
        p[u][i]=p[p[u][i-1]][i-1];
    {
        long long powv=1;
        for(int i=1;i<=50;++i){
            powv=powv*d[u]%mod;
            val[u][i]=(val[p[u][0]][i]+powv)%mod;
        }
    }
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(p[u][0]!=v){
            p[v][0]=u;
            d[v]=d[u]+1;
            DFS(v);
        }
    }
}
int lca(int u,int v){
    if(d[u]<d[v])std::swap(u,v);
    int delta=d[u]-d[v];
    for(int i=0;i<20;++i)
        if(delta&(1<<i))
            u=p[u][i];
    for(int i=19;i>=0;--i)
        if(p[u][i]!=p[v][i])
            u=p[u][i],v=p[v][i];
    return u==v?u:p[u][0];
}
int main(){
    int n=read();
    for(int i=1;i<n;++i){
        int u=read();
        int v=read();
        addEdge(u,v);
        addEdge(v,u);
    }
    d[1]=0;
    DFS(1);
    int m=read();
    for(int i=0;i<m;++i){
        int u=read();
        int v=read();
        int fa=lca(u,v);
        int k=read();
        int res=val[u][k]+val[v][k]-val[fa][k]-val[p[fa][0]][k];
        printf("%d\n",(res%mod+mod)%mod);
    }
    return 0;
}

