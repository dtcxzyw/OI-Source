#include <cstdio>
#include <algorithm>
int read(){
    int res=0,c;
    bool flag=false;
    do{ 
        c=getchar();
        flag|=c=='-';
    }while(c<'0'||c>'9');
    while('0'<=c&&c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return flag?-res:res;
}
const int size=100005;
struct Edge{
    int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
    ++cnt;
    E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
    last[u]=cnt;
}
int tot,csiz,crt,siz[size],st[size<<1][19],id[size],len[size],scnt=0;
void DFS(int u,int p,int dis){
    st[++scnt][0]=len[u]=dis;
    id[u]=scnt;
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(p!=v){
            DFS(v,u,dis+E[i].w);
            st[++scnt][0]=dis;
        }
    }
}
int lg[size<<1];
void buildST(){
    DFS(1,0,0);
    lg[1]=0;
    for(int i=2;i<=scnt;++i)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=18;++i){
        int end=scnt-(1<<i)+1,off=1<<(i-1);
        for(int j=1;j<=end;++j)
            st[j][i]=std::min(st[j][i-1],st[j+off][i-1]);
    }
}
int dis(int u,int v){
    int l=id[u],r=id[v];
    if(l>r)std::swap(l,r);
    int k=lg[r-l+1];
    return len[u]+len[v]-(std::min(st[l][k],st[r-(1<<k)+1][k])<<1);
}
bool vis[size]={};
int getRoot(int u,int p){
    int maxs=0;
    siz[u]=1;
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(!vis[v] && v!=p){
            getRoot(v,u);
            siz[u]+=siz[v];
            maxs=std::max(maxs,siz[v]);
        }
    }
    maxs=std::max(maxs,tot-siz[u]);
    if(csiz>maxs){
        csiz=maxs;
        crt=u;
    }
}
int fa[size];
void divide(int u){
    vis[u]=true;
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        if(!vis[v]){
            tot=siz[v],csiz=1<<30;
            getRoot(v,0);
            fa[crt]=u;
            divide(crt);
        }
    }
}
long long diss[size]={},disf[size]={},sum[size]={};
void add(int u,int e){
    sum[u]+=e;
    int src=u;
    while(fa[u]){
        long long d=dis(src,fa[u]);
        long long val=d*e;
        diss[fa[u]]+=val;
        disf[u]+=val;
        sum[fa[u]]+=e;
        u=fa[u];
    }
}
long long calc(int u){
    long long res=diss[u];
    int src=u;
    while(fa[u]){
        long long d=dis(src,fa[u]);
        res+=(diss[fa[u]]-disf[u])+d*(sum[fa[u]]-sum[u]);
        u=fa[u];
    }
    return res;
}
int maxwell=1;
long long query(int u,long long cu){
    for(int i=last[u];i;i=E[i].next){
        int v=E[i].to;
        long long cv=calc(v);
        if(cv<cu)return query(v,cv);
    }
    maxwell=u;
    return cu;
}
int main(){
    int n=read();
    int q=read();
    for(int i=1;i<n;++i){
        int u=read();
        int v=read();
        int w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    buildST();
    tot=n,csiz=1<<30;
    getRoot(1,0);
    divide(crt);
    while(q--){
        int u=read();
        int e=read();
        add(u,e);
        printf("%lld\n",query(maxwell,calc(maxwell)));
    }
    return 0;
}

