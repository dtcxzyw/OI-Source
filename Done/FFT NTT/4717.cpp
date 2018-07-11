#include <cstdio>
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
typedef void(*FwtFunc)(int*,int);
#define asInt64(x) static_cast<Int64>(x)
const int size=1<<18,mod=998244353;
int add(int a,int b){
	a+=b;
	return a>=mod?a-mod:a;
}
int sub(int a,int b){
	a-=b;
	return a<0?a+mod:a;
}
const Int64 inv2=499122177;
#define FWTBEGIN(func) \
void func(int* A,int n){\
	for(int i=2;i<=n;i<<=1){\
		int m=i>>1;\
		for(int j=0;j<n;j+=i){\
			for(int k=0;k<m;++k){\
				
#define FWTEND }\
		}\
	}\
}

FWTBEGIN(FWTOr)
A[j+k+m]=add(A[j+k],A[j+k+m]);
FWTEND
FWTBEGIN(UFWTOr)
A[j+k+m]=sub(A[j+k+m],A[j+k]);
FWTEND
FWTBEGIN(FWTAnd)
A[j+k]=add(A[j+k],A[j+k+m]);
FWTEND
FWTBEGIN(UFWTAnd)
A[j+k]=sub(A[j+k],A[j+k+m]);
FWTEND

FWTBEGIN(FWTXor)
int t=A[j+k+m];
A[j+k+m]=sub(A[j+k],t);
A[j+k]=add(A[j+k],t);
FWTEND
FWTBEGIN(UFWTXor)
int t=A[j+k+m];
A[j+k+m]=sub(A[j+k],t)*inv2%mod;
A[j+k]=add(A[j+k],t)*inv2%mod;
FWTEND

int A[size],B[size],C[size],D[size];
void foo(int n,FwtFunc fwt,FwtFunc ufwt){
	memcpy(C,A,sizeof(int)*n);
	memcpy(D,B,sizeof(int)*n);
	fwt(C,n);
	fwt(D,n);
	for(int i=0;i<n;++i)
		C[i]=asInt64(C[i])*D[i]%mod;
	ufwt(C,n);
	for(int i=0;i<n;++i)
		printf("%d ",C[i]);
	puts("");
}
int main(){
	int n=1<<read();
	for(int i=0;i<n;++i)A[i]=read();
	for(int i=0;i<n;++i)B[i]=read();
	foo(n,FWTOr,UFWTOr);
	foo(n,FWTAnd,UFWTAnd);
	foo(n,FWTXor,UFWTXor);
	return 0;
}

