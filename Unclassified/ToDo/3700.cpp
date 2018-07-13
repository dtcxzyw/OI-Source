#include <cstdio>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int mod=1000000007,size=4000001;
long long inv[size];
int main(){
	int n=read();
	int m=read();
	inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=-mod/i*inv[mod%i]%mod;
	for(int i=0;i<m;++i){
		int a=read();
		int b=read();
		long long cur=read()%mod*inv[a]%mod*inv[b]%mod;
		printf("%lld\n",(cur+mod)%mod);
		long long k=read();
		long long sum=(k*(k+1)>>1)%mod;
		int res=cur*sum%mod*sum%mod;
		printf("%d\n",(res+mod)%mod);
	}
	return 0;
}

