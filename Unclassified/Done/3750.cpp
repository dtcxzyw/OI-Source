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
const int mod=100003,size=100100;
int A[size],inv[size],g[size],f[size];
int main(){
	int n=read();
	int k=read();
	for(int i=1;i<=n;++i)A[i]=read();
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
	int minp=0;
	for(int i=n;i>=1;--i)
		if(A[i]){
			++minp;
			for(int j=1;j*j<=i;++j)
				if(i%j==0){
					if(j*j==i)A[j]^=1;
					else A[i/j]^=1,A[j]^=1;
				}
		}
	g[n]=1;
	for(int i=n-1;i>=k+1;--i)
		g[i]=(1LL*g[i+1]*(n-i)%mod+n)*inv[i]%mod;
	for(int i=1;i<=k;++i)f[i]=i;
	for(int i=k+1;i<=minp;++i)f[i]=(f[i-1]+g[i])%mod;
	int res=f[minp];
	for(long long i=1;i<=n;++i)res=(i*res)%mod;
	printf("%d\n",res);
	return 0;
}

