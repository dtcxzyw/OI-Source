#include <cstdio>
#include <algorithm>
using namespace std;
long long A[100001],s[100001];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	long long l=0,r=0;
	for(int i=1;i<=n;++i){
		scanf("%lld",&A[i]);
		A[i]*=10000;
		r=max(r,A[i]);
	}
	
	s[0]=0;
	while(l<=r){
		int mid=(l+r)>>1;
		bool flag=false;
		long long minv=0;
		for(int i=1;i<=n;++i){
			s[i]=s[i-1]+A[i]-mid;
			if(i>=m){
				minv=min(minv,s[i-m]);
				if(s[i]>=minv){
					flag=true;
					break;
				}
			}
		}
		if(flag)l=mid+1;
		else r=mid-1;
	}
	
	printf("%lld\n",l/10);
	return 0;
}

