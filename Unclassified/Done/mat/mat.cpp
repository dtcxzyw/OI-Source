#include <cstdio>
#include <memory.h>
constexpr long long mod=1000000007LL;
struct Mat3 final{
	long long v[3][3];
	Mat3(){
		memset(v,0,sizeof(v));
	}
	Mat3 operator*(const Mat3& rhs){
		Mat3 res;
		int i,j,k;
		for(i=0;i<3;++i)
			for(j=0;j<3;++j)
				for(k=0;k<3;++k)
					res.v[i][j]=(res.v[i][j]+(v[i][k]*rhs.v[k][j])%mod)%mod;
		return res;
	}
};
int main(){
	int n,T;
	scanf("%d",&T);
	while(T){
		scanf("%d",&n);
		--n;
		Mat3 ans,mul;
		mul.v[0][0]=mul.v[0][1]=mul.v[1][2]=mul.v[2][0]=1;
		ans.v[0][0]=ans.v[1][1]=ans.v[2][2]=1;
		while(n){
			if(n&1)ans=ans*mul;
			mul=mul*mul,n>>=1;
		}
		printf("%d\n",static_cast<int>(ans.v[0][0]));
		--T;
	}
	return 0;
}

