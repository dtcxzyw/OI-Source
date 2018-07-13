#include <cstdio>
#include <algorithm>
typedef long long Int64;
char buf[30000100];
Int64 input(Int64 mod){
	Int64 res=0;
	for(Int64 i=0;buf[i];++i)
		res=(res*10+buf[i]-'0')%mod;
	return res;
}
Int64 mod;
struct Mat{
	Int64 v[2][2];
	Mat(){
		v[0][0]=v[0][1]=v[1][0]=v[1][1]=0;
	}
	Mat operator*(const Mat& rhs) const{
		Mat res;
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
				for(int k=0;k<2;++k)
					res.v[i][j]=(res.v[i][j]+v[i][k]*rhs.v[k][j])%mod;
		return res;
	}
};
Int64 calc(Int64 k,Int64 p){
	mod=p;
	Mat ans,mul;
	ans.v[0][0]=ans.v[1][1]=mul.v[0][1]=mul.v[1][0]=mul.v[1][1]=1;	
	while(k){
		if(k&1)ans=ans*mul;
		k>>=1,mul=mul*mul;
	}
	return ans.v[0][1];
}
Int64 gcd(Int64 a,Int64 b){
	return b?gcd(b,a%b):a;
}
Int64 powm(Int64 a,Int64 k,Int64 mod){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
Int64 fac[10000];
Int64 loop(Int64 p,Int64 mod){
	int fcnt=0;
	for(Int64 i=1;i*i<=p;++i)
		if(p%i==0){
			fac[fcnt++]=i;
			if(i*i!=p)fac[fcnt++]=p/i;
		}
	std::sort(fac,fac+fcnt);
	for(int i=0;i<fcnt;++i)
		if(calc(fac[i]+3,mod)==2)
			return fac[i];
}
const Int64 lut[6]={0,1,3,8,6,20};
Int64 g(Int64 p){
	if(p<=5)return lut[p];
	if(powm(5,(p-1)>>1,p)==1)return loop(p-1,p);
	else return loop((p+1)<<1,p);
}
Int64 pre(Int64 p){
	Int64 res=1;
	for(Int64 i=2;i*i<=p && p>1;++i)
		if(p%i==0){
			p/=i;
			Int64 x=g(i),old=p;
			while(p%i==0)p/=i;
			x*=old/p;
			res=res/gcd(res,x)*x;
		}
	if(p>1){
		Int64 x=g(p);
		res=res/gcd(res,x)*x;
	}
	return res;
}
int main(){
	Int64 p;
	scanf("%s%lld",buf,&p);
	printf("%lld\n",calc(input(pre(p)),p));
	return 0;
}

