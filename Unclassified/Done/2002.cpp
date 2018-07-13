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
struct Edge{
    int to,next;
} E[2][500001];
const int size=100001;
int last[2][size]={},cnt[2]={};
void addEdge(int u,int v,int x){
    ++cnt[x];
    E[x][cnt[x]].to=v,E[x][cnt[x]].next=last[x][u];
    last[x][u]=cnt[x];
}
int pcnt=0,bcnt=0,dfn[size]={},low[size],st[size],top=0,col[size];
bool flag[size]={};
void DFS(int u){
    low[u]=dfn[u]=++pcnt;
    st[++top]=u;
    flag[u]=true;
    for(int i=last[0][u];i;i=E[0][i].next){
        int v=E[0][i].to;
        if(!dfn[v]){
            DFS(v);
            low[u]=std::min(low[u],low[v]);
        }
        else if(flag[v])
            low[u]=std::min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        ++bcnt;
        int v;
        do{
            v=st[top--];
            col[v]=bcnt;
            flag[v]=false;
        }
        while(u!=v);
    }
}
int in[size]={},p[size];
void topSort(int n){
    int siz=0;
    for(int i=1;i<=n;++i)
        for(int j=last[1][i];j;j=E[1][j].next)
            ++in[E[1][j].to];
    for(int i=1;i<=n;++i)
        if(!in[i])
            p[++siz]=i;
    for(int i=1;i<=siz;++i){
        int u=p[i];
        for(int j=last[1][u];j;j=E[1][j].next){
            int v=E[1][j].to;
            if(--in[v]==0)
                p[++siz]=v;
        }
    }
}
bool mark[size]={};
void color(int u){
	mark[u]=true;
	for(int i=last[1][u];i;i=E[1][i].next){
		int v=E[1][i].to;
		if(!mark[v])
			color(v);
	}
}
int main(){
    int n=read();
    int m=read();
    int u,v;
    for(int i=0;i<m;++i){
        u=read();
        v=read();
        addEdge(u,v,0);
    }
        
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            DFS(i);
            
    for(int i=1;i<=n;++i)
        for(int j=last[0][i];j;j=E[0][j].next){
            int v=E[0][j].to;
            if(col[i]!=col[v])
                addEdge(col[i],col[v],1);
        }
        
    topSort(bcnt);
    
    int ans=0;
    for(int i=1;i<=bcnt;++i){
		int u=p[i];
    	if(!mark[u])
    		++ans,color(u);
    }
    
    printf("%d\n",ans);
    return 0;
}

