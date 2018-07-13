#include <cstdio>
#include <cstring>
#include <algorithm>
int A[1001][2],dp[2][13001],maxd[6001];
int main(){
	int n;
	scanf("%d",&n);
	int maxv=0,minv=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&A[i][0],&A[i][1]);
		maxv+=std::max(A[i][0],A[i][1]);
		minv+=std::min(A[i][0],A[i][1]);
		maxd[i]=maxv-minv;
	}
	
	memset(dp,0x3f,sizeof(dp));
	const int off=6500;
	dp[0][off]=0;
	int c,l;
	for(int i=1;i<=n;++i){
		c=i&1,l=1-c;
		memset(dp[c],0x3f,sizeof(dp[c]));
		for(int j=-maxd[i];j<=maxd[i];++j){
			int x=j+off,d=A[i][0]-A[i][1];
			dp[c][x]=std::min(dp[l][x+d],dp[l][x-d]+1);
		}
	}
	
	int ans=0x3f3f3f3f;
	for(int i=0;i<=maxd[n];++i){
		ans=std::min(dp[c][off-i],dp[c][off+i]);
		if(ans!=0x3f3f3f3f)break;
	}
	printf("%d\n",ans);
	return 0;
}

