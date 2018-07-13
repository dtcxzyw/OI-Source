#include <cstdio>
long long A[10],B[10];
void exgcd(long long a,long long b,long long& x,long long& y,long long& d){
	if(b){
		exgcd(b,a%b,y,x,d);
		y-=a/b*x;
	}
	else d=a,x=1,y=0;
}
long long clamp(long long a,long long m){
	return (a%m+m)%m;
}
long long inv(long long a,long long m){
	long long d,x,y;
	exgcd(a,m,x,y,d);
	return clamp(x,m);
}
long long mulm(long long a,long long b,long long m){
	long long res=0;
	while(b){
		if(b&1)res=(res+a)%m;
		b>>=1,a=(a<<1)%m;
	}
	return res;
}
int main(){
	int k;
	scanf("%d",&k);
	for(int i=0;i<k;++i)
		scanf("%lld",&A[i]);
	for(int i=0;i<k;++i)
		scanf("%lld",&B[i]);
	long long mul=1;
	for(int i=0;i<k;++i)
		mul*=B[i],A[i]=clamp(A[i],B[i]);
	long long sum=0;
	for(int i=0;i<k;++i){
		long long m=mul/B[i];
		long long c=mulm(m,inv(m,B[i]),mul);
		long long add=mulm(c,A[i],mul);
		sum=clamp(sum+add,mul);
	}
	printf("%lld\n",sum);
	return 0;
}

