#include <cstdio>
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
int A[100002],q[100011],b=0,e=1;
long long dp[100001];
int main(){
	int n=read();
	int k=read();
	long long sum=0;
	for(int i=1;i<=n;++i){
		A[i]=read();
		sum+=A[i];
	}
	A[n+1]=dp[0]=q[b]=0;
	for(int i=1;i<=n+1;++i){
		while(b!=e && q[b]<i-k-1)++b;
		dp[i]=dp[q[b]]+A[i];
		while(b!=e && dp[q[e-1]]>=dp[i])--e;
		q[e++]=i;
	}
	printf("%lld\n",sum-dp[n+1]);
	return 0;
}

