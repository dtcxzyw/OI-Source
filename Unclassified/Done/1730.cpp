#include <cstdio>
#include <cstring>
int dp[51][51][1001];
template <typename T>
void CAS(T& a,T b){
	if(a>b)a=b;
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
int main(){
	int n=read();
	int m=read();
	int u,v,w;
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		CAS(dp[u][v][1],w);
	}
	for(int e=2;e<=m;++e)
		for(int k=1;k<=n;++k)
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j)
					CAS(dp[i][j][e],dp[i][k][e-1]+dp[k][j][1]);
	int q=read();
	for(int i=0;i<q;++i){
		double ans=1e10;
		u=read();
		v=read();
		for(int j=1;j<=m;++j)
			if(dp[u][v][j]!=0x3f3f3f3f)
				CAS(ans,static_cast<double>(dp[u][v][j])/j);
		if(ans==1e10)puts("OMG!");
		else printf("%.3lf\n",ans);
	}
	return 0;
}

