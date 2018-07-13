#include <cstdio>
#include <vector>
long long dp[1<<16][16]={};
int id[16],bcnt[1<<16];
std::vector<int> st[17];
int iabs(int x){
	return x>0?x:-x;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i){
		scanf("%d",&id[i]);
		dp[1<<i][i]=1;
	}
	int end=1<<n;
	for(int i=1;i<end;++i)
		bcnt[i]=bcnt[i>>1]+(i&1);
	for(int i=1;i<end;++i)
		st[bcnt[i]].push_back(i); 
	for(int i=2;i<=n;++i){
		for(int j=0;j<st[i].size();++j){
			int dst=st[i][j];
			for(int x=0;x<n;++x)
				if(dst&(1<<x)){
					int src=dst^(1<<x);
					for(int y=0;y<n;++y)if(iabs(id[x]-id[y])>k)
						dp[dst][x]+=dp[src][y];
				}
		}
	}
	long long ans=0;
	for(int i=0;i<n;++i)
		ans+=dp[end-1][i];
	printf("%lld\n",ans);
	return 0;
}

