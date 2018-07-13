#include <cstdio>
#include <algorithm>
int d[511]={},cnt[511][511]={},id[1500],pc=0,l=500,r=1;
void dfs(int u){
	for(int v=l;v<=r;++v)
		if(cnt[u][v]){
			--cnt[u][v],--cnt[v][u];
			dfs(v);
		}
	id[++pc]=u;
}
int main(){
	int n;
	scanf("%d",&n);
	int u,v;
	for(int i=0;i<n;++i){
		scanf("%d%d",&u,&v);
		++cnt[u][v],++cnt[v][u];
		++d[u],++d[v];
		l=std::min(l,std::min(u,v));
		r=std::max(r,std::max(u,v));
	}
	int s=1;
	for(int i=l;i<=r;++i)
		if(d[i]&1){
			s=i;
			break;
		}
	dfs(s);
	for(int i=pc;i>0;--i)
		printf("%d\n",id[i]);
	return 0;
}

