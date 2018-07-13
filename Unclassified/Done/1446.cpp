#include <cstdio>
#include <cstring>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=70;
int to[size][size];
int inv(int a,int p){
	int k=p-2,res=1;
	while(k){
		if(k&1)res=res*a%p;
		k>>=1,a=a*a%p;
	}
	return res;
}
int dp[21][21][21],cnt[size];
bool flag[size];
int foo(int n,int c,int p,int sr,int sg,int sb){
	memset(dp,0,sizeof(dp));
	memset(cnt,0,sizeof(cnt));
	memset(flag,0,sizeof(flag));
	int sum=0;
	for(int i=1;i<=n;++i)
		if(!flag[i]){
			int p=i;
			++sum;
			while(!flag[p]){
				flag[p]=true;
				++cnt[sum];
				p=to[c][p];
			}
		}
	dp[0][0][0]=1;
	for(int i=1;i<=sum;++i)
		for(int r=sr;r>=0;--r)
			for(int g=sg;g>=0;--g)
				for(int b=sb;b>=0;--b){
					if(r>=cnt[i])dp[r][g][b]=(dp[r][g][b]+dp[r-cnt[i]][g][b])%p;
					if(g>=cnt[i])dp[r][g][b]=(dp[r][g][b]+dp[r][g-cnt[i]][b])%p;
					if(b>=cnt[i])dp[r][g][b]=(dp[r][g][b]+dp[r][g][b-cnt[i]])%p;
				}
	return dp[sr][sg][sb];
}
int main(){
	int r=read();
	int g=read();
	int b=read();
	int n=r+g+b;
	int m=read();
	int p=read();
	for(int i=0;i<m;++i)
		for(int j=1;j<=n;++j)
			to[i][j]=read();
	for(int i=1;i<=n;++i)to[m][i]=i;
	int ans=0;
	for(int i=0;i<=m;++i)
		ans=(ans+foo(n,i,p,r,g,b))%p;
	ans=(ans*inv(m+1,p))%p;
	printf("%d\n",ans);
	return 0;
}

