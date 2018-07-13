#include <cstdio>
const int mod=19260817;
const long long end=1LL<<58;
int read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		if(res>=end)res%=mod;
		c=getchar();
	}
	return res%mod;
}
long long inv(long long a){
	long long res=1;
	int k=mod-2;
	while(k){
		if(k&1)res=res*a%mod;
		k>>=1,a=a*a%mod;
	}
	return res;
}
int main(){
	int a=read();
	int b=read();
	if(b)printf("%lld\n",a*inv(b)%mod);
	else puts("Angry!");
	return 0;
}

