#include <cstdio>
#include <cstring>
int read(){
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	return c-'0';
}
const int size=20*20*2;
struct Edge{
	int to,next,w,c;
} E[100000];
int last[size]={},cnt=1;
const int SS=size-1,ST=size-2;
void addEdgeImpl(int u,int v,int c,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w,E[cnt].c=c;
	last[u]=cnt;
}
void addEdge(int u,int v,int c,int w){
	addEdgeImpl(u,v,c,w);
	addEdgeImpl(v,u,0,-w);
}
int dis[size],eid[size],q[size];
bool flag[size]={};
bool SPFA(){
	memset(dis,0x3f,sizeof(dis));
	int b=0,e=1;
	q[0]=SS,dis[SS]=0,flag[SS]=true;
	while(b!=e){
		int u=q[b];
		flag[u]=false;
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].c>0 && dis[v]>dis[u]+E[i].w){
				dis[v]=dis[u]+E[i].w;
				eid[v]=i;
				if(!flag[v]){
					flag[v]=true;
					q[e]=v;
					e=(e+1)%size;
				}
			}
		}
	}
	return dis[ST]!=0x3f3f3f3f;
}
int minv(int a,int b){
	return a<b?a:b;
}
int MCMF(){
	int ans=0;
	while(SPFA()){
		int p=ST,f=1<<30;
		while(p!=SS){
			f=minv(f,E[eid[p]].c);
			p=E[eid[p]^1].to;
		}
		p=ST;
		while(p!=SS){
			E[eid[p]].c-=f;
			E[eid[p]^1].c+=f;
			p=E[eid[p]^1].to;
		}
		ans+=f*dis[ST];
	}
	return ans;
}
int get(int x,int y,int z){
	return (x*20+y)*2+z;
}
const int off[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int fix(int a,int b){
	return ((a-1)%b+b)%b+1;
}
char A[20][20];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",A[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			addEdge(SS,get(i,j,0),1,0);
			addEdge(get(i,j,1),ST,1,0);
			int t;
			switch(A[i][j]){
				case 'L':t=0;break;
				case 'R':t=1;break;
				case 'U':t=2;break;
				case 'D':t=3;break;
			}
			for(int k=0;k<4;++k){
				int cx=fix(i+off[k][0],n),cy=fix(j+off[k][1],m);
				addEdge(get(i,j,0),get(cx,cy,1),1,k!=t);
			}
		}
	printf("%d\n",MCMF());
	return 0;
}

