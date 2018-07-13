#include <cstdio>
#include <cstring>
const long long mod=1000000000LL;
const long long out=100000000LL;
struct Mat2{
    long long v[2][2];
    Mat2(){
        memset(v,0,sizeof(v));
    }
    Mat2 operator*(const Mat2& rhs) const{
        Mat2 res;
        int i,j,k;
        for(i=0;i<2;++i)
            for(j=0;j<2;++j)
                for(k=0;k<2;++k)
                    res.v[i][j]=(res.v[i][j]+(v[i][k]*rhs.v[k][j])%mod)%mod;
        return res;
    }
};
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    n=gcd(n,m);
    bool flag=n>39;
    Mat2 ans,mul;
    ans.v[0][0]=ans.v[1][1]=1;
    mul.v[0][0]=mul.v[0][1]=mul.v[1][0]=1;
    while(n){
        if(n&1)ans=ans*mul;
        mul=mul*mul,n>>=1;
    }
    long long res=ans.v[0][1];
    if(flag)
        printf("%08lld",res%out);
    else
        printf("%lld",res);
    return 0;
}

