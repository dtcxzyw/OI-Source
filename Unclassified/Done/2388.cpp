#include <cstdio>
int main(){
	int n;
	scanf("%d",&n);
	long long cnt=0,ans=0;
	for(int i=1;i<=n;++i){
		int x=i;
		while(x%5==0)++cnt,x/=5;
		ans+=cnt;
	}
	printf("%lld\n",ans);
	return 0;
}

