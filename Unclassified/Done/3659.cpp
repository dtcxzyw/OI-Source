#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int size=50001;
struct Edge{
	int to,next,w;
} E[4*size];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
long long dis[size];
int q[size];
bool flag[size]={};
void SPFA(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,flag[s]=true,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			long long nd=dis[u]+E[i].w+t;
			int v=E[i].to;
			if(nd<dis[v]){
				dis[v]=nd;
				if(!flag[v]){
					flag[v]=true;
					if(dis[q[b]]<dis[v]){
						q[e]=v;
						e=(e+1)%size;
					}
					else{
						b=(b-1+size)%size;
						q[b]=v;
					}
				}
			}
		}
	}
}
int w[101][101];
int id(int x,int y,int n,int m){
	return (x*n+y)*3+m;
}
int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&w[i][j]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int m=0;m<=2;++m){
				int v=(m==2?w[i][j]:0),me=id(i,j,n,(m+1)%3);
				if(i>1)addEdge(id(i-1,j,n,m),me,v);
				if(j>1)addEdge(id(i,j-1,n,m),me,v);
				if(i<n)addEdge(id(i+1,j,n,m),me,v);
				if(j<n)addEdge(id(i,j+1,n,m),me,v);
			}
	SPFA(id(1,1,n,0),t);
	printf("%d\n",min(dis[id(n,n,n,0)],min(dis[id(n,n,n,1)],dis[id(n,n,n,2)])));
	return 0;
}

