#include <cstdio>
#include <cstring>
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
const int size=3001;
struct Edge{
	int to,next,w;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int c[size]={},dp[size][size],siz[size]={};
void DFS(int u){
	dp[u][0]=0;
	
	if(c[u]){
		siz[u]=1;
		dp[u][1]=c[u];
	}
	
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		DFS(v);
		siz[u]+=siz[v];
	}
	
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		for(int j=siz[u];j>=1;--j)
			for(int k=1;k<=std::min(j,siz[v]);++k)
				dp[u][j]=std::max(dp[u][j],dp[v][k]+dp[u][j-k]-E[i].w);
	}
}
int main(){
	int n=read();
	int m=read();
	int to,w;
	for(int i=1;i<=n-m;++i){
		int k=read();
		for(int j=0;j<k;++j){
			to=read();
			w=read();
			addEdge(i,to,w);
		}
	}
	for(int i=n-m+1;i<=n;++i)
		c[i]=read();
	memset(dp,0xc0,sizeof(dp));
	DFS(1);
	int ans=0;
	for(int i=m;i>=1;--i)
		if(dp[1][i]>=0){
			ans=i;
			break;
		}
	printf("%d\n",ans);
	return 0;
}

