#include <cstdio>
#include <cstring>
long long dis[51][51];
bool link[65][51][51]={};
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
int main(){
	int n,m;
	n=read();
	m=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		link[0][u][v]=true;
	}
	for(int k=1;k<=64;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(link[k-1][i][j])
					for(int l=1;l<=n;++l)
						link[k][i][l]|=link[k-1][j][l];
	memset(dis,0x3f,sizeof(dis));
	for(int k=0;k<=64;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(link[k][i][j])
					dis[i][j]=1;
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(dis[i][j]>dis[i][k]+dis[k][j])
					dis[i][j]=dis[i][k]+dis[k][j];
	printf("%lld\n",dis[1][n]);
	return 0;
}

