#include <cstdio>
struct Edge{
	int to,next,w;
} E[210];
int last[101]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dp[101][101]={},child[101][2]={};
bool flag[101]={};
void DFS(int u){
	flag[u]=true;
	int c=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!flag[v]){
			child[u][c++]=i;
			DFS(v);
		}
	}
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int DFS(int u,int q){
	if(q==0)return 0;
	if(dp[u][q])return dp[u][q];
	if(child[u][0]){
		int le=child[u][0],re=child[u][1];
		CAS(dp[u][q],E[le].w+DFS(E[le].to,q-1));
		CAS(dp[u][q],E[re].w+DFS(E[re].to,q-1));
		for(int i=0;i+2<=q;++i)
			CAS(dp[u][q],E[le].w+E[re].w+DFS(E[le].to,i)+DFS(E[re].to,q-2-i));
	}
	return dp[u][q];
}
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	int u,v,w;
	for(int i=1;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1);
	printf("%d\n",DFS(1,q));
	return 0;
}

