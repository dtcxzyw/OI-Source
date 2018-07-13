#include <cstdio>
#include <cstring>
bool flag[1001][1001];
int cnt[1001][1001]={};
const int mod=100003;
int main(){
	memset(flag,1,sizeof(flag));
	int n,m;
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i=0;i<m;++i){
		scanf("%d%d",&x,&y);
		flag[x][y]=false;
	}
	cnt[1][1]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if((i!=1 || j!=1) && flag[i][j]){
				if(flag[i-1][j] && flag[i][j-1])
					cnt[i][j]=(cnt[i-1][j]+cnt[i][j-1])%mod;
				else if(flag[i-1][j])
					cnt[i][j]=cnt[i-1][j];
				else if(flag[i][j-1])
					cnt[i][j]=cnt[i][j-1];
			}
	printf("%d\n",cnt[n][n]);
	return 0;
}

