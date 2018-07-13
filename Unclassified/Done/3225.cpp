#include <cstdio>
#include <cstring>
#include <set>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
} 
const int size=510;
struct Edge{
	int to,next;
} E[size*size];
int last[size],cnt;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int dfn[size],dcnt,low[size];
bool flag[size];
void DFS(int u,int p){
	dfn[u]=low[u]=++dcnt;
	int scnt=0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(dfn[v]){
			if(v!=p && dfn[v]<low[u])
				low[u]=dfn[v];
		}
		else{
			DFS(v,u),++scnt;
			if(low[v]<low[u])low[u]=low[v];
			if(p!=-1 && low[v]>=dfn[u])flag[u]=true;
		}
	}
	if(p==-1 && scnt>1)flag[u]=true;
}
int siz,vis[size];
std::set<int> link;
void solve(int u){
	vis[u]=true;
	++siz;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!vis[v])solve(v);
		else if(flag[v])link.insert(v);
	}
}
void clear(){
	cnt=0;
	memset(last,0,sizeof(last));
	memset(dfn,0,sizeof(dfn));
	memset(flag,0,sizeof(flag));
	dcnt=0;
}
bool foo(int t){
	int n=read();
	if(n==0)return false;
	clear();
	for(int i=0;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);	
	}
	for(int i=1;i<=500;++i)
		if(last[i] && !dfn[i])
			DFS(i,-1);
	for(int i=1;i<=500;++i)
		vis[i]=flag[i];
	long long ans=0,cnt=1;
	for(int i=1;i<=500;++i)
		if(last[i] && !vis[i]){
			siz=0;
			link.clear();
			solve(i);
			if(link.size()==1)++ans,cnt*=siz;
			else if(link.empty())ans+=2,cnt*=1LL*siz*(siz-1)/2;
		}
	printf("Case %d: %lld %lld\n",t,ans,cnt);
	return true;
}
int main(){
	int t=1;
	while(foo(t))++t;
	return 0;
}

