#include <iostream>
#include <memory.h>
using namespace std;
long long m;
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
					res.v[i][j]=(res.v[i][j]+(v[i][k]*rhs.v[k][j])%m)%m;
		return res;
	}
};
int main(){
	long long p,q,a1,a2,n;
	cin>>p>>q>>a1>>a2>>n>>m;
	if(n==1){
		cout<<a1%m<<endl;
		return 0;
	}
	Mat2 res,mul;
	res.v[0][0]=(p*a2%m+q*a1%m)%m,res.v[1][1]=a1,res.v[0][1]=res.v[1][0]=a2;
	mul.v[0][0]=p,mul.v[0][1]=1,mul.v[1][0]=q;
	n-=2;
	while(n){
		if(n&1)res=res*mul;
		n>>=1,mul=mul*mul;
	}
	cout<<res.v[0][1]<<endl;
	return 0;	
}

