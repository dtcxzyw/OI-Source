#include <cstdio>
#include <algorithm>
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
int mat[501][501],l[501],r[501];
bool flag[501][501]={};
const int off[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int n,m,now;
void color(int x,int y){
	if(flag[x][y])return;
	if(x==n)l[now]=std::min(l[now],y),r[now]=std::max(r[now],y);
	flag[x][y]=true;
	for(int i=0;i<4;++i){
		int dx=x+off[i][0],dy=y+off[i][1];
		if(dx>0 && dy>0 && dx<=n && dy<=m && mat[x][y]>mat[dx][dy])color(dx,dy);
	}
}
int dp[501];
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			mat[i][j]=read();
	for(int i=1;i<=m;++i)color(1,i);
	int cnt=0;
	for(int i=1;i<=m;++i)
		if(!flag[n][i])++cnt;
	if(cnt)printf("0\n%d\n",cnt);
	else{
		for(now=1;now<=m;++now){
			l[now]=m,r[now]=1;
			memset(flag,0,sizeof(flag));
			color(1,now);
		}
		memset(flag,0,sizeof(flag));
		memset(dp,0x3f,sizeof(dp));
		for(int i=1;i<=m;++i)
			for(int j=l[i];j<=r[i];++j)
				for(int k=j;k<=r[i];++k){
					flag[j][k]=true;
					if(j==1)dp[k]=1;
				}
		for(int i=1;i<=m;++i)
			for(int j=1;j<i;++j)
				if(flag[j+1][i])
					dp[i]=std::min(dp[i],dp[j]+1);
		printf("1\n%d\n",dp[m]);
	}
	return 0;
}

