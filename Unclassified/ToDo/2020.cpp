#include <cstdio>
#include <algorithm>
const int size=1000001;
int pos[size]={},fib[6*size];
void calcPos(int k){
	fib[1]=fib[2]=1;
	int i=3;
	do{
		fib[i]=(fib[i-1]+fib[i-2])%k;
		if(pos[fib[i]]==0)pos[fib[i]]=i;
		++i;
	}while(!(fib[i-1]==1 && fib[i-2]==1));
}
void exgcd(int a,int b,int& x,int& y){
	if(b){
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	else x=1,y=0;
}
int calcInv(int a,int k){
	int x,y;
	exgcd(a,k,x,y);
	return (x%k+k)%k;
}
int inv[size];
void preInv(int k){
	for(int i=1;i<k;++i)
		if(inv[i]==0){
			inv[i]=calcInv(i,k);
			inv[inv[i]]=i;
		}
}
typedef long long Int64;
Int64 mod;
struct Mat{
	Int64 val[2][2];
	Mat(){
		val[0][0]=val[0][1]=val[1][0]=val[1][1]=0;
	}
	Int64* operator[](int i){
		return val[i];
	}
	const Int64* operator[](int i) const{
		return val[i];
	}
	Mat operator*(const Mat& rhs) const{
		Mat res;
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
				for(int k=0;k<2;++k)
					res[i][j]=(res[i][j]+val[i][k]*rhs[k][j])%mod;
		return res;
	}
};
Int64 calcFib(int k){
	Mat res,mul;
	res[0][0]=res[1][1]=1;
	mul[0][1]=mul[1][0]=mul[1][1]=1;
	while(k){
		if(k&1)res=res*mul;
		k>>=1,mul=mul*mul;
	}
	return res[0][1];
}
int main(){
	Int64 n,k;
	//scanf("%lld%lld%lld\n",&n,&k,&mod);
	n=6;
	k=7;
	mod=100;
	if(n<=2){
		puts("1");
		return 0;
	}
	calcPos(k);
	preInv(k);
	int now=2;n-=2;
	Int64 res=1;
	while(n){
		int val=inv[now];
		Int64 x=pos[val];
		int len=std::min(n,x);
		res=res*calcFib(len-1)%mod;
		n-=len;
	}
	printf("%lld\n",res);
	return 0;
}

