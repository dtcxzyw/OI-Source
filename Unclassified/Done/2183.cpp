#include <cstdio>
int fac[30],c[30]={},mod[30],fcnt=0;
void pre(int p){
	for(int i=2;p!=1;++i)
		if(p%i==0){
			fac[fcnt]=i;
			int old=p;
			do p/=i,++c[fcnt];
			while(p%i==0);
			mod[fcnt]=old/p;
			++fcnt;
		}
}
long long powm(long long a,int k,long long mod){
	long long res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int cum,cphi;
class Num{
private:
	long long a,k;
public:
	Num(int va,int vk):a(va),k(vk){}
	Num operator*(const Num& rhs) const{
		return Num(a*rhs.a%mod[cum],k+rhs.k);
	}
	Num operator/(const Num& rhs) const{
		return Num(a*powm(rhs.a,cphi-1,mod[cum])%mod[cum],k-rhs.k);
	}
	long long get() const{
		if(k>=c[cum])return 0;
		return a*powm(fac[cum],k,mod[cum])%mod[cum];
	}
};
long long base[100001];
Num getFac(int n){
	if(n==0)return Num(1,0);
	int div=n/fac[cum];
	int a=base[n%mod[cum]]*powm(base[mod[cum]-1],n/mod[cum],mod[cum])%mod[cum];
	return Num(a,div)*getFac(div);
}
long long C(int n,int m){
	return (getFac(n)/(getFac(m)*getFac(n-m))).get(); 
}
int A[5];
int main(){
	int p,n,m;
	scanf("%d%d%d",&p,&n,&m);
	long long sum=0;
	for(int i=0;i<m;++i){
		scanf("%d",&A[i]);
		sum+=A[i];
	}
	if(sum>n)puts("Impossible");
	else{
		pre(p);
		long long ans=0;
		for(int i=0;i<fcnt;++i){
			int cur=n;
			base[0]=1;
			for(int j=1;j<mod[i];++j){
				base[j]=base[j-1];
				if(j%fac[i])
					base[j]=base[j]*j%mod[i];
			}
			long long res=1;
			cum=i;
			cphi=mod[i]/fac[i]*(fac[i]-1);
			for(int j=0;j<m;++j){
				res=res*C(cur,A[j])%mod[i];
				cur-=A[j];
			}
			int m=p/mod[i];
			ans=(ans+res*m%p*powm(m%mod[i],cphi-1,mod[i]))%p;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

