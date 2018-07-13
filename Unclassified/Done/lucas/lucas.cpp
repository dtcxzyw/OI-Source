#include <cstdio>
#include <cstdint>
int64_t fac[100001];
int p;
inline int powm(int64_t n,int k){
	int64_t ans=1,mul=n;
	while(k){
		if(k&1)
			ans=ans*mul%p;
		k>>=1,mul=mul*mul%p;
	}
	return ans;
}
inline int C(int n,int m){
	if(n<m)return 0;
	return fac[n]*powm(fac[m]*fac[n-m],p-2)%p;
}
inline int lucas(int n,int m){
	int64_t ans=1;
	while(m && ans){
		ans=ans*C(n%p,m%p)%p;
		n/=p,m/=p;
	}
	return ans;
}
int main(){
	int t,n,m;
	scanf("%d",&t);
	while(t){
		scanf("%d%d%d",&n,&m,&p);
		fac[0]=1;
		for(int i=1;i<=p;++i)
			fac[i]=fac[i-1]*i%p;
		printf("%d\n",lucas(n+m,m));
		--t;
	}
	return 0;
}

