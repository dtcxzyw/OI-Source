#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=185;
typedef long long Int64;
const Int64 maxv=1LL<<62;
#define asInt64(x) static_cast<long long>(x)
int mod;
struct Mat{
	int n,m,v[size][size];
	Mat(int n,int m):n(n),m(m){
		memset(v,0,sizeof(v));
	}
	int* operator[](int i){
		return v[i];
	}
	const int* operator[](int i) const{
		return v[i];
	}
	Mat operator*(const Mat& rhs) const{
		Mat res(n,rhs.m);
		for(int i=0;i<n;++i)
			for(int j=0;j<rhs.m;++j){
				Int64 sum=0;
				for(int k=0;k<m;++k){
					sum+=asInt64(v[i][k])*rhs[k][j];
					if(sum>=maxv)sum%=mod;
				}
				res[i][j]=sum%mod;
			}
		return res;
	}
};
int C[size][size]={};
Int64 powv[size];
int main(){
	int n,a,b;
	scanf("%d%d%d%d",&n,&a,&b,&mod);
	int c=a+b+1,d=2*c;
	
	C[0][0]=1;
	for(int i=1;i<c;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	powv[0]=1;
	for(int i=1;i<=a;++i)
		powv[i]=powv[i-1]*n%mod;
		
	Mat mul(d,d);
	for(int i=0;i<c;++i){
		//0->0
		mul[i][i]=1;
		//1->0
		mul[i+c][i]=1;
		//0->1
		for(int j=i;j<c;++j)
			mul[i][j+c]=C[j][i];
	}
	
	Mat ans(1,d);
	ans[0][0]=1;
	while(n){
		if(n&1)ans=ans*mul;
		n>>=1,mul=mul*mul;
	}
	
	int res=0;
	for(int i=0;i<=a;++i){
		int p=a+b-i;
		Int64 fac=C[a][i]*((a-i)&1?-1:1)*powv[i]%mod;
		Int64 cnt=(ans[0][p]+ans[0][p+c])%mod;
		res=(res+cnt*fac)%mod;
	}
	printf("%d\n",(res+mod)%mod);
	return 0;
}

