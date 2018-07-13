#include <cstdio>
#include <algorithm>
struct Cow{
	int t,w;
	bool operator<(Cow rhs) const{
		return t<rhs.t;
	}
} cow[10000];
int dp[2][10001]={};
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&cow[i].w,&cow[i].t);
	std::sort(cow,cow+n);
	bool now=true,last=false;
	for(int i=0;i<n;++i){
		now=!now,last=!last;
		for(int j=0;j<cow[i].t;++j)
			dp[now][j+1]=std::max(dp[now][j+1],std::max(dp[last][j+1],dp[last][j]+cow[i].w));
	}
	int ans=0;
	for(int i=1;i<=10000;++i)
		ans=std::max(ans,dp[now][i]);
	printf("%d\n",ans);
	return 0;
}

