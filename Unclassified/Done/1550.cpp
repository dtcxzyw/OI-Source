#include <cstdio>
#include <algorithm>
const int size=301;
int fa[size],w[size][size],c[size],cnt=0;
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[size*size];
void addEdge(int u,int v,int w){
	E[cnt].u=u,E[cnt].v=v,E[cnt].w=w;
	++cnt;
}
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'|| c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n=read();
	for(int i=0;i<n;++i)
		c[i]=read();
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			w[i][j]=read();
	for(int i=0;i<n;++i){
		for(int j=i+1;j<n;++j)
			addEdge(i,j,w[i][j]);
		addEdge(i,n,c[i]);
	}
	std::sort(E,E+cnt);
	for(int i=0;i<=n;++i)
		fa[i]=i;
	int ans=0;
	for(int i=0;n>0;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			--n;
			ans+=E[i].w;
		}
	}
	printf("%d\n",ans);
	return 0;
}

