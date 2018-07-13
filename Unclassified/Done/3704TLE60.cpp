#include <cstdio>
#include <algorithm>
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
const int size=1000005,mod=1000000007;
int f[size];
void update(int n){
	static int i=2;
	for(;i<=n;++i)
		f[i]=(f[i-1]+f[i-2])%mod;
}
long long powm(long long a,long long k){
	long long res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
long long fac[size];
long long foo(){
	int n=read();
	int m=read();
	update(std::max(n,m));
	int siz=std::min(n,m);
	long long res=1;
	for(int i=siz;i>=1;--i){
		fac[i]=static_cast<long long>(n/i)*(m/i);
		for(int j=i<<1;j<=siz;j+=i)fac[i]-=fac[j];
		res=res*powm(f[i],fac[i])%mod;
	}
	return res;
}
int main(){
	f[0]=0,f[1]=1;
	int t=read();
	while(t--)printf("%lld\n",foo());
	return 0;
}

