#include <cstdio>
#include <cstring>
typedef long long Int64;
const Int64 size=310,maxc=size*size/2,maxv=1LL<<45;
Int64 dp[size][maxc],sum[2][maxc];
Int64 clamp(Int64 a){
	return a<maxv?a:maxv;
}
Int64 get(Int64 i,Int64 j){
	Int64 end=i*(i-1)/2;
	return sum[i&1][j<end?j:end];
}
bool flag[size]={};
int main(){
	Int64 n,k,x;
	scanf("%lld%lld%lld",&n,&k,&x);
	dp[1][0]=sum[1][0]=1;
	for(int i=2;i<=n;++i){
		int cnt=i*(i-1)/2;
		memset(sum[i&1],0,sizeof(sum[i&1]));
		for(int j=0;j<=cnt;++j){
			dp[i][j]=clamp(get(i-1,j)-(j>=i?get(i-1,j-i):0));
			sum[i&1][j]=(j?sum[i&1][j-1]:0)+dp[i][j];
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)if(!flag[j]){
			int cnt=0;
			for(int p=1;p<j;++p)if(!flag[p])++cnt;
			Int64 val=dp[n-i][x-cnt];
			if(k>val && i!=n)k-=val;
			else{
				x-=cnt;
				flag[j]=true;
				printf("%d ",j);
				break;
			}
		}
	return 0;
}

