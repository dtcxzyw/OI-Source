#include <cstdio>
double dp[101][1<<15]={};
int w[15],mask[15]={};
double maxv(double a,double b){
	return a>b?a:b;
}
int main(){
	int k,n;
	scanf("%d%d",&k,&n);
	int end=1<<n;
	for(int i=0;i<n;++i){
		scanf("%d",&w[i]);
		int x;
		while(true){
			scanf("%d",&x);
			if(x)mask[i]|=1<<(x-1);
			else break;
		}
	}
	for(int i=k-1;i>=0;--i)
		for(int j=0;j<end;++j){
			for(int x=0;x<n;++x)
				if((mask[x]|j)==j)dp[i][j]+=maxv(dp[i+1][j],dp[i+1][j|(1<<x)]+w[x]);
				else dp[i][j]+=dp[i+1][j];
				
			dp[i][j]/=n;
		}
	printf("%.6lf\n",dp[0][0]);
	return 0;
}

