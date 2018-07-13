#include <cstdio>
const int size=3100;
int S[size];
long long dp[size][size];
int q[size],b,e;
long long f(int i,int j){
	return dp[i][j]+S[i]*S[i];
}
double slope(int i,int j,int p){
	return static_cast<double>(f(j,p)-f(i,p))/(S[j]-S[i]);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&S[i]);
		S[i]+=S[i-1];
	}
	dp[0][0]=0;
	for(int i=1;i<=n;++i)dp[i][1]=S[i]*S[i];
	for(int i=2;i<=m;++i){
		b=e=0;
		for(int j=1;j<=n;++j){
			while(b+1<e && slope(q[b],q[b+1],i-1)<=2*S[j])++b;
			int k=(b<e?q[b]:0);
			int len=S[j]-S[k];
			dp[j][i]=dp[k][i-1]+len*len;
			while(b+1<e && slope(q[e-2],q[e-1],i-1)>=slope(q[e-1],j,i-1))--e;
			q[e++]=j;
		}
	}
	long long ans=m*dp[n][m]-S[n]*S[n];
	printf("%lld\n",ans);
	return 0;
}

