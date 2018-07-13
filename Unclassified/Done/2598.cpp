#include <cstdio>
#include <cstring>
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
const int size=110*110,SS=1,ST=2;
struct Edge{
	int to,next,c;
} E[20*size];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int c){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c;
	last[u]=cnt;
}
void addEdge(int u,int v,int c){
	addEdgeImpl(u,v,c);
	addEdgeImpl(v,u,0);
}
int q[size],d[size];
bool BFS(int icnt){
	memset(d,0,sizeof(int)*icnt);
	int b=0,e=1;
	q[b]=SS,d[SS]=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(d[v]==0 && E[i].c>0){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[ST];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int DFS(int u,int f){
	if(u==ST || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].c)))>0){
			E[i].c-=k,E[i^1].c+=k;
			f-=k,res+=k;
			if(f==0)break;
		}
	}
	if(!res)d[u]=0;
	return res;
}
int dinic(int icnt){
	int res=0;
	while(BFS(icnt)){
		memcpy(now,last,sizeof(int)*icnt);
		res+=DFS(SS,1<<30);
	}
	return res;
}
const int off[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int A[110][110],id[110][110]={};
int main(){
	int n=read();
	int m=read();
	int icnt=3;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			A[i][j]=read(),id[i][j]=++icnt;
	const int inf=1<<30;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if(A[i][j]==1)addEdge(SS,id[i][j],inf);
			else if(A[i][j]==2)addEdge(id[i][j],ST,inf);
			if(A[i][j]!=2)
				for(int k=0;k<4;++k){
					int x=i+off[k][0],y=j+off[k][1];
					if(id[x][y] && A[x][y]!=1)
						addEdge(id[i][j],id[x][y],1);
				}
		}
	printf("%d\n",dinic(icnt+2));
	return 0;
}

