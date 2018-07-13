#include <cstdio>
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
const int size=100001;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int k,d[size],p[size];
int flag[size]={};
std::vector<int> layer[size];
void DFS(int u){
	d[u]=d[p[u]]+1;
	layer[d[u]].push_back(u); 
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			DFS(v);
		}
	}
}
void color(int u,int k){
	if(flag[u]>=k)return;
	flag[u]=k;
	if(k>1)
		for(int i=last[u];i;i=E[i].next)
			color(E[i].to,k-1);
}
int main(){
	int n=read();
	k=read();
	int t=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);	
	}
	d[0]=0;
	DFS(1);
	int ans=0;
	for(int i=n;i>=0;--i)
		for(int j=0;j<layer[i].size();++j){
			int u=layer[i][j];
			if(!flag[u]){
				for(int c=0;c<k;++c)
					if(p[u])u=p[u];
				color(u,k+1);
				++ans;
			}
		}
	printf("%d\n",ans);
	return 0;	
}

