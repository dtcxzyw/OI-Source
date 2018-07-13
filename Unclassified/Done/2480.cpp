#include <cstdio>
const int mod=999911659,phi=999911658;
long long powm(long long a,int k,int m){
	a%=mod;
	long long res=1;
	while(k){
		if(k&1)res=res*a%m;
		k>>=1,a=a*a%m;
	}
	return res;
}
int info[4][2],fac[4][36000],inv[4][36000],pcnt=0;
void initPrime(int x){
	int id=pcnt++;
	info[id][0]=x;
	int m=phi/x;
	info[id][1]=m*powm(m,x-2,x)%phi;
	fac[id][0]=1;
	for(int i=1;i<x;++i)
		fac[id][i]=fac[id][i-1]*i%x;
	inv[id][1]=1;
	for(int i=2;i<x;++i)
		inv[id][i]=(x-x/i)*inv[id][x%i]%x;
	inv[id][0]=1;
	for(int i=1;i<x;++i)
		inv[id][i]=inv[id][i-1]*inv[id][i]%x;
}
void pre(){
	int x=phi;
	for(int i=2;i<=x && x!=1;++i)
		if(x%i==0){
			do x/=i;
			while(x%i==0);
			initPrime(i);
		}
}
int C(int n,int m,int p,int mv){
	return fac[p][n]*inv[p][m]%mv*inv[p][n-m]%mv;
}
long long lucas(int n,int m,int p,int mv){
	int res=1;
	while(n|m){
		int a=n%mv,b=m%mv;
		if(a<b)return 0;
		res=res*C(a,b,p,mv)%mv;
		n/=mv,m/=mv;
	}
	return res;
}
int C(int n,int m){
	int res=0;
	for(int i=0;i<pcnt;++i)
		res=(res+lucas(n,m,i,info[i][0])*info[i][1])%phi;
	return res;
}
int main(){
	pre();
	int n,g;
	scanf("%d%d",&n,&g);
	if(g==mod)puts("0");
	else{
		int sum=0;
		for(int i=1;i*i<=n;++i){
			if(n%i==0){
				sum=(sum+C(n,i))%phi;
				int j=n/i;
				if(j!=i)sum=(sum+C(n,j))%phi;
			}
		}
		int ans=powm(g,sum,mod);
		printf("%d\n",ans);
	}
	return 0;
}

