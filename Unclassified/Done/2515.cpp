#include <cstdio>
const int size=110;
struct Edge{
    int to,next;
} E1[size],E2[size];
int last1[size]={},last2[size]={},cnt1=0,cnt2=0;
void addEdge1(int u,int v){
    ++cnt1;
    E1[cnt1].to=v,E1[cnt1].next=last1[u];
    last1[u]=cnt1;
}
void addEdge2(int u,int v){
    ++cnt2;
    E2[cnt2].to=v,E2[cnt2].next=last2[u];
    last2[u]=cnt2;
}
int pcnt=0,dfn[size]={},low[size],st[size],scnt=0,bcnt=0,col[size],bv[size],bw[size];
bool flag[size]={};
int w[size],val[size];
void DFS(int u){
    flag[u]=true;
    dfn[u]=low[u]=++pcnt;
    st[++scnt]=u;
    for(int i=last1[u];i;i=E1[i].next){
        int v=E1[i].to;
        if(!dfn[v]){
            DFS(v);
            if(low[v]<low[u])low[u]=low[v];
        }
        else if(flag[v] && dfn[v]<low[u])
            low[u]=dfn[v];
    }
    if(dfn[u]==low[u]){
        int c=++bcnt;
        bv[c]=bw[c]=0;
        int v;
        do{
            v=st[scnt--];
            col[v]=c;
            flag[v]=false;
            bv[c]+=val[v],bw[c]+=w[v];
        }while(u!=v);
    }
}
bool in[size]={};
void pre(int n){
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            DFS(i);
    for(int i=0;i<=n;++i)
        for(int j=last1[i];j;j=E1[j].next){
            int v=E1[j].to;
            if(col[i]!=col[v])
                addEdge2(col[i],col[v]),in[col[v]]=true;
        }
}
int dp[size][501]={},m;
void CAS(int& a,int b){
    if(a<b)a=b;
}
void slove(int u){
    for(int i=last2[u];i;i=E2[i].next){
        int v=E2[i].to;
        slove(v);
        for(int j=m;j>=bw[v];--j)
            for(int k=bw[v];k<=j;++k)
                CAS(dp[u][j],dp[u][j-k]+dp[v][k-bw[v]]+bv[v]);
    }
}
int main(){
    int n;
    scanf("%d%d",&n,&m);
    w[0]=val[0]=0;
    for(int i=1;i<=n;++i)scanf("%d",&w[i]);
    for(int i=1;i<=n;++i)scanf("%d",&val[i]);
    int p;
    for(int i=1;i<=n;++i){
        scanf("%d",&p);
        if(p)addEdge1(p,i);
    }
    pre(n);
    for(int i=1;i<=bcnt;++i)
    	if(!in[i])addEdge2(0,i);
    slove(0);
    int ans=0;
    for(int i=0;i<=m;++i)
        if(dp[0][i]>ans)
            ans=dp[0][i];
    printf("%d\n",ans);
    return 0;
}

