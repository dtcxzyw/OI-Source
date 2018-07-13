#include <cstdio>
#include <algorithm>
const int size=1001;
struct Edge{
	int to,next,w;
} E[size<<1];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int p[size][11],len[size],d[size];
void DFS(int u){
	for(int i=1;i<=10;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			p[v][0]=u;
			len[v]=len[u]+E[i].w;
			d[v]=d[u]+1;
			DFS(v);
		}
	}
}
int LCA(int u,int v){
	if(d[u]>d[v])std::swap(u,v);
	int delta=d[v]-d[u];
	for(int i=0;i<=10;++i)
		if(delta&(1<<i))v=p[v][i];
	if(u==v)return u;
	for(int i=10;i>=0;--i)
		if(p[u][i]!=p[v][i])
			u=p[u][i],v=p[v][i];
	return p[u][0];
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int u,v,w;
	for(int i=1;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	len[1]=d[1]=0;
	DFS(1);
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		int lca=LCA(u,v);
		printf("%d\n",len[u]+len[v]-(len[lca]<<1));
	}
	return 0;
}

