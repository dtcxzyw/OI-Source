#include <cstdio>
#include <algorithm>
const int size=30,mod=998244353;
long long dp[size][size]={},inv[size];
int main(){
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j){
			for(int l=0;l<=j;++l){
				for(int r=l;r<i;++r){
					int p=std::max(l+1,r);
					dp[i][p]=(dp[i][p]+dp[j][l]*dp[i-1][r])%mod;
				}
			}
		}
		for(int j=1;j<=i;++j)
			dp[i][j]=dp[i][j]*inv[i]%mod;
	}
	long long res=0;
	for(int i=1;i<=n;++i)
		res=(res+dp[n][i]*i)%mod;
	printf("%lld\n",res);
	long long val=58*inv[4]%mod*inv[2]%mod*inv[3]%mod;
	printf("%lld\n",val);
	return 0;
}

