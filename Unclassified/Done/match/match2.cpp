#include <cstdio>
#include <memory.h>
struct Edge final{
	int to,next;
} E[1000001];
int last[1001]={},pair[1001]={};
bool flag[1001]={};
bool match(int u){
	int v;
	for(int i=last[u];i;i=E[i].next){
		v=E[i].to;
		if(!flag[v]){
			flag[v]=true;
			if(!pair[v] || match(pair[v])){
				pair[v]=u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	int n,m,e,u,v;
	scanf("%d%d%d",&n,&m,&e);
	for(int i=1;i<=e;++i){
		scanf("%d%d",&u,&v);
		if(v>m)continue;
		E[i].to=v,E[i].next=last[u];
		last[u]=i;
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		memset(flag,0,sizeof(flag));
		ans+=match(i);
	}
	printf("%d\n",ans);
	return 0;
}

