#include <cstdio>
#include <cstring>
int dis[101][101];
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	memset(dis,0x3f,sizeof(dis));
	int k,u;
	for(int i=1;i<=n;++i){
		scanf("%d",&k);
		for(int j=1;j<=k;++j){
			scanf("%d",&u);
			dis[i][u]=(j!=1);
		}
	}
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			if(dis[i][k]!=0x3f3f3f3f)
				for(int j=1;j<=n;++j)
					if(dis[i][j]>dis[i][k]+dis[k][j])
						dis[i][j]=dis[i][k]+dis[k][j];
	if(dis[a][b]!=0x3f3f3f3f)
		printf("%d\n",dis[a][b]);
	else
		puts("-1");
	return 0;
}

