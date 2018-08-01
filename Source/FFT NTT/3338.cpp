#include <cstdio>
#include <complex>
#include <algorithm>
#include <cmath>
typedef double FT;
typedef std::complex<FT> Complex;
const int size=600000;
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
Complex A[size],B[size];
int main(){
	int n;
	scanf("%d",&n);
	int m=1;
	while(m<(n<<1))m<<=1;
	init(m);
	for(int i=0;i<n;++i){
		double x;
		scanf("%lf",&x);
		A[i]=Complex(x,0.0);
	}
	FFT(m,A,root);
	int end=2*n-1;
	for(int i=1;i<n;++i){
		FT off=n-i,off2=off*off,invOff2=1.0/off2;
		B[i-1]=Complex(-invOff2,0.0);
		B[end-i]=Complex(invOff2,0.0);
	}
	FFT(m,B,root);
	for(int i=0;i<m;++i)
		A[i]*=B[i];
	FFT(m,A,invR);
	int off=n-1;
	for(int i=0;i<n;++i)
		printf("%lf\n",A[i+off].real()/m);
	return 0;
}

