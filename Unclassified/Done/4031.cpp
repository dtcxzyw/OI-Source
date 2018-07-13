#include <cstdio>
typedef long long Int64;
Int64 read(){
	Int64 res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
struct Mat{
	Int64 val[2][2];
	Mat(){
		val[0][0]=val[0][1]=val[1][0]=val[1][1]=0;
	}
	const Int64* operator[](int i) const{
		return val[i];	
	}
	Int64* operator[](int i){
		return val[i];	
	}
};
Int64 p;
Mat operator*(const Mat& lhs,const Mat& rhs){
	Mat res;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k)
				res[i][j]=(res[i][j]+lhs[i][k]*rhs[k][j])%p;
	return res;
}
void exgcd(Int64 a,Int64 b,Int64& d,Int64& x,Int64& y){
	if(b){
		exgcd(b,a%b,d,y,x);
		y-=a/b*x;
	}
	else d=a,x=1,y=0;
}

Int64 foo(){
	Int64 a1=read();
	Int64 l=read();
	Int64 r=read();
	Int64 k=read()-2;
	p=read();
	Int64 m=read();
	Mat ans,mul;
	ans[0][0]=ans[1][1]=mul[0][1]=mul[1][0]=mul[1][1]=1;
	while(k){
		if(k&1)ans=ans*mul;
		k>>=1,mul=mul*mul;
	}
	Int64 ka=ans[1][0],kb=ans[1][1];
	Int64 rhand=(m%p-ka*(a1%p)%p+p)%p;
	Int64 d,x,y;
	exgcd(kb,p,d,x,y);
	if(rhand%d)return 0;
	else{
		Int64 x0=x*(rhand/d),step=p/d;
		l-=x0,r-=x0;
		Int64 p0=l/step*step;
		if(p0<l)p0+=step;
		if(r<p0)return 0;
		return (r-p0)/step+1;
	}
}
int main(){
	int t=read();
	for(int i=0;i<t;++i)printf("%lld\n",foo());
	return 0;
}

