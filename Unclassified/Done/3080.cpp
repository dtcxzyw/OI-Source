#include <cstdio>
#include <cstring>
#include <algorithm>
int x[1001],dp[1001][1001][2];
int iabs(int x){
	return x>0?x:-x;
}
void CAS(int& a,int b){
	if(a>b)a=b;
}
int main(){
	int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    	scanf("%d",&x[i]);
    std::sort(x+1,x+n+1);
    
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;++i)
        dp[i][i][1]=dp[i][i][0]=iabs(x[i])*n;
        
	for(int k=2;k<=n;++k)
		for(int r=k;r<=n;++r){
			int l=r-k+1;
			CAS(dp[l][r][0],dp[l+1][r][0]+(x[l+1]-x[l])*(n-k+1));
			CAS(dp[l][r][0],dp[l+1][r][1]+(x[r]-x[l])*(n-k+1));
			CAS(dp[l][r][1],dp[l][r-1][0]+(x[r]-x[l])*(n-k+1));
			CAS(dp[l][r][1],dp[l][r-1][1]+(x[r]-x[r-1])*(n-k+1));
		}
	printf("%d\n",std::min(dp[1][n][0],dp[1][n][1]));
    return 0;
}

