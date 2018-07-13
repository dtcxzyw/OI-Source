#include <cstdio>
const int size=500100;
int icnt=0,son[size][2];
void build(int u){
	int c=getchar()-'0';
	for(int i=0;i<c;++i){
		int v=++icnt;
		build(v);
		son[u][i]=v;
	}
}
typedef int(*Func)(int,int);
int maxv(int a,int b){
	return a>b?a:b;
}
int minv(int a,int b){
	return a<b?a:b;
}
int dp[size][3];
const int inv[3][2]={{1,2},{0,2},{0,1}};
#define ls son[u][0]
#define rs son[u][1]
#define lc inv[i][0]
#define rc inv[i][1]
template<Func func>
void DFS(int u){
	if(son[u][1]){
		DFS<func>(ls);
		DFS<func>(rs);
		for(int i=0;i<3;++i)
			dp[u][i]=func(dp[ls][lc]+dp[rs][rc],dp[ls][rc]+dp[rs][lc])+(i==0);
	}
	else if(son[u][0]){
		DFS<func>(ls);
		for(int i=0;i<3;++i)
			dp[u][i]=func(dp[ls][lc],dp[ls][rc])+(i==0);
	}
	else{
		dp[u][0]=1;
		dp[u][1]=dp[u][2]=0;
	}
}
int main(){
	build(++icnt);
	DFS<maxv>(1);
	int maxres=maxv(dp[1][0],maxv(dp[1][1],dp[1][2]));
	DFS<minv>(1);
	int minres=minv(dp[1][0],minv(dp[1][1],dp[1][2]));
	printf("%d %d\n",maxres,minres);
	return 0;
}

