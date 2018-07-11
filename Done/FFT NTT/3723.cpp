#include <cstdio>
#include <complex>
#include <algorithm>
#include <cmath>
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
typedef double FT;
typedef long long Int64;
typedef std::complex<FT> Complex;
const int size=140005;
Complex root[size],invR[size];
int tot;
void init(int n){
	tot=n;
	FT fac=2.0*acos(-1.0)/n;
	for(int i=0;i<n;++i){
		root[i]=Complex(cos(fac*i),sin(fac*i));
		invR[i]=conj(root[i]);
	}
}
void FFT(int n,Complex* A,Complex* w){
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
Complex A[size],B[size],C[size];
int mul(int n){
	int m=1;
    while(m<(n<<1))m<<=1;
    init(m);
    FFT(m,A,root);
    FFT(m,B,root);
    for(int i=0;i<m;++i)
    	C[i]=A[i]*B[i];
    FFT(m,C,invR);
    return m;
}
int main(){
    int n=read();
    int m=read();
    int off=n-1;
    Int64 SA=0,SA2=0;
    for(int i=0;i<n;++i){
    	int x=read();
    	SA+=x,SA2+=x*x;
		A[i]=Complex(x,0.0);
    }
    memcpy(A+n,A,sizeof(Complex)*n);
    Int64 SB=0,SB2=0;
    for(int i=0;i<n;++i){
    	int x=read();
    	SB+=x,SB2+=x*x;
		B[off-i]=Complex(x,0.0);
    }
    int div=mul(n);
    Int64 val=0,fac=2*(SA-SB);
    Int64 mwc=round(-fac/(2.0*n)),offset=(n*mwc+fac)*mwc+SA2+SB2;
    for(int i=0;i<n;++i){
    	Int64 c=C[i+off].real()/div+0.5;
    	val=std::max(val,c);
    }
    printf("%lld\n",offset-2*val);
    return 0;
}

