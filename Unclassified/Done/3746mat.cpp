#include <cstdio>
#include <cstring>
long long p;
struct Mat{
	long long v[50][50];
	int r,c;
	Mat(int _r,int _c):r(_r),c(_c){
		memset(v,0,sizeof(v));
	}
	Mat operator*(const Mat& rhs){
		Mat res(r,rhs.c);
		for(int i=0;i<r;++i)
			for(int j=0;j<rhs.c;++j)
				for(int k=0;k<c;++k)
					res.v[i][j]=(res.v[i][j]+1LL*v[i][k]*rhs.v[k][j])%p;
		return res;
	}
};
int main(){
	long long n,k,r;
	scanf("%lld%lld%lld%lld",&n,&p,&k,&r);
	Mat res(1,k),mul(k,k);
	res.v[0][0]=1;
	for(int i=0;i<k;++i){
		mul.v[i][i]=1;
		++mul.v[i][(i+1)%k];
	}
	k*=n;
	while(k){
		if(k&1)res=res*mul;
		k>>=1,mul=mul*mul;
	}
	printf("%lld\n",res.v[0][r]);
	return 0;
}

