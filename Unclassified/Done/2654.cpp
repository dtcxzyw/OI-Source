#include <cstdio>
#include <queue>
#include <cstring>
int A[21],s[21],dp[21][21];
int foo(int m){
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=m;++i)A[i+m]=A[i];
	for(int i=1;i<=2*m;++i)dp[i][i]=0,s[i]=s[i-1]+A[i];
	for(int i=2;i<=m;++i)
		for(int l=1;l<=m;++l){
			int r=l+i-1;
			for(int k=l;k<r;++k)
				dp[l][r]=std::min(dp[l][r],dp[l][k]+dp[k+1][r]+s[r]-s[l-1]);
		}
	int res=1<<30;
	for(int i=1;i<=m;++i)
		res=std::min(res,dp[i][i+m-1]);
	return res;
}
int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	std::priority_queue<int,std::vector<int>,std::greater<int> > q;
	int x;
	for(int i=0;i<n;++i){
		scanf("%d",&x);
		q.push(x); 
	}
	int ans=0;
	for(int i=0;i<k;++i){
		for(int j=0;j<m;++j){
			scanf("%d",&x);
			A[x]=q.top();
			q.pop();
		}
		ans+=foo(m);
		q.push(s[m]); 
	}
	printf("%d\n",ans);
	return 0;
}

