#include <cstdio>
#include <algorithm>
int fa[2001];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int a,int b){
	fa[a]=b;
}
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[2000001];
int x[2001],y[2001];
int main(){
	int n,c;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j){
			int dx=x[i]-x[j],dy=y[i]-y[j];
			E[cnt].w=dx*dx+dy*dy;
			if(E[cnt].w>=c){
				E[cnt].u=i,E[cnt].v=j;
				++cnt;
			}
		}
	
	if(cnt<n-1){
		puts("-1");
		return 0;
	}
	
	std::sort(E,E+cnt);
	
	for(int i=1;i<=n;++i)fa[i]=i;
		
	long long sum=0;
	
	for(int i=0;i<cnt;++i){
		int a=find(E[i].u),b=find(E[i].v);
		if(a!=b){
			sum+=E[i].w;
			merge(a,b);
			--n;
			if(n==1)break;
		}
	}
	
	if(n==1)printf("%lld",sum);
	else puts("-1");
	
	return 0;
}

