#include <cstdio>
#include <cstring>
int link[15][15];
void CAS(int& a,int b){
	if(a>b)a=b;
}
int dp[1<<12],k[15],ans=1<<30,n,end;
void DFS(int u){
	for(int i=0;i<n;++i)
		if((1<<i)&u)
			for(int j=0;j<n;++j)
				if((1<<j|u)!=u && link[i][j]!=0x3f3f3f3f){
					int v=u|(1<<j);
					int nw=dp[u]+k[i]*link[i][j];
					if(nw<dp[v] && nw<ans){
						dp[v]=nw;
						k[j]=k[i]+1;
						DFS(v);
					}
				}
}
int main(){
	int m;
	scanf("%d%d",&n,&m);
	memset(link,0x3f,sizeof(link));
	int u,v,w;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&w);
		--u,--v;
		CAS(link[u][v],w);
		CAS(link[v][u],w);
	}
	end=(1<<n)-1;
	for(int r=0;r<n;++r){
		memset(dp,0x3f,sizeof(dp));
		dp[1<<r]=0;
		k[r]=1;
		DFS(1<<r);
		CAS(ans,dp[end]);
	}
	printf("%d\n",ans);
	return 0;
}

