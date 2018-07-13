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
int d[size],p[size],siz[size]={},son[size]={};
void buildTree(int u){
    siz[u]=1;
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(p[u]!=v){
            p[v]=u;
            d[v]=d[u]+1;
            buildTree(v);
            siz[u]+=siz[v];
            if(siz[v]>siz[son[u]])
                son[u]=v;
        }
    }
}
int id[size]={},icnt=0,mapd[size],top[size];
void buildChain(int u){
    id[u]=++icnt;
    mapd[icnt]=d[u];
    if(son[u]){
        top[son[u]]=top[u];
        buildChain(son[u]);
    }
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(!id[v]){
            top[v]=v;
            buildChain(v);
        }
    }
}
int sum[51][size]={};
long long powv[size];
void build(int n){
    for(int i=1;i<=n;++i)powv[i]=1;
    for(int i=1;i<=50;++i){
        int* S=sum[i];
        for(int j=1;j<=n;++j){
            powv[j]=powv[j]*mapd[j]%mod;
            S[j]=(S[j]+powv[j])%mod;
            int high=j+(j&-j);
            if(high<=n)S[high]=(S[high]+S[j])%mod;
        }
    }
}
int query(int x,int k){
    int res=0;
    while(x){
        res=(res+sum[k][x])%mod;
        x-=x&-x;
    }
    return res;
}
int queryRange(int l,int r,int k){
    return (query(r,k)-query(l-1,k))%mod;
}
int queryChain(int u,int v,int k){
    int res=0;
    while(top[u]!=top[v]){
        if(d[top[u]]<d[top[v]])std::swap(u,v);
        res=(res+queryRange(id[top[u]],id[u],k))%mod;
        u=p[top[u]];
    }
    if(d[u]>d[v])std::swap(u,v);
    res=(res+queryRange(id[u],id[v],k))%mod;
    return (res+mod)%mod;
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
    buildTree(1);
    top[1]=1;
    buildChain(1);
    build(n);
    int m=read();
    for(int i=0;i<m;++i){
        int u=read();
        int v=read();
        int k=read();
        printf("%d\n",queryChain(u,v,k));
    }
    return 0;
}

