#include <cstdio>
#include <algorithm>
using namespace std;
long long A[100001],ms[100001];
int msp[100001];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	A[0]=0,ms[0]=2000LL*100000LL;
	for(int i=1;i<=n;++i)
		scanf("%lld",&A[i]);

	long long maxv=0LL;
	int p=0;
	for(int i=1;i<=n;++i){
		A[i]+=A[i-1];
		if(ms[i-1]<A[i])
			ms[i]=ms[i-1],msp[i]=msp[i-1];
		else
			ms[i]=A[i],msp[i]=i;
		if(i>=m)
			maxv=max(maxv,(A[i]-ms[i-m])*1000/(i-msp[i-m]));
	}
	
	printf("%lld\n",maxv);
	return 0;
}

