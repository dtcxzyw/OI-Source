#include <cstdio>
#include <cstring>
const int size=50;
const long long maxv=1LL<<62;
int mod;
struct Mat{
	int n,m,val[size][size];
	Mat(){}
	Mat(int n,int m):n(n),m(m){}
	void clear(){
		memset(val,0,sizeof(val));
	}
	int* operator[](int i){
		return val[i];
	}
	const int* operator[](int i) const{
		return val[i];
	}
	Mat operator*(const Mat& rhs) const{
		Mat res(n,rhs.m);
		for(int i=0;i<n;++i)
			for(int j=0;j<rhs.m;++j){
				long long sum=0;
				for(int k=0;k<m;++k){
					sum+=static_cast<long long>(val[i][k])*rhs.val[k][j];
					if(sum>=maxv)sum%=mod;
				}
				res[i][j]=sum%mod;
			}
		return res;
	}
};
Mat res,mul;
int main(){
	int A,n;
	scanf("%d%d%d",&A,&n,&mod);
	res.n=1,res.m=n+1;
	res.clear();
	res[0][0]=1;
	for(int i=1;i<=A;++i){
		mul.n=mul.m=n+1;
		mul.clear();
		for(int j=0;j<=n;++j){
			mul[j][j]=1;
			mul[j][j+1]=i;
		}
		res=res*mul;
	}
	long long ans=res[0][n];
	for(int i=1;i<=n;++i)ans=ans*i%mod;
	printf("%d\n",static_cast<int>(ans));
	return 0;
}

