#include <cstdio>
int prime[100],cnt=0,fac[501][100]={};
bool test(int x){
	for(int i=0;i<cnt;++i)
		if(x%prime[i]==0)return false;
	return true;
}
void pre(){
	for(int i=2;i<500;++i)
		if(test(i))
			prime[cnt++]=i;
	for(int i=2;i<=500;++i){
		int v=i;
		for(int j=0;j<cnt;++j)
			if(v%prime[j]==0){
				do v/=prime[j],++fac[i][j];
				while(v%prime[j]==0);	
			}
	}
}
int fsum[500][100]={},dsum[100]={};
typedef long long LL;
LL gcd(LL a,LL b){
	return b?gcd(b,a%b):a;
}
LL mul(int* p){
	LL res=1;
	for(int i=0;i<cnt;++i)
		for(int j=0;j<p[i];++j)
			res*=prime[i];
	return res;
}
int main(){
	pre();
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n+m;++i)
		for(int j=0;j<cnt;++j)
			dsum[j]+=fac[i][j];
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j)
			for(int k=0;k<cnt;++k)
				fsum[i][k]+=fac[j][k];
		for(int j=i+m;j<n+m;++j)
			for(int k=0;k<cnt;++k)
				fsum[i][k]+=fac[j][k];
	}
	for(int k=0;k<cnt;++k){
		int minv=dsum[k];
		for(int i=1;i<=n;++i)
			if(minv>fsum[i][k])
				minv=fsum[i][k];
		dsum[k]-=minv;
		for(int i=1;i<=n;++i)
			fsum[i][k]-=minv;
	}
	LL a=0,b=mul(dsum);
	for(int i=1;i<=n;++i)
		a+=mul(fsum[i]);
	LL c=gcd(a,b);
	a/=c,b/=c;
	printf("%lld\n%lld\n",a,b);
	return 0;
}

