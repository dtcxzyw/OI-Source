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
const int size=1000005,mod=1000000007,cycle=mod-1;
typedef long long Int64;
int powm(Int64 a,int k){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int inv(int a){
	return powm(a,mod-2);
}
int mu[size],prime[size],pow[size][3];
Int64 fac[size],pFac[size],invPFac[size];
bool flag[size]={};
void pre(int n){
	mu[1]=1,pow[0][2]=0,pow[1][0]=pow[1][1]=pow[1][2]=1;
	int pcnt=0;
	for(int i=2;i<=n;++i){
		if(!flag[i]){
			mu[i]=-1;
			prime[++pcnt]=i;
		}
		for(int j=1;j<=pcnt && i*prime[j]<size;++j){
			int val=i*prime[j];
			flag[val]=true;
			if(i%prime[j]){
				mu[val]=-mu[i];
			}
			else{
				mu[val]=0;
				break;
			}
		}
	}
	for(int i=2;i<=n;++i){
		pow[i][2]=(pow[i-1][2]+pow[i-2][2])%mod;
		pow[i][0]=inv(pow[i][2]);
		pow[i][1]=1;
	}
	for(int i=1;i<=n;++i)fac[i]=1;
	for(int i=1;i<=n;++i)
		for(int j=i,x=1;j<=n;j+=i,++x)
			fac[j]=fac[j]*pow[i][mu[x]+1]%mod;
	pFac[0]=1;
	for(int i=1;i<=n;++i)
		pFac[i]=pFac[i-1]*fac[i]%mod;
	invPFac[n]=inv(pFac[n]);
	for(int i=n-1;i>=0;--i)
		invPFac[i]=invPFac[i+1]*fac[i+1]%mod;
}
int foo(){
	int n=read();
	int m=read();
	int end=std::min(n,m);
	Int64 res=1;
	for(int l=1;l<=end;){
		int r=std::min(n/(n/l),m/(m/l));
		res=res*powm(pFac[r]*invPFac[l-1]%mod,static_cast<Int64>(n/l)*(m/l)%cycle)%mod;
		l=r+1;
	}
	return res;
}
int main(){
	pre(1000000);
	int t=read();
	while(t--)printf("%d\n",foo());
	return 0;
}

