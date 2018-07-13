#include <cstdio>
#include <vector>
#include <memory.h>
struct Edge final{
	int to,next;
	bool flag;
} E[1002001];
int cnt=0,last[2003];
inline int minv(int a,int b){
	return a<b?a:b;
}
constexpr int s=2001,t=2002;
struct Info final{
	int v,prev,e;
};
bool flag[2003];
inline bool BFS(){
	memset(flag,0,sizeof(flag));
	using Path=std::vector<Info>;
	Path p;
	p.push_back({s,-1,-1});
	int size,i,l=0,id;
	while(true){
		size=p.size();
		for(i=l;i<size;++i){
			if(flag[p[i].v])continue;
			else flag[p[i].v]=true;
			for(id=last[p[i].v];id;id=E[id].next)
				if(E[id].flag){
					if(E[id].to==t){
						i=l;
						E[id].flag=false;
						while(i){
							E[p[i].e].flag=false;
							i=p[i].prev;
						}
						
						return true;
					}
					else p.push_back({E[id].to,i,id});
				}
		}
		if(p.size()==size)return false;
		l=size;
	}
}
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].flag=true;
	last[u]=cnt;
}
int main(){
	int n,m,e,i,u,v;
	scanf("%d%d%d",&n,&m,&e);
	
	for(i=1;i<=n;++i)
		addEdge(s,i);
		
	for(i=1;i<=m;++i)
		addEdge(i+1000,t);
	
	for(i=0;i<e;++i){
		scanf("%d%d",&u,&v);
		if(v>m)continue;
		addEdge(u,v+1000);
	}
	
	int ans=0;
	while(BFS())++ans;
	printf("%d\n",ans);
	return 0;
}

