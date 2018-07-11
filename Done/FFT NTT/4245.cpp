#include <cstdio>
#include <algorithm>
#include <cstring>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
typedef long long Int64;
typedef __int128 Int128;
#define asInt64(x) static_cast<Int64>(x)
#define asInt128(x) static_cast<Int128>(x)
const int size=300005,m1=469762049,m2=998244353,m3=1004535809,g=3;
int mod;
Int64 powm(Int64 a,int k){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int add(int a,int b){
	a+=b;
	return a>=mod?a-mod:a;
}
int sub(int a,int b){
	a-=b;
	return a<0?a+mod:a;
}
int root[size],invR[size],tot;
void init(int n){
	tot=n;
	Int64 base=powm(g,(mod-1)/n);
	Int64 invBase=powm(base,mod-2);
	root[0]=invR[0]=1;
	for(int i=1;i<n;++i)root[i]=root[i-1]*base%mod;
	for(int i=1;i<n;++i)invR[i]=invR[i-1]*invBase%mod;
}
void NTT(int n,int* A,int* w){
	for(int i=0,j=0;i<n;++i){
		if(i>j)std::swap(A[i],A[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	for(int i=2;i<=n;i<<=1){
		int m=i>>1,fac=tot/i;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<m;++k){
				int t=asInt64(A[j+k+m])*w[fac*k]%mod;
				A[j+k+m]=sub(A[j+k],t);
				A[j+k]=add(A[j+k],t);
			}
		}
	}
}
int T1[size],T2[size];
void mul(int n,int* A,int* B,int* C,int mv){
	mod=mv;
	init(n);
	memcpy(T1,A,sizeof(int)*n);
	memcpy(T2,B,sizeof(int)*n);
	A=T1,B=T2;
	NTT(n,A,root);
	NTT(n,B,root);
	for(int i=0;i<n;++i)
		C[i]=asInt64(A[i])*B[i]%mod;
	NTT(n,C,invR);
	Int64 div=powm(n,mod-2);
	for(int i=0;i<n;++i)
		C[i]=C[i]*div%mod;
}
int A[size]={},B[size]={},C[3][size]={};
Int128 getK(Int128 mul,int mv){
	mod=mv;
	Int128 m=mul/mv;
	return powm(m%mv,mv-2)*m%mul;
}
int main(){
	int n=read();
	int m=read();
	int p=read();
	for(int i=0;i<=n;++i)A[i]=read();
	for(int i=0;i<=m;++i)B[i]=read();
	int k=1;
	while(k<((std::max(n,m)+1)<<1))k<<=1;
	mul(k,A,B,C[0],m1);
	mul(k,A,B,C[1],m2);
	mul(k,A,B,C[2],m3);
	Int128 mul=asInt128(m1)*m2*m3;
	Int128 k1=getK(mul,m1),k2=getK(mul,m2),k3=getK(mul,m3);
	int end=n+m;
	for(int i=0;i<=end;++i){
		int val=((C[0][i]*k1+C[1][i]*k2+C[2][i]*k3)%mul)%p;
		printf("%d ",val);
	}
	return 0;
}

