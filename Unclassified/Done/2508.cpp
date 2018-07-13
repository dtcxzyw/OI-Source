#include <cstdio>
#include <cmath>
long long gcd(long long a,long long b){
	return b?gcd(b,a%b):a;
}
long long ans=0;
void calc(long long d){
	long long end=d>>1;
	long long last=0;
	for(long long a=1;a*a<=end;++a){
		long long a2=a*a,b=sqrt(d-a2),b2=b*b;
		if(a!=b && b!=last && a2+b2==d && gcd(a2,b2)==1){
			++ans;
			last=b;
		}
	}
}
int main(){
	long long r;
	scanf("%lld",&r);
	long long end=2*r;
	for(long long i=1;i*i<=end;++i)
		if(end%i==0){
			calc(end/i);
			if(end/i!=i)calc(i);
		}
	printf("%lld\n",(ans+1)<<2);
	return 0;
}

