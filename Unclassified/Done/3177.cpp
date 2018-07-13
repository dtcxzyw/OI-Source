#include <cstdio>
typedef long long Int64;
const int size=2010;
struct Edge{
	int to,next;
	Int64 w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,Int64 w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
void CAS(Int64& a,Int64 b){
	if(a<b)a=b;
}
int minv(int a,int b){
	return a<b?a:b;
}
int n,k;
Int64 dp[size][size]={};
int siz[size];
void DFS(int u,int p){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			DFS(v,u);
			siz[u]+=siz[v];
		}
	}
	dp[u][0]=dp[u][1]=0;
	for(int i=2;i<=k && i<=siz[u];++i)dp[u][i]=-1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			for(int j=minv(siz[u],k);j>=0;--j)
				for(int s=0;s<=j && s<=siz[v];++s)
					if(dp[u][j-s]>=0){
						int s1=s*(k-s);
						int s2=(siz[v]-s)*(n-k-(siz[v]-s));
						CAS(dp[u][j],dp[u][j-s]+dp[v][s]+E[i].w*(s1+s2));
					}
		}
	}
}
int main(){
	scanf("%d%d",&n,&k);
	int u,v;
	Int64 w;
	for(int i=1;i<n;++i){
		scanf("%d%d%lld",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1,0);
	printf("%lld\n",dp[1][k]);
	return 0;
}

