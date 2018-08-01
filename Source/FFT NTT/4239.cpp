#include <cstdio>
#include <algorithm>
#include <cstring>
#include <complex>
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
const int size=300005,mod=1000000007;
typedef double FT;
typedef long long Int64;
#define asInt64(x) static_cast<Int64>(x)
typedef std::complex<FT> Complex;
Complex w[size];
int tot;
Int64 powm(Int64 a,int k){
	Int64 res=1;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
void init(int n){
	tot=n;
	FT fac=2.0*acos(-1.0)/n;
	for(int i=0;i<n;++i)
		w[i]=Complex(cos(fac*i),sin(fac*i));
}
void FFT(int n,Complex* A){
	for(int i=0,j=0;i<n;++i){
		if(i>j)std::swap(A[i],A[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	for(int i=2;i<=n;i<<=1){
		int m=i>>1,fac=tot/i;
		for(int j=0;j<n;j+=i)
			for(int k=0;k<m;++k){
				Complex t=A[j+k+m]*w[fac*k];
				A[j+k+m]=A[j+k]-t;
				A[j+k]+=t;
			}
	}
}
Complex x[size],y[size],a[size],b[size],c[size],d[size];
void mul(int p,const int* A,const int* B,int* C){
	for(int i=0;i<p;++i)x[i]=Complex(A[i]&32767,A[i]>>15);
	memset(x+p,0,sizeof(Complex)*p);
	for(int i=0;i<p;++i)y[i]=Complex(B[i]&32767,B[i]>>15);
	memset(y+p,0,sizeof(Complex)*p);
	p<<=1;
	FFT(p,x);
    FFT(p,y);
    for(int i=0;i<p;++i){
    	int j=(p-i)&(p-1);
    	Complex da=(x[i]+conj(x[j]))*Complex(0.5,0.0);
        Complex db=(x[i]-conj(x[j]))*Complex(0.0,-0.5);
        Complex dc=(y[i]+conj(y[j]))*Complex(0.5,0.0);
        Complex dd=(y[i]-conj(y[j]))*Complex(0.0,-0.5);
    	a[j]=da*dc;
        b[j]=da*dd;
        c[j]=db*dc;
        d[j]=db*dd;
    }
    for(int i=0;i<p;++i)
    	x[i]=a[i]+b[i]*Complex(0.0,1.0);
    for(int i=0;i<p;++i)
    	y[i]=c[i]+d[i]*Complex(0.0,1.0);
    FFT(p,x);
    FFT(p,y);
    for(int i=0;i<p;++i){
    	Int64 da=asInt64(x[i].real()/p+0.5)%mod;
        Int64 db=asInt64(x[i].imag()/p+0.5)%mod;
        Int64 dc=asInt64(y[i].real()/p+0.5)%mod;
        Int64 dd=asInt64(y[i].imag()/p+0.5)%mod;
        int val=(da+((db+dc)<<15)+(dd<<30))%mod;
        C[i]=(val<0?val+mod:val);
    }
}
int C[size];
void inv(int n,int* A,int* B){
    if(n==1)B[0]=powm(A[0],mod-2);
    else{
        inv(n>>1,A,B);
        //B=(2-A*B)*B
        mul(n,A,B,C);
		mul(n,C,B,C);
		for(int i=0;i<n;++i){
			int val=(2LL*B[i]-C[i])%mod;
			B[i]=(val<0?val+mod:val);
		}
    }
}
int A[size]={},B[size];
int main(){
    int n=read();
    int m=1;
    while(m<n)m<<=1;
    init(m<<1);
    for(int i=0;i<n;++i)A[i]=read();
    inv(m,A,B);
    for(int i=0;i<n;++i)printf("%d ",B[i]);
    return 0;
}

