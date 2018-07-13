#include <cstdio>
long long f[100001];
int main(){
    long long n,m,ans=0;
    scanf("%lld%lld",&n,&m);
    int maxv=n>m?n:m,minv=n<m?n:m;
    for(int i=minv;i>=1;--i){
    	f[i]=(n/i)*(m/i);
    	for(int j=i<<1;j<=maxv;j+=i)f[i]-=f[j];
    	ans+=f[i]*i;
	}
	ans+=ans-m*n;
    printf("%lld\n",ans);
	return 0;
}

