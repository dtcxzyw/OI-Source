#include <cstdio>
#include <algorithm>
#include <cmath>
struct Edge{
	int u,v;
	double w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[1000000];
int fa[1001],x[1001],y[1001];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	int u,v;
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		fa[find(u)]=find(v);
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(find(i)!=find(j)){
				double dx=x[i]-x[j],dy=y[i]-y[j];
				E[cnt].u=i,E[cnt].v=j,E[cnt].w=sqrt(dx*dx+dy*dy);
				++cnt;
			}
	std::sort(E,E+cnt);
	double ans=0.0;
	for(int i=0;i<cnt;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			ans+=E[i].w;
		}
	}
	printf("%.2lf\n",ans);
	return 0;
}

