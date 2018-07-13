#include <cstdio>
#include <cstring>
#include <algorithm>
struct Student{
	int a,b;
	bool operator<(Student rhs) const{
		return rhs.b<b;
	}
} A[201];
void CAS(int& a,int b){
	if(a>b)a=b;
}
int dp[2][40011];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&A[i].a,&A[i].b);
	std::sort(A+1,A+n+1);
	dp[0][0]=0;
	int c,l,t=0;
	for(int i=1;i<=n;++i){
		c=i&1,l=1-c;
		memset(dp[c],0x3f,sizeof(dp[c]));
		for(int j=0;j<=t;++j){
			CAS(dp[c][j+A[i].a],std::max(dp[l][j],j+A[i].a+A[i].b));
			CAS(dp[c][j],std::max(dp[l][j],A[i].a+A[i].b+t-j));
		}
		t+=A[i].a;
	}
	int ans=1<<30;
	for(int i=0;i<=t;++i)
		CAS(ans,dp[c][i]);
	printf("%d\n",ans);
	return 0;
}

