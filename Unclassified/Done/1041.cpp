#include <cstdio>
#include <vector>
const int size=301;
struct Edge{
	int to,next;
} E[1000];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size],siz[size],child[size]={};
std::vector<int> layer[size];
void DFS(int u,int d){
	siz[u]=1;
	layer[d].push_back(u) ;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p[u]){
			p[v]=u;
			DFS(v,d+1);
			siz[u]+=siz[v];
		}
	}
}
int ans=1<<30;
bool flag[size]={};
void color(int u,bool mask){
	flag[u]=mask;
	for(int i=last[u];i;i=E[i].next)
		if(E[i].to!=p[u])
			color(E[i].to,mask);
}
void cut(int d,int sum){
	ans=std::min(ans,sum);
	for(int i=0;i<layer[d].size();++i){
		int u=layer[d][i];
		if(flag[u])continue;
		color(u,true);
		cut(d+1,sum-siz[u]);
		color(u,false);
	}
}
int main(){
	int n,p;
	scanf("%d%d",&n,&p);
	int u,v;
	for(int i=0;i<p;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	cut(1,n);
	printf("%d\n",ans);
	return 0;
}

