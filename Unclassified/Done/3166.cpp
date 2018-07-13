#include <cstdio>
long long C(long long n){
	return n*(n-1)*(n-2)/6;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	++n,++m;
	long long res=C(n*m)-n*C(m)-m*C(n);
	for(int i=1;i<n;++i)
		for(int j=1;j<m;++j){
			int x=gcd(i,j)-1;
			if(x)res-=2LL*(n-i)*(m-j)*x;
		}
	printf("%lld\n",res);
	return 0;
}

