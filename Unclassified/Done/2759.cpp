#include <cstdio>
#include <cmath>
int main(){
	int n;
	scanf("%d",&n);
	--n;
	long long l=1,r=1LL<<60,ans;
	while(l<=r){
		long long mid=(l+r)>>1;
		if(mid*log10(1.0l+mid)>=n)ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}

