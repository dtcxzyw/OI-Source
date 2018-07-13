#include <cstdio>
#include <set>
constexpr int size=100001;
struct Edge final{
	int to,next;
} E[size<<1];
int cnt=0,last[size]={};
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
std::set<int> key;
int p[size]={},order[size],mp[size];
bool visit[size]={};
void DFS(int x){
	static int count=0;
	mp[x]=order[x]=++count,visit[x]=true;
	int child=0;
	for(int i=last[x];i;i=E[i].next){
		int v=E[i].to;
		
		if(!visit[v]){
			p[v]=x;
			DFS(v);
			mp[x]=std::min(mp[x],mp[v]);
			++child;
			if(p[x] && mp[v]>=order[x])
				key.insert(x);
		}
		else if(p[E[i].to]!=x)
			mp[x]=std::min(mp[x],order[v]);
	}
	
	if(!p[x] && child>1)
		key.insert(x);
}

int main(){
	int n,m,i,u,v;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
	
	for(int i=1;i<=n;++i)
		DFS(i);
		
	printf("%d\n",static_cast<int>(key.size()));
	for(auto&& x:key)
		printf("%d ",x);
	return 0;
}

