#include <cstdio>
#include <algorithm>
const int size=1<<16;
int prime[size],pcnt,fcnt,fac[size];
bool test(long long x){
	for(int i=0;i<pcnt;++i)
		if(x%prime[i]==0)
			return false;
	return true;
}
long long nfac[size],ncnt=0,f[size],base[size];
void DFS(int a,long long f){
	if(a==fcnt)nfac[ncnt++]=f;
	else{
		for(int i=0;i<=fac[a];++i){
			DFS(a+1,f);
			f*=base[a];
		}
	}
}
void pre(long long n){
	prime[0]=2,pcnt=1;
	for(int i=3;1LL*i*i<=n;i+=2)
		if(test(i))
			prime[pcnt++]=i;
	fcnt=0;
	for(int i=0;i<pcnt && n!=1;++i)
		if(n%prime[i]==0){
			base[fcnt]=prime[i];
			do ++fac[fcnt],n/=prime[i];
			while(n%prime[i]==0);
			++fcnt;
		}
	if(n!=1 && test(n)){
	    base[fcnt]=n;
	    fac[fcnt]=1;
	    ++fcnt;
	}
}
int main(){
	long long n;
	scanf("%lld",&n);
	pre(n);
	DFS(0,1);
	std::sort(nfac,nfac+ncnt);
	long long ans=0;
	for(int i=ncnt-1;i>=0;--i){
		f[i]=n/nfac[i];
		for(int j=i+1;j<ncnt;++j)
			if(nfac[j]%nfac[i]==0)
				f[i]-=f[j];
		ans+=f[i]*nfac[i];
	}
	printf("%lld\n",ans);
	return 0;
}

