#include <cstdio>
int f[10001];
const int mod=10000;
int powm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		b>>=1,a=a*a%mod;
	}
	return res;
}
void foo(){
	int a,b;
	scanf("%d%d",&a,&b);
	f[0]=0;
	for(int i=1;i<=10000;++i)
		f[i]=(f[i-1]+powm(i,b))%mod;
	int res=(f[a%mod]+f[10000]*(a/mod)%mod)%mod;
	printf("%d\n",res);
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--)foo();
	return 0;
}

