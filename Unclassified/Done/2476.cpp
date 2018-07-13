#include <cstdio>
const int mod=1000000007;
int cnt[6]={},dp[16][16][16][16][16][6]={};
bool flag[16][16][16][16][16][6]={};
int DFS(int x1,int x2,int x3,int x4,int x5,int lx){
	if(!flag[x1][x2][x3][x4][x5][lx]){
		long long res=(x1+x2+x3+x4+x5==0);
		if(x1)res+=1LL*(x1-(lx==2))*DFS(x1-1,x2,x3,x4,x5,1);
		if(x2)res+=1LL*(x2-(lx==3))*DFS(x1+1,x2-1,x3,x4,x5,2);
		if(x3)res+=1LL*(x3-(lx==4))*DFS(x1,x2+1,x3-1,x4,x5,3);
		if(x4)res+=1LL*(x4-(lx==5))*DFS(x1,x2,x3+1,x4-1,x5,4);
		if(x5)res+=1LL*x5*DFS(x1,x2,x3,x4+1,x5-1,5);
		flag[x1][x2][x3][x4][x5][lx]=true;
		dp[x1][x2][x3][x4][x5][lx]=res%mod;
	}
	return dp[x1][x2][x3][x4][x5][lx];
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int x;
		scanf("%d",&x);
		++cnt[x];
	}
	printf("%d",DFS(cnt[1],cnt[2],cnt[3],cnt[4],cnt[5],0));
	return 0;
}

