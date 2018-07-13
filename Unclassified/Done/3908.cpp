#include <cstdio>
long long calc(long long n){
	long long mod=n%4LL;
	switch(mod){
		case 0:return n;
		case 1:return 1;
		case 2:return n+1;
		case 3:return 0;
	}
}
int main(){
	long long n;
	scanf("%lld",&n);
	printf("%lld\n",calc(n));
	return 0;
}

