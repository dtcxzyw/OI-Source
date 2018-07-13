#include <cstdio>
#include <algorithm>
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[100*100];
int mat[100][100],fa[100],cnt=0;
int find(int x){
	return fa[x]==x?fa[x]:fa[x]=find(fa[x]);
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			scanf("%d",&mat[i][j]);
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j){
			E[cnt].u=i,E[cnt].v=j,E[cnt].w=mat[i][j];
			++cnt;
		}
	std::sort(E,E+cnt);
	for(int i=0;i<n;++i)
		fa[i]=i;
	int ans=0;
	for(int i=0;n>1;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			ans+=E[i].w;
			--n;
		}
	}
	printf("%d\n",ans);
	return 0;
}

