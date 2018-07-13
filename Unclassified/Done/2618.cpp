#include <cstdio>
#include <algorithm>
using namespace std;
const int size=1000001;
int prime[100001],pcnt=1;
bool isPrime(int x){
	for(int i=2;i*i<=x;++i)
		if(x%i==0)return false;
	return true;
}
void foo(int n){
	prime[0]=2;
	for(int i=3;i<=n;i+=2)
		if(isPrime(i))
			prime[pcnt++]=i;
}
int input[size],icnt=0,dp[size];
int main(){
	while(scanf("%d",&input[icnt])!=EOF)++icnt;
	int n=0;
	for(int i=0;i<icnt;++i)
		n=std::max(n,input[i]);
	foo(n);
	dp[1]=0;
	for(int i=2;i<=n;++i){
		dp[i]=dp[i-1]+1;
		for(int j=0;j<pcnt;++j)
			if(i%prime[j]==0)
				dp[i]=std::min(dp[i],dp[i/prime[j]]+1);
	}
	for(int i=0;i<icnt;++i)
		printf("%d\n",dp[input[i]]);
	return 0;
}

