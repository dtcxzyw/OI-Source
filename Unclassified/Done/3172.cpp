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
const int size=100100,mod=1000000007;
int powm(int a,int k){
	int res=1;
	while(k){
		if(k&1)res=1LL*res*a%mod;
		k>>=1,a=1LL*a*a%mod;
	}
	return res;
}
int dp[size];
int main(){
	int n,k,l,h;
	scanf("%d%d%d%d",&n,&k,&l,&h);
	l=(l-1)/k;
	h/=k;
	int end=h-l+1;
	for(int i=end;i>0;--i){
		int a=h/i-l/i;
		dp[i]=(powm(a,n)-a)%mod;
		for(int j=i<<1;j<=end;j+=i)dp[i]=(dp[i]-dp[j])%mod;
	}
	printf("%d\n",(dp[1]+(l==0)+mod)%mod);
	return 0;
}

