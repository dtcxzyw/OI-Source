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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=1000100,mod=1000000007;
long long fac[size],inv[size],ifac[size],f[size];
void update(int x){
	static int i=2;
	for(;i<=x;++i){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifac[i]=ifac[i-1]*inv[i]%mod;
		f[i]=(i-1)*(f[i-1]+f[i-2])%mod;
	}
}
int main(){
	fac[0]=fac[1]=inv[1]=ifac[0]=ifac[1]=1;
	f[0]=1,f[1]=0;
	int t=read();
	for(int i=0;i<t;++i){
		int n=read();
		int m=read();
		update(n);
		long long C=fac[n]*ifac[m]%mod*ifac[n-m]%mod;
		print(C*f[n-m]%mod);
	}
	return 0;
}

