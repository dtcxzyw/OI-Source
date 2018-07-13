#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
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
const int size=3010;
struct Edge{
	int to,next,w;
} E[70100];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
std::vector<int> pu[size];
long long f[size],g[size];
int in[size];
bool flag[size]={};
long long maxv(long long a,long long b){
	return a>b?a:b;
}
struct Info{
	int u;
	long long d;
	Info(int s,long long f):u(s),d(f){}
	bool operator<(const Info& rhs) const{
		return d>rhs.d;
	}
};
void foo(){
	memset(f,0x3f,sizeof(f));
	std::priority_queue<Info> q;
	g[1]=f[1]=0;
	q.push(Info(1,0));
	while(q.size()){
		Info u=q.top();
		q.pop();
		if(flag[u.u] || maxv(f[u.u],g[u.u])!=u.d)continue;
		flag[u.u]=true;
		for(int i=0;i<pu[u.u].size();++i){
			int v=pu[u.u][i];
			if(--in[v]==0){
				g[v]=u.d;
				q.push(Info(v,maxv(g[v],f[v]))); 
			}
		}
		for(int i=last[u.u];i;i=E[i].next){
			int v=E[i].to;
			if(f[v]>u.d+E[i].w){
				f[v]=u.d+E[i].w;
				if(!in[v])q.push(Info(v,maxv(f[v],g[v]))); 
			}
		}
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int w=read();
		addEdge(u,v,w);
	}
	for(int i=1;i<=n;++i){
		int k=read();
		in[i]=k;
		for(int j=0;j<k;++j){
			int v=read();
			pu[v].push_back(i);
		}
	}
	foo();
	printf("%lld\n",maxv(f[n],g[n]));
	return 0;
}

