#include <cstdio>
#include <vector>
const int size=10010;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
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
bool flag[size*1000]={};
std::vector<int> d[size];
void DFS(int u,int p){
	d[u].push_back(0); 
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p){
			DFS(v,u);
			for(int j=0;j<d[v].size();++j){
				d[u].push_back(d[v][j]+E[i].w);
				flag[d[u].back()]=true;
			}
		}
	}
	for(int i=last[u];i;i=E[i].next){
		int vi=E[i].to;
		if(vi!=p){
			for(int j=E[i].next;j;j=E[j].next){
				int vj=E[j].to;
				if(vj!=p){
					for(int k=0;k<d[vi].size();++k)
						for(int l=0;l<d[vj].size();++l)
							flag[d[vi][k]+d[vj][l]+E[i].w+E[j].w]=true;
				}
			}
		}
	}
}
int main(){
	int n=read();
	int m=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	DFS(1,0);
	for(int i=0;i<m;++i)
		puts(flag[read()]?"AYE":"NAY");
	return 0;
}

