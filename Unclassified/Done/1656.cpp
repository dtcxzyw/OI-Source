#include <cstdio>
#include <algorithm>
struct Edge{
	int to,next;
} E[10001];
int last[151]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
struct Pair{
	int u,v;
	bool operator<(Pair rhs) const{
		return u==rhs.u?v<rhs.v:u<rhs.u;
	}
} ans[10001];
int acnt=0;
void addAns(int u,int v){
	if(u>v)std::swap(u,v);
	ans[acnt].u=u,ans[acnt].v=v;
	++acnt;
}
int dfn[151],low[151],pcnt;
void DFS(int u,int p){
	dfn[u]=low[u]=++pcnt;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!dfn[v]){
			DFS(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>dfn[u])
				addAns(u,v);
		}
		else if(dfn[v]<dfn[u] && v!=p)
			low[u]=std::min(low[u],dfn[v]);
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	std::sort(ans,ans+acnt);
	for(int i=0;i<acnt;++i)
		printf("%d %d\n",ans[i].u,ans[i].v);
	return 0;
}

