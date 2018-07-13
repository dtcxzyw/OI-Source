#include <cstdio>
#include <algorithm>
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[500*500];
int fa[500]={};
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	int c,cnt=0;
	for(int i=0;i<b;++i){
		for(int j=0;j<=i;++j)scanf("%d",&c);
		for(int j=i+1;j<b;++j){
			scanf("%d",&c);
			if(c){
				E[cnt].u=i;
				E[cnt].v=j;
				E[cnt].w=c;
				++cnt;
			}
		}
	}
	std::sort(E,E+cnt);
	for(int i=0;i<b;++i)
		fa[i]=i;
	int ans=a;
	for(int i=0;i<cnt;++i){
		int fu=find(E[i].u),fv=find(E[i].v);
		if(fu!=fv){
			fa[fu]=fv;
			ans+=E[i].w;
		}
	}
	printf("%d\n",ans);
	return 0;
}

