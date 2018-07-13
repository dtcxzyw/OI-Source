#include <cstdio>
#include <complex>
#include <cmath>
using c=std::complex<double>;
constexpr int maxn=1<<21;
constexpr double pi=acos(-1.0);
c A[maxn],B[maxn];
int getInt(){
    int res=0,c;
    do c=getchar();
    while(c<'0' || c>'9');
    while(c>='0' && c<='9'){
        res=res*10+c-'0';
        c=getchar();
    }
    return res;
}
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
int main(){
    int n,m;
    n=getInt();m=getInt();
    for(int i=0;i<=n;++i)A[i]=getInt();
    for(int i=0;i<=m;++i)B[i]=getInt();
    int size=1,bit=0;
    while(n+m+1>size)size<<=1,++bit;
    for(int i=0;i<size;++i)
        rev[i]=(rev[i>>1]>>1) | ((i&1)<<(bit-1));
    FFT(A,1,size);
    FFT(B,1,size);
    for(int i=0;i<size;++i)
        A[i]*=B[i];
    FFT(A,-1,size);
    for(int i=0;i<n+m+1;++i)
        printf("%d ",static_cast<int>(A[i].real()/size+0.5));
    return 0;
}

