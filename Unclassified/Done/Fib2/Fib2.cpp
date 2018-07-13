#include <iostream>
#include <memory.h>
using namespace std;
long long p,m;
bool mod=false;
struct Mat2 final{
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
					res.v[i][j]+=v[i][k]*rhs.v[k][j];
		if(mod){
			for(i=0;i<2;++i)
				for(j=0;j<2;++j)
					res.v[i][j]-=(res.v[i][j]%m==1);
		}
		
		for(i=0;i<2;++i)
			for(j=0;j<2;++j)
				res.v[i][j]%=p;
		return res;
	}
};
int main(){
	long long n;
	cin>>n>>m>>p;
	Mat2 res,mul;
	res.v[0][0]=res.v[1][1]=mul.v[0][0]=mul.v[0][1]=mul.v[1][0]=1;
	long long i=1;
	while(n){
		if(n&1)res=res*mul;
		n>>=1,mul=mul*mul;
		i<<=1;
		if(i>3)mod=true;
	}
	cout<<res.v[0][1]<<endl;
	return 0;	
}

