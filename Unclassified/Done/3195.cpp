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
const int size=50010;
long long sum[size],X[size],Y[size],C[size],q[size],dp[size];
double slope(int x,int y){
	return static_cast<double>(C[x]-C[y])/(Y[x]-Y[y]);
}
int main(){
	int n=read();
	int l=read();
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+read();
		X[i]=sum[i]+i-l-1;
		Y[i]=i+sum[i];
	}
	int b=0,e=1;
	q[0]=0;
	X[0]=-l-1;
	for(int i=1;i<=n;++i){
		while(e-b>1 && 2*X[i]>slope(q[b],q[b+1]))++b;
		long long d=X[i]-Y[q[b]];
		dp[i]=dp[q[b]]+d*d;
		C[i]=dp[i]+Y[i]*Y[i];
		while(e-b>1 && slope(q[e-2],q[e-1])>slope(q[e-1],i))--e;
		q[e++]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}

