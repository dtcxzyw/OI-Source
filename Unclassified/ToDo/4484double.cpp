#include <cstdio>
#include <algorithm>
const int size=30,mod=998244353;
double dp[size][size][size][size][size]={},inv[size];
int main(){
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=1.0/i;
	for(int i=1;i<=n;++i)dp[1][1][i][1][0]=1;
	for(int i=1;i<n;++i)//insert i+1
		for(int j=1;j<=i;++j)
			for(int k=1;k<=n;++k)
				for(int a=1;a<=i;++a)
					for(int b=0;b<a;++b){
						for(int p=b;p<a;++p)
							dp[i+1][j][i+1][p][b]+=dp[i][j][k][a][b];
						for(int p=a;p<=i;++p)
							dp[i+1][j+1][i+1][p][a]+=dp[i][j][k][a][b];
					}
	double res=0.0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int a=1;a<=i;++a)
				for(int b=0;b<a;++b)
					res+=dp[n][i][j][a][b]*i;
	for(int i=1;i<=n;++i)
		res/=i;
	printf("%f\n",float(res));
	printf("%f\n",58.0f/24.0f);
	return 0;
}

