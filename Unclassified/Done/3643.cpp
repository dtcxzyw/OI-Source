#include <cstdio>
#include <algorithm>
const int size=520;
const long long mod=1000000007;
int A[size],B[size],X[2*size],len[2*size],inv[size],dp[size][2*size];
int get(int x,int siz){
	return std::upper_bound(X,X+siz,x)-X;
}
int main(){
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
	int siz=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&A[i],&B[i]);
		X[siz++]=A[i];
		X[siz++]=B[i]+1;
	}
	std::sort(X,X+siz);
	siz=std::unique(X,X+siz)-X;
	for(int i=1;i<=n;++i)
		A[i]=get(A[i],siz),B[i]=get(B[i],siz);
	for(int i=1;i<siz;++i)len[i]=X[i]-X[i-1];
	for(int i=0;i<siz;++i)dp[0][i]=1;
	for(int i=1;i<=n;++i){
		dp[i][0]=1;
		for(int j=A[i];j<=B[i];++j){
			dp[i][j]=static_cast<long long>(dp[i-1][j-1])*len[j]%mod;
			long long cnt=1,c=len[j]-1;
			for(int k=i-1;k && c;--k)
				if(A[k]<=j && j<=B[k]){
					++cnt;
					c=c*(len[j]+cnt-2)%mod*inv[cnt]%mod;
					dp[i][j]=(dp[i][j]+dp[k-1][j-1]*c)%mod;
				}
		}
		for(int j=1;j<siz;++j)
			dp[i][j]=(mod+dp[i][j]+dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1])%mod;
	}
	int ans=(mod+dp[n][siz-1]-1)%mod;
	printf("%d\n",ans);
	return 0;
}

