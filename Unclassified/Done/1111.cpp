#include <cstdio>
#include <algorithm>
int fa[1001];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
struct Edge{
	int u,v,t;
	bool operator<(const Edge& rhs) const{
		return t<rhs.t;
	}
} E[100001];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=0;i<m;++i)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].t);
	std::sort(E,E+m);
	for(int i=0;i<m;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			int x=find(1);
			bool flag=true;
			for(int j=2;j<=n;++j)
				if(find(j)!=x){
					flag=false;
					break;
				}
			if(flag){
				printf("%d\n",E[i].t);
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}

