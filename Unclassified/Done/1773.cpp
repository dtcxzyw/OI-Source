#include <cstdio>
#include <cstring>
int dp[1001][50],a[1001],sum[1001][1001]={};
int read(){
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	int p=0;
	while('0'<=c&&c<='9'){
		a[++p]=c-'0';
		c=getchar();
	}
	return p;
}
int m;
void CAS(int& a,int b){
	if(a>b)a=b;
}
int main(){
	int len=read();
	scanf("%d",&m);
	for(int i=1;i<=len;++i)
		for(int j=i;j<=len;++j)
			sum[i][j]=(sum[i][j-1]*10+a[j])%m;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=len;++i)
		dp[i][sum[1][i]]=1;
	for(int i=1;i<=len;++i)
		for(int j=1;j<i;++j)
			for(int k=0;k<m;++k)
				CAS(dp[i][(k*sum[j+1][i])%m],dp[j][k]+1);
	for(int k=0;k<m;++k)
		if(dp[len][k]!=0x3f3f3f3f){
			printf("%d %d ",k,dp[len][k]-1);
			break;
		}
	for(int k=m-1;k>=0;--k)
		if(dp[len][k]!=0x3f3f3f3f){
			printf("%d %d\n",k,dp[len][k]-1);
			break;
		}
	return 0;
}

