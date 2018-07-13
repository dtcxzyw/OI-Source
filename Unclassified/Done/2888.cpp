#include <cstdio>
#include <cstring>
#include <algorithm>
int dis[301][301];
void CAS(int& a,int b){
	if(a>b)a=b;
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,m,t;
	n=read();
	m=read();
	t=read();
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;++i)
		dis[i][i]=0;
	int u,v,w;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		CAS(dis[u][v],w);
	}
	const int nil=0x3f3f3f3f;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)if(dis[i][k]!=nil)
			for(int j=1;j<=n;++j)if(dis[k][j]!=nil)
				CAS(dis[i][j],std::max(dis[i][k],dis[k][j]));
	for(int i=0;i<t;++i){
		u=read();
		v=read();
		if(dis[u][v]==nil)puts("-1");
		else printf("%d\n",dis[u][v]);
	}
	return 0;
}

