#include <cstdio>
typedef unsigned long long U64;
typedef long long Int64;
typedef __int128 Int128;
U64 read(){
	U64 res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
U64 random(U64 x){
	U64 val=(x^8951392852)+(x<<32)+(x>>32);
	return val%x;
}
U64 mul(Int128 a,Int128 b,Int128 mod){
	return a*b%mod;
}
U64 gcd(U64 a,U64 b){
	return b?gcd(b,a%b):a;
}
U64 pollardRHO(U64 n){
	U64 x=random(n),y=x;
	int k=2;
	for(int i=2;;++i){
		x=(mul(x,x,n)-1)%n;
		if(x<n)x+=n;
		U64 d=gcd(y-x,n);
		if(d!=1 && d!=n)return d;
		if(i==k){
			y=x;
			k<<=1;
		}
	}
}
void exgcd(U64 a,U64 b,Int64& x,Int64& y){
	if(b){
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	else x=1,y=0;
}
U64 inv(U64 u,Int64 r){
	Int64 x,y;
	exgcd(u,r,x,y);
	return (x%r+r)%r;
}
U64 powm(U64 a,U64 k,U64 mod){
	U64 res=1;
	while(k){
		if(k&1)res=mul(res,a,mod);
		k>>=1,a=mul(a,a,mod);
	}
	return res;
}
int main(){
	U64 e=read();
	U64 mod=read();
	U64 c=read();
	U64 a=pollardRHO(mod);
	U64 b=mod/a;
	U64 r=(a-1)*(b-1);
	U64 d=inv(e,r);
	U64 n=powm(c,d,mod);
	printf("%llu %llu\n",d,n);
	return 0;
}

