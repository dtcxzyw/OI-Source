#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=251;
int w[size],dis[size][size],maxv[size][size];
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
	int n,m,q;
	n=read();
	m=read();
	q=read();
	for(int i=1;i<=n;++i)w[i]=read();
	memset(dis,0x3f,sizeof(dis));
	memset(maxv,0x3f,sizeof(maxv));
	for(int i=1;i<=n;++i)
		dis[i][i]=0,maxv[i][i]=w[i];
	int u,v,c;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		c=read();
		CAS(dis[u][v],c);
		CAS(dis[v][u],c);
		maxv[u][v]=maxv[v][u]=std::max(w[v],w[u]);
	}
	while(true){
		bool flag=true;
		for(int k=1;k<=n;++k)
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j){
					int d=dis[i][k]+dis[k][j]+std::max(maxv[i][k],maxv[k][j]);
					if(d<dis[i][j]+maxv[i][j] && dis[i][k]!=0x3f3f3f3f && dis[k][j]!=0x3f3f3f3f){
						dis[i][j]=dis[i][k]+dis[k][j];
						maxv[i][j]=std::max(maxv[i][k],maxv[k][j]);
						flag=false;
					}
				}
		if(flag)break;
	}
	for(int i=0;i<q;++i){
		scanf("%d%d",&u,&v);
		printf("%d\n",dis[u][v]+maxv[u][v]);
	}
	return 0;
}

