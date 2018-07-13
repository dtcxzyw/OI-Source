#include <cstdio>
#include <vector>
#include <memory.h>
struct Edge final{
	int to,next,w;
} E[100001];
int cnt=0,last[10001],n,s,t;
inline int minv(int a,int b){
	return a<b?a:b;
}
constexpr int maxv=100000000;
struct Info final{
	int v,prev,e;
};
bool flag[10001];
inline int BFS(){
	memset(flag,0,n+1);
	using Path=std::vector<Info>;
	Path p;
	p.push_back({s,-1,-1});
	int size,i,l=0,id,limit=maxv;
	while(true){
		size=p.size();
		for(i=l;i<size;++i){
			if(flag[p[i].v])continue;
			else flag[p[i].v]=true;
			for(id=last[p[i].v];id;id=E[id].next)
				if(E[id].w>0){
					if(E[id].to==t){
						
						limit=E[id].w;
						l=i;
						
						while(i){
							limit=minv(limit,E[p[i].e].w);
							i=p[i].prev;
						}
					
						i=l;
						E[id].w-=limit;
						while(i){
							E[p[i].e].w-=limit;
							i=p[i].prev;
						}
						
						return limit;
					}
					else p.push_back({E[id].to,i,id});
				}
		}
		if(p.size()==size)return 0;
		l=size;
	}
}
int main(){
	int m,i,u;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=0;i<m;++i){
		++cnt;
		scanf("%d%d%d",&u,&E[cnt].to,&E[cnt].w);
		E[cnt].next=last[u];
		last[u]=cnt;
	}
	int w,ans=0;
	while(w=BFS())ans+=w;
	printf("%d\n",ans);
	return 0;
}

