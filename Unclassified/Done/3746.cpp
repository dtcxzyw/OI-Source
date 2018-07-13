#include <cstdio>
int prime[1<<15];
bool flag[1<<15]={};
int calcPhi(int x){
	int cnt=0;
	for(int i=2;i<=x;++i){
		if(!flag[i])prime[++cnt]=i;
		for(int j=1;prime[j]*i<(1<<15);++j){
			flag[prime[j]*i]=true;
			if(!(i%prime[j]))break;
		}
	}
	
	for(int i=1;i<=cnt;++i)
	    if(!(x%prime[i]))
	        x=x/prime[i]*(prime[i]-1);
	return x-1;
}
int powm(long long x,int k,long long p){
	long long res=1;
	while(k){
		if(k&1)res=res*x%p;
		k>>=1,x=x*x%p;
	}
	return res;
}
long long cache=1;
int C(int m,int n,int p,int phi){
	long long res=cache;
	for(int i=2;i<=m;++i)
	    res=res*powm(i,phi,p)%p;
	for(int i=2;i<=n-m;++i)
	    res=res*powm(i,phi,p)%p;
	return res;
}
int main(){
	int n,p,k,r;
	scanf("%d%d%d%d",&n,&p,&k,&r);
	int phi=calcPhi(p);
	n*=k;
	for(int i=2;i<=n;++i)
	    cache=cache*i%p;
	int ans=0;
	for(int i=r;i<=n;i+=k)
		ans=(ans+C(i,n,p,phi))%p;
	printf("%d\n",ans);
	return 0;
}
