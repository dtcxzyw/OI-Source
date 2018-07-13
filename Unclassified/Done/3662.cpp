#include <cstdio>
#include <algorithm>
int sum[100001]={};
int main(){
	int n,k,b,x;
	scanf("%d%d%d",&n,&k,&b);
	for(int i=0;i<b;++i){
		scanf("%d",&x);
		sum[x]=1;
	}
	for(int i=1;i<=n;++i)
		sum[i]+=sum[i-1];
	int minv=100001;
	for(int i=k;i<=n;++i)
		minv=std::min(minv,sum[i]-sum[i-k]);
	printf("%d\n",minv);
	return 0;
}

