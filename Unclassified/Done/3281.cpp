#include <cstdio>
#include <cstring>
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
const int size=100005,mod=20130427;
long long bit,bsum,P[size],S[size],A[size],L[size],R[size],dp[size][2];
long long maxv(long long a,long long b){
	return a>b?a:b;
}
int DP(bool dec){
	int n=read();
	for(int i=n;i>=1;--i)A[i]=read();
	if(dec){
		for(int i=1;i<=n;++i)
			if(A[i]){
				--A[i];
				for(int j=1;j<i;++j)
					A[j]=bit-1;
				break;
			}
		while(!A[n])--n;
		if(n==0)return 0;
	}
	L[0]=0;
	for(int i=1;i<=n;++i)L[i]=(L[i-1]+A[i]*P[i-1])%mod;
	R[n+1]=0;
	for(int i=n;i>=1;--i)R[i]=(R[i+1]*bit+A[i])%mod;
	memset(dp,0,sizeof(dp));
	long long ans=0;
	for(int i=1;i<=n;++i){
		long long mul=P[i-1]*S[i-1]%mod;
		dp[i][0]=(bit*dp[i-1][0]+bsum*mul)%mod;
		dp[i][1]=(A[i]*dp[i-1][0]+((A[i]*(A[i]-1))>>1)%mod*mul+
			dp[i-1][1]+A[i]*(L[i-1]+1)%mod*S[i-1])%mod;
		ans=(ans+maxv(0,R[i+1]-1)*dp[i][0]+dp[i][1])%mod;
	}
	return ans;
}
int main(){
	bit=read();
	bsum=(((bit-1)*bit)>>1)%mod;
	P[0]=1,S[0]=1;
	for(int i=1;i<size;++i){
		P[i]=P[i-1]*bit%mod;	
		S[i]=(S[i-1]+P[i])%mod;
	}
	int pl=DP(true);
	int pr=DP(false);
	printf("%d\n",(pr-pl+mod)%mod);
	return 0;
}

