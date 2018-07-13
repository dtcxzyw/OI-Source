#include <cstdio>
#include <cstring>
bool dp[2][100];
int clamp(int x,int k){
	return (x%k+k)%k;
}
bool foo(){
	memset(dp,0,sizeof(dp));
	int n,k;
	scanf("%d%d",&n,&k);
	int c=0,x;
	scanf("%d",&x);
	dp[c][clamp(x,k)]=true;
	for(int i=1;i<n;++i){
		memset(dp[1-c],0,sizeof(dp[1-c]));
		scanf("%d",&x);
		for(int i=0;i<k;++i)
			if(dp[c][i])
				dp[1-c][clamp(i+x,k)]=dp[1-c][clamp(i-x,k)]=true;
		c=1-c;
	}
	return dp[c][0];
}
int main(){
	int m;
	scanf("%d",&m);
	while(m--)
		puts(foo()?"Divisible":"Not divisible");
	return 0;
}

