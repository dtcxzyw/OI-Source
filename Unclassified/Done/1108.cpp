#include <cstdio>
#include <algorithm>
int w[5001],dp[5001]={},c[5001]={};
int main(){
	int n;
	scanf("%d",&n);
	w[0]=2147483647;
	for(int i=1;i<=n;++i)
		scanf("%d",&w[i]);
	int ans=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j)
			if(w[i]<w[j])
				dp[i]=std::max(dp[i],dp[j]+1);
		ans=std::max(ans,dp[i]);
	}
	
	c[0]=1;
	int sum=0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<i;++j){
			if(dp[i]==dp[j]+1&&w[i]<w[j])c[i]+=c[j];
			if(dp[i]==dp[j]&&w[i]==w[j])c[j]=0;
		}
	
	for(int i=1;i<=n;++i)
		if(dp[i]==ans)
			sum+=c[i];
	
	printf("%d %d\n",ans,sum);	
	return 0;
}

