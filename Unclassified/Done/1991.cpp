#include <cstdio>
#include <algorithm>
#include <cmath>
const int size=501;
struct Edge{
	int u,v;
	double w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[size*size];
int fa[size],X[size],Y[size],cnt=0;
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
double len[size];
int main(){
	int s,n;
	scanf("%d%d",&s,&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&X[i],&Y[i]);
		fa[i]=i;
		for(int j=1;j<i;++j){
			double dx=X[i]-X[j],dy=Y[i]-Y[j];
			E[cnt].u=i,E[cnt].v=j,E[cnt].w=sqrt(dx*dx+dy*dy);
			++cnt;
		}
	}
	std::sort(E,E+cnt);
	int num;
	len[0]=0;
	for(int i=0;num<n-1;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			++num;
			len[num]=E[i].w;
		}
	}
	printf("%.2lf\n",len[num-s]);
	return 0;
}

