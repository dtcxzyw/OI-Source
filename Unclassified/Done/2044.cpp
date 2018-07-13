#include <cstdio>
#include <cstring>
long long m;
long long mulm(long long a,long long b){
	long long res=0; 
	while(b){
		if(b&1)res=(res+a)%m;
		b>>=1,a=(a<<1)%m;
	}
	return res;
}
struct Mat2{
    long long v[2][2];
    Mat2(){
        memset(v,0,sizeof(v));
    }
    Mat2 operator*(const Mat2& rhs){
        Mat2 res;
        int i,j,k;
        for(i=0;i<2;++i)
            for(j=0;j<2;++j)
                for(k=0;k<2;++k)
                    res.v[i][j]=(res.v[i][j]+mulm(v[i][k],rhs.v[k][j]))%m;
        return res;
    }
};
int main(){
    long long a,c,x,n,g;
    scanf("%lld%lld%lld%lld%lld%lld",&m,&a,&c,&x,&n,&g);
    c%=m,a%=m,x%=m;
    Mat2 ans,mul;
    ans.v[0][0]=x,ans.v[0][1]=c;
    mul.v[0][0]=a,mul.v[1][0]=mul.v[1][1]=1;
    while(n){
        if(n&1)ans=ans*mul;
        mul=mul*mul,n>>=1;
    }
    printf("%lld\n",ans.v[0][0]%g);
    return 0;
}

