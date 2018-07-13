#include <cstdio>
#include <cstring>
const int size=201;
struct Edge{
	int to,next,w;
} E[2][80010];
int last[2][size]={},cnt[2]={};
void addEdge(int u,int v,int w,int id=0){
	++cnt[id];
	E[id][cnt[id]].to=v,E[id][cnt[id]].next=last[id][u],E[id][cnt[id]].w=w;
	last[id][u]=cnt[id];
}
int n,t;
bool vis[size];
int minv(int a,int b){
	return a<b?a:b;
}
int dfs(int u,int f){
	if(u==n)return f;
	vis[u]=true;
	for(int i=last[1][u];i;i=E[1][i].next)
		if(!vis[E[1][i].to]&&E[1][i].w>0){
			int nf=dfs(E[1][i].to,minv(f,E[1][i].w));
			if(nf){
				E[1][i].w-=nf;
				E[1][i^1].w+=nf;
				return nf;
			}
		}
	return 0;
}
bool check(int x){
	cnt[1]=1;
	memset(last[1],0,sizeof(last[1]));
	for(int i=1;i<=n;++i)
		for(int j=last[0][i];j;j=E[0][j].next)
			if(E[0][j].w<=x && i<E[0][j].to){
				addEdge(i,E[0][j].to,1,1);
				addEdge(E[0][j].to,i,1,1);
			}
	int pc=0;
	while(pc<t){
		memset(vis,0,sizeof(vis));
		int add=dfs(1,1<<30);
		if(add)pc+=add;
		else break;
	}
	return pc>=t;
}
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
	int m;
	n=read();
	m=read();
	t=read();
	int u,v,w,l=1<<30,r=0;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
		if(w>r)r=w;
		if(w<l)l=w;
	}
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}

