#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
struct Edge{
	int to,next,w,c;
} E[1000];
int last[50]={},cnt=1;
const int S=48,T=49;
void addEdge(int u,int v,int w,int c=0){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w,E[cnt].c=c;
	last[u]=cnt;
}
int P[21][21],Q[21][21];
bool flag[50];
int dis[50],e[50],pre[50],f[50],ans=0;
bool SPFA(){
	memset(flag,0,sizeof(flag));
	memset(dis,0xc0,sizeof(dis));
	memset(f,0x3f,sizeof(f));
	std::queue<int> q;
	q.push(S);
	dis[S]=0;
	flag[S]=true;
	while(q.size()){
		int u=q.front();
		q.pop();
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].w>0 && dis[u]+E[i].c>dis[v]){
				dis[v]=dis[u]+E[i].c,e[v]=i,pre[v]=u,f[v]=std::min(f[u],E[i].w);
				if(!flag[v]){
					flag[v]=true;
					q.push(v);
				}
			}
		}
	} 
	if(dis[T]==0xc0c0c0c0)return false;
	ans+=f[T]*dis[T];
	int p=T;
	while(p!=S){
		E[e[p]].w-=f[T],E[e[p]^1].w+=f[T];
		p=pre[p];
	}
	return true;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&P[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&Q[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			int w=P[i][j]*Q[j][i];
			addEdge(i,j+n,1,w);
			addEdge(j+n,i,0,-w);
		}
	for(int i=1;i<=n;++i){
		addEdge(S,i,1);
		addEdge(i,S,0);
		addEdge(i+n,T,1);
		addEdge(T,i+n,0);
	}
	while(SPFA());
	printf("%d\n",ans);
	return 0;
}

