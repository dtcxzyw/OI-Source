#include <cstdio>
long long p;
struct Mat{
	int n,m,val[20][20];
	Mat(int a,int b):n(a),m(b){
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				val[i][j]=0;
	}
	const int* operator[](int i) const{
		return val[i];
	}
	int* operator[](int i){
		return val[i];
	}
	Mat operator*(const Mat& rhs){
		Mat res(n,rhs.m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=rhs.m;++j)
				for(int k=1;k<=m;++k)
					res[i][j]=(res[i][j]+1LL*val[i][k]*rhs[k][j])%p;
		return res;
	}
};
int b[20],c[20];
long long calc(const Mat& base,const Mat& mul,long long n,int k){
	if(n<=k){
		long long res=0;
		for(int i=1;i<=n;++i)res=(res+b[i])%p;
		return res;
	}
	else{
		long long i=n-k-1;
		Mat pow=mul,ans=mul;
		while(i){
			if(i&1)ans=ans*pow;
			i>>=1,pow=pow*pow;
		}
		ans=ans*base;
		return ans[1][1];
	}
}
int main(){
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;++i)scanf("%d",&b[i]);
	for(int i=1;i<=k;++i)scanf("%d",&c[i]);
	long long m,n;
	scanf("%lld%lld%lld",&m,&n,&p);
	Mat base(k+1,1);
	for(int i=1;i<=k;++i){
		base[i+1][1]=b[k-i+1]%p;
		base[1][1]=(base[1][1]+base[i+1][1])%p;
	}
	Mat mul(k+1,k+1);
	mul[1][1]=1;
	for(int i=1;i<=k;++i)
		mul[1][i+1]=mul[2][i+1]=c[i]%p;
	for(int i=3;i<=k+1;++i)
		mul[i][i-1]=1;
	printf("%lld\n",((calc(base,mul,n,k)-calc(base,mul,m-1,k))%p+p)%p);
	return 0;
}

