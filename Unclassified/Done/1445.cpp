#include <cstdio>
#include <vector>
const long long mod=1000000007LL;
int prime[100000],pcnt=0;
bool flag[1000001]={};
bool test(int x){
	for(int i=0;i<pcnt;++i)
		if(x%prime[i]==0)
			return false;
	return true;
}
int main(){
	int n;
	scanf("%d",&n);
	
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[pcnt++]=i;
		for(int j=0;j<pcnt && 1LL*i*prime[j]<=n;++j){
			flag[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
	
	long long res=1;
	for(int i=0;i<pcnt;++i){
		long long cnt=0;
		for(long long j=prime[i];j<=n;j*=prime[i])
			cnt=(cnt+n/j)%mod;
		cnt=(cnt<<1|1)%mod;
		res=(res*cnt)%mod;
	}
	printf("%lld\n",res);
	return 0;
}

