#include <cstdio>
#include <map>
#include <string>
#include <cstring>
const int size=101;
bool link[size][size]={};
int dp[size][size];
char buf[256];
std::string read(){
	scanf("%s",buf);
	return buf;
}
void CAS(int& a,int b){
	if(a<b)a=b;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	std::map<std::string,int> id;
	for(int i=1;i<=n;++i)
		id[read()]=i;
	for(int i=0;i<m;++i){
		int u=id[read()],v=id[read()];
		link[u][v]=link[v][u]=true;
	}
	memset(dp,0xc0,sizeof(dp));
	dp[1][1]=1;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			for(int k=1;k<j;++k)
				if(link[k][j]){
					CAS(dp[i][j],dp[i][k]+1);
					CAS(dp[j][i],dp[i][k]+1);
				}
	int ans=1;
	for(int i=1;i<=n;++i)
		if(dp[i][n]>ans && link[i][n])
			ans=dp[i][n];
	printf("%d\n",ans);
	return 0;
}

