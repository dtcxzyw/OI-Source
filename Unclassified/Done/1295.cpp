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
const int size=100100;
int h[size],dp[size],pre[size];
int maxv(int a,int b){
	return a>b?a:b;
}
int minv(int a,int b){
	return a<b?a:b;
}
int main(){
	int n=read();
	int m=read();
	int l=1,sum=0;
	h[0]=1<<30,dp[0]=0,pre[0]=-1;
	for(int i=1;i<=n;++i){
		h[i]=read();
		pre[i]=i-1;
		while(h[pre[i]]<=h[i])pre[i]=pre[pre[i]];
		sum+=h[i];
		while(sum>m)sum-=h[l++];
		dp[i]=1<<30;
		int j;
		for(j=i;pre[j]+1>=l;j=pre[j])
			dp[i]=minv(dp[i],dp[pre[j]]+h[j]);
		dp[i]=minv(dp[i],dp[l-1]+h[j]);
	}
	printf("%d\n",dp[n]);
	return 0;
}

