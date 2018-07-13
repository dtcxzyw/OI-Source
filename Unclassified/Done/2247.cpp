#include <cstdio>
#include <cstring>
#include <cstdlib>
const int size=501;
struct Edge{
	int to,next;
} E[size*size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int fa[size];
bool flag[size]={};
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int dfn[size],low[size],p[size],pcnt=0,x=0;
bool mark[size];
void DFS(int u){
	mark[u]=true;
	dfn[u]=low[u]=++pcnt;
	int chi=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			if(mark[v]){
				if(p[u]!=v && low[u]>dfn[v])
					low[u]=dfn[v];
			}
			else{
				++chi;
				p[v]=u;
				DFS(v);
				if(low[u]>low[v])low[u]=low[v];
				if(p[u]==-1){
					if(chi>=2)x=u;
				}
				else if(dfn[u]<=low[v])
					x=u;
			}
		}
	}
}
void test(int n,int a=0,int b=0){
	memset(mark,0,sizeof(mark));
    flag[a]=flag[b]=true;
    int r;
    for(r=1;r<=n;++r)
    	if(!flag[r])break;
    p[r]=-1;
    DFS(r);
    if(x){
    	if(a)printf("%d ",a);
    	if(b)printf("%d ",b);
    	printf("%d ",x);
    	exit(0);
    }
    flag[a]=flag[b]=false;
}
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
        fa[i]=i;
    int u,v,cnt=n;
    for(int i=0;i<m;++i){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            fa[fu]=fv;
            --cnt;
        }
    }
    if(cnt!=1){
        puts("Poor SOL!");
        return 0;
    }
    if(k==1){
        for(int i=1;i<=n;++i)
            test(n);
    }
    else if(k==2){
        for(int i=1;i<=n;++i)
            test(n,i);
    }
    else{
        for(int i=1;i<=n;++i)
            for(int j=i+1;j<=n;++j)
                test(n,i,j);
    }
    puts("How oversuspicious you are, SOL!");
    return 0;
}

