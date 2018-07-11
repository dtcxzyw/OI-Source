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
#define asInt64(x) static_cast<Int64>(x)
const int size=17005,mod=1004535809;
Int64 powm(Int64 a,int k,int mod){
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
	const int g=3;
	tot=n;
	Int64 base=powm(g,(mod-1)/n,mod);
	Int64 invBase=powm(base,mod-2,mod);
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
int calcG(int p){
	int fac[15];
	int x=p-1,fcnt=0;
	for(int i=2;i<=x;++i)
		if(x%i==0){
			do x/=i;
			while(x%i==0);
			fac[++fcnt]=i;
		}
	for(int i=2;i<p;++i){
		bool flag=true;
		for(int j=1;j<=fcnt;++j)
			if(powm(i,p/fac[j],p)==1){
				flag=false;
				break;
			}
		if(flag)return i;
	}
	return -1;
}
int map[10000];
void initMap(int m,int g){
	int cur=1,end=m-2;
	for(int i=0;i<=end;++i){
		map[cur]=i;
		cur=cur*g%m;
	}
}
int A[size]={},B[size]={},C[size];
void powPoly(int n,int m){
	int d=m-1;
	int k=1;
	while(k<(d<<1))k<<=1;
	init(k);
	Int64 inv=powm(k,mod-2,mod);
	B[0]=1;
	while(n){
		if(n&1){
			//B=A*B
			memcpy(C,A,sizeof(int)*k);
			NTT(k,C,root);
			NTT(k,B,root);
			for(int i=0;i<k;++i)
				B[i]=asInt64(C[i])*B[i]%mod;
			NTT(k,B,invR);
			for(int i=0;i<d;++i)
				B[i]=add(B[i],B[i+d])*inv%mod;
			memset(B+d,0,sizeof(int)*(k-d));
		}
		n>>=1;
		//A=A*A
		NTT(k,A,root);
		for(int i=0;i<k;++i)
			A[i]=asInt64(A[i])*A[i]%mod;
		NTT(k,A,invR);
		for(int i=0;i<d;++i)
			A[i]=add(A[i],A[i+d])*inv%mod;
		memset(A+d,0,sizeof(int)*(k-d));
	}
}
int main(){
	int n=read();
	int m=read();
	int g=calcG(m);
	initMap(m,g);
	int x=map[read()];
	int s=read();
	for(int i=0;i<s;++i){
		int x=read();
		if(x)++A[map[x]];
	}
	powPoly(n,m);
	printf("%d\n",B[x]);
	return 0;
}

