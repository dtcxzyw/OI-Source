#include <cstdio>
#include <algorithm>
const int size=6001;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int c[size],dp[size][2]={};
bool flag[size]={};
void DFS(int u){
	dp[u][0]=0;
	dp[u][1]=std::max(c[u],0);
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		DFS(v);
		if(dp[v][0]>0)dp[u][1]+=dp[v][0];
		if(dp[v][1]>0)dp[u][0]+=dp[v][1];
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&c[i]);
	int l,k;
	for(int i=1;i<n;++i){
		scanf("%d%d",&l,&k);
		addEdge(k,l);
		flag[l]=true;
	}
	scanf("%d%d",&l,&k);
	for(int i=1;i<=n;++i)
		if(!flag[i]){
			DFS(i);
			printf("%d\n",std::max(dp[i][0],dp[i][1]));
		}
	return 0;
}

