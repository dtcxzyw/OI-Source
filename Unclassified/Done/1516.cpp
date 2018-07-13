#include <cstdio>
typedef long long LL;
LL exgcd(LL a,LL b,LL &x,LL &y,LL &d){
	if(b){
		exgcd(b,a%b,y,x,d);
		y-=a/b*x;
	}
	else x=1,y=0,d=a;
}
LL clamp(LL a,LL m){
	return (a%m+m)%m;
}
int main(){
	LL x,y,m,n,l;
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l);
	LL a=m-n,b=y-x,X,Y,D;
	exgcd(a,l,X,Y,D);
	if(b%D)puts("Impossible");
	else {
		l/=D;
		printf("%lld\n",clamp(clamp(X,l)*clamp(b/D,l),l));
	}
	return 0;
}

