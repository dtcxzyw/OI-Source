#include <cstdio>
#include <cstring>
char buf[60];
int dp[60][60];
bool comp(int b1,int b2,int siz){
	for(int i=0;i<siz;++i)
		if(buf[b1+i]!=buf[b2+i])
			return false;
	return true;
}
void CAS(int& a,int b){
	if(a>b)a=b;
}
int main(){
	scanf("%s",buf+1);
	int n=strlen(buf+1);
	memset(dp,0x3f,sizeof(dp));
	dp[1][1]=1;
	for(int i=2;i<=n;++i){
		for(int j=1;j<i;++j)
			for(int k=1;k<=j;++k){
				CAS(dp[i][k],dp[j][k]+i-j);
				if(i-j==j-k+1 && comp(j+1,k,i-j))CAS(dp[i][k],dp[j][k]+1);
			}
		for(int j=1;j<i;++j)
			CAS(dp[i][i],dp[i][j]+1);
	}
	int ans=1<<30;
	for(int i=1;i<=n;++i)
		CAS(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}

