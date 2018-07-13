#include <cstdio>
#include <cstring>
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
const int size=1600;
struct Edge{
	int to,next;
} E[2*size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size];
std::vector<int> dc[size];
void DFS(int u,int d){
	dc[d].push_back(u);
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u]!=v){
			p[v]=u;
			DFS(v,d+1);
		}
	}
}
bool flag[2*size]={};
int main(){
	int n=read();
	for(int i=0;i<n;++i){
		int u=read();
		int k=read();
		for(int j=0;j<k;++j){
			int v=read();
			addEdge(u,v);
			addEdge(v,u);
		}
	}
	memset(p,0x3f,sizeof(p));
	p[0]=0;
	DFS(0,0);
	int cnt=0;
	for(int i=n;i>=1;--i){
		for(int j=0;j<dc[i].size();++j){
			int v=dc[i][j];
			if(!flag[v]){
				v=p[v];
				bool add=false;
				if(!flag[v])flag[v]=add=true;
				for(int k=last[v];k;k=E[k].next)
					if(!flag[E[k].to] && p[E[k].to]==v)
						flag[E[k].to]=add=true;
				cnt+=add;
			}	
		}
	}
	printf("%d\n",cnt);
	return 0;
}

