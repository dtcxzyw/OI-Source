#include <cstdio>
typedef long long Int64;
const Int64 mod=1000000007LL,phi=mod-1,invk=mod-2;
Int64 read(){
	Int64 res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
void read(Int64& m1,Int64& m2){
	m1=m2=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		m1=(m1*10+c-'0')%mod;
		m2=(m2*10+c-'0')%phi;
		c=getchar();
	}
}
Int64 powm(Int64 a,Int64 k){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
Int64 inv(Int64 a){
	return powm(a,invk);
}
Int64 clamp(Int64 x){
	return (x%mod+mod)%mod;
}
Int64 sum(Int64 a,Int64 k){
	if(a==1)return clamp(k+1);
	return clamp(powm(a,k+1)-1)*inv(a-1)%mod;
}
Int64 calc(Int64 x,Int64 a,Int64 b,Int64 k){
	Int64 l=powm(a,k-1)*x%mod;
	Int64 r=b*sum(a,k-2)%mod;
	return (l+r)%mod;
}
int main(){
	Int64 n,np;
	read(n,np);
	Int64 m,mp;
	read(m,mp);
	Int64 a=read();
	Int64 b=read();
	Int64 c=read();
	Int64 d=read();
	Int64 v1m;
	if(a==1)v1m=clamp(1+(m-1)*b);
	else v1m=calc(1,a,b,mp);
	Int64 res;
	if(a==1 && c==1){
		Int64 B=(d+b*(m-1))%mod;
		res=clamp(v1m+(n-1)*B);
	}
	else{
		Int64 pv=powm(a,mp-1);
		Int64 A=pv*c%mod;
		Int64 B=(pv*d%mod+b*sum(a,mp-2)%mod)%mod;
		res=calc(v1m,A,B,np);
	}
	printf("%lld\n",res);
	return 0;
}

