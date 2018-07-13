#include <cstdio>
#include <algorithm>
long long sum[100001]={};
int main(){
	int n,w;
	scanf("%d%d",&n,&w);
	int p,b,maxp=0;
	for(int i=0;i<n;++i){
		scanf("%d%d",&p,&b);
		sum[p]+=b;
		maxp=std::max(maxp,p);
	}
	for(int i=1;i<=maxp;++i)sum[i]+=sum[i-1];
	long long ans=0;
	for(int i=1;i<=maxp-w;++i)ans=std::max(ans,sum[i+w]-sum[i]);
	printf("%lld\n",ans);
	return 0;
}

