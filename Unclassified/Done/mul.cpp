#include <cstdio>
#include <complex>
#include <cmath>
#include <algorithm>
using c=std::complex<double>;
constexpr int maxn=1<<17;
constexpr double pi=acos(-1.0);
c A[maxn],B[maxn];
int rev[maxn];
void FFT(c* num,int fac,int size){
    for(int i=0;i<size;++i)
        if(i<rev[i])
            std::swap(num[i],num[rev[i]]);
    for(int i=1;i<size;i<<=1){
        auto x=pi/i;
        c wm(cos(x),fac*sin(x));
        for(int k=0,off=i<<1;k<size;k+=off){
            c w=1.0;
            for(int j=0;j<i;++j,w*=wm){
                c t=w*num[k+j+i],u=num[k+j];
                num[k+j]=u+t;
                num[k+j+i]=u-t;
            }       
        }
    }
}
void getInt(c* res){
	int c,i=0;
    do c=getchar();
    while(c<'0' || c>'9');
    while(c>='0' && c<='9'){
        res[i]=c-'0';
        c=getchar(),++i;
    }
}
int res[maxn]={};
int main(){
    int n;
    scanf("%d",&n);
    getInt(A);
    std::reverse(A,A+n);
    getInt(B);
    std::reverse(B,B+n);
    n<<=1;
    int size=1,bit=0;
    while(n>size)size<<=1,++bit;
    for(int i=0;i<size;++i)
        rev[i]=(rev[i>>1]>>1) | ((i&1)<<(bit-1));
    FFT(A,1,size);
    FFT(B,1,size);
    for(int i=0;i<size;++i)
        A[i]*=B[i];
    FFT(A,-1,size);
	int x=0;
	for(int i=0;i<n;++i){
		x+=static_cast<int>(A[i].real()/size+0.5);
		res[i]=x%10;
		x/=10;
	}
	int b=n;
	while(!res[b])--b;
	for(;b>=0;--b)
	    putchar(res[b]+'0');
    return 0;
}

