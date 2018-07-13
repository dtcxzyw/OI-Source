#include <cstdio>
const int size=5001;
struct Edge{
	int to,next;
} E[10010];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
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
int dp[size][size]={},sum[size]={},m;
const int mod=1000000007;
int clamp(int x){
	return (x+mod)%mod;
}
void DFS(int u,int p){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p)DFS(v,u);
	}
	for(int i=1;i<=m;++i){
		if(!dp[u][i])continue;
		for(int j=last[u];j;j=E[j].next){
			int v=E[j].to;
			if(v!=p)dp[u][i]=clamp(1LL*dp[u][i]*clamp((sum[v]-dp[v][i])%mod)%mod);
		}
		sum[u]=clamp((sum[u]+dp[u][i])%mod);
	}
}
int main(){
	int n,k;
	n=read();
	m=read();
	for(int i=1;i<=n;++i){
		k=read();
		for(int j=0;j<k;++j)
			++dp[i][read()];
	}
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1,0);
	printf("%d\n",sum[1]);
	return 0;	
}

