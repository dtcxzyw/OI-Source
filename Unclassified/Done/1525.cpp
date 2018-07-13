#include <cstdio>
#include <algorithm>
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w>rhs.w;
	}
} E[100000];
int fa[40010];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	std::sort(E,E+m);
	for(int i=1;i<=(n<<1);++i)
		fa[i]=i;
	for(int i=0;i<m;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu==fv){
			printf("%d\n",E[i].w);
			return 0;
		}
		fa[fu]=find(E[i].v+n);
		fa[fv]=find(E[i].u+n);
	}
	puts("0");
	return 0;
}

