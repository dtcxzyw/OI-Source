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
const int size=50*50*50,S=0;
struct Edge{
	int to,next,f;
} E[size*6];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0);
}
int d[size],q[size],T;
bool bfs(){
	memset(d,0,sizeof(int)*(T+1));
	d[S]=1,q[0]=S;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(!d[v] && E[i].f>0){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[T];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int dfs(int u,int f){
	if(u==T || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=dfs(v,minv(f,E[i].f)))>0){
			E[i].f-=k;
			E[i^1].f+=k;
			res+=k;
			f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
const int inf=1<<30;
int dinic(){
	int res=0;
	while(bfs()){
		memcpy(now,last,sizeof(int)*(T+1));
		res+=dfs(S,inf);
	}
	return res;	
}
int x,y,z,A[41][41][41];
int getID(int i,int j,int k){
	return ((i-1)*x+j-1)*y+k;
}
const int off[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int main(){
	x=read();
	y=read();
	z=read();
	T=getID(z,x,y)+1;
	int d=read();
	for(int i=1;i<=z;++i)
		for(int j=1;j<=x;++j)
			for(int k=1;k<=y;++k)
				A[i][j][k]=read();
	for(int j=1;j<=x;++j)
		for(int k=1;k<=y;++k)
			addEdge(S,getID(1,j,k),inf);
	for(int i=1;i<=z;++i)
		for(int j=1;j<=x;++j)
			for(int k=1;k<=y;++k){
				int u=getID(i,j,k);
				addEdge(u,(i==z?T:getID(i+1,j,k)),A[i][j][k]);
				if(i>d){
					for(int t=0;t<4;++t){
						int nx=j+off[t][0],ny=k+off[t][1];
						if(1<=nx && nx<=x && 1<=ny && ny<=y)
							addEdge(u,getID(i-d,nx,ny),inf);
					}
				}
			}
	printf("%d\n",dinic());
	return 0;
}

