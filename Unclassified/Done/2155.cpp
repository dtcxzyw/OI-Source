#include <cstdio>
const int size=10000010;
int prime[1000010],pcnt=0,fac[size],f[size];
bool flag[size];
void pre(int n,int p){
	f[1]=fac[1]=1;
	for(int i=2;i<=n;++i){
		fac[i]=1LL*fac[i-1]*i%p;
		if(flag[i])f[i]=1LL*f[i-1]*i%p;
		else prime[pcnt++]=i,f[i]=1LL*f[i-1]*(i-1)%p;
		for(int j=0;j<pcnt && prime[j]*i<=n;++j){
			flag[prime[j]*i]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
int powm(int a,int k,int p){
	int res=1;
	while(k){
		if(k&1)res=1LL*res*a%p;
		k>>=1,a=1LL*a*a%p;
	}
	return res;
}
int n[10000],m[10000];
int main(){
	int t,p;
	scanf("%d%d",&t,&p);
	int maxv=0;
	for(int i=0;i<t;++i){
		scanf("%d%d",&n[i],&m[i]);
		if(maxv<n[i])maxv=n[i];
		if(maxv<m[i])maxv=m[i];
	}
	pre(maxv,p);
	for(int i=0;i<t;++i)
		printf("%d\n",static_cast<int>((1LL*f[m[i]]*fac[n[i]]%p)*powm(fac[m[i]],p-2,p)%p));
	return 0;
}

