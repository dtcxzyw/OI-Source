#include <cstdio>
bool dp[20001]={};
int v[31];
int main(){
	int mv,n,x;
	scanf("%d%d",&mv,&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&v[i]);
	dp[0]=true;
	for(int i=1;i<=n;++i){
		for(int j=mv;j>=v[i];--j)
			dp[j]|=dp[j-v[i]];
	}
	
	for(int i=mv;i>=0;--i)
		if(dp[i]){
			printf("%d\n",mv-i);
			break;
		}
	return 0;
}

