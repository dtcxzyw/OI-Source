#include <cstdio>
int main(){
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	long long a,b;
	scanf("%lld%lld",&a,&b);
	long long ans=a*b-a-b;
	printf("%lld\n",ans);
	return 0;
}

