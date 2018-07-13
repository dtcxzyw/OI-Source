#include <cstdio>
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
const int size=201;
int link[size][size],cnt[size][size]={};
int main(){
	int n=read();
	int m=read();
	memset(link,0x3f,sizeof(link));
	for(int i=1;i<=n;++i)
		link[i][i]=0,cnt[i][i]=1;
	int u,v;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		link[u][v]=link[v][u]=read();
		cnt[u][v]=cnt[v][u]=1;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)if(i!=k)
			for(int j=1;j<=n;++j)if(i!=j && j!=k){
				int nd=link[i][k]+link[k][j];
				if(nd<link[i][j])link[i][j]=nd,cnt[i][j]=0;
				if(nd==link[i][j])cnt[i][j]+=cnt[i][k]*cnt[k][j];
			}
	bool none=true;
	for(int k=1;k<=n;++k){
		bool flag=false;
		for(int i=1;i<=n && !flag;++i)if(i!=k)
			for(int j=1;j<=n;++j)if(i!=j && j!=k)
				if(link[i][k]+link[k][j]==link[i][j] && cnt[i][k]*cnt[k][j]==cnt[i][j]){
					flag=true;
					break;
				}
		if(flag)printf("%d ",k),none=false;
	}
	if(none)puts("No important cities.");
	return 0;
}

