#include <cstdio>
#include <cstring>
int read(){
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	return c-'0';
}
const int size=25*25*3;
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
int MCMF(int x){
	int mf=0,ans=0;
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
		mf+=f;
		ans+=f*dis[ST];
	}
	return mf==x?ans:-1;
}
int get(int u,int v,int x){
	return (u*21+v)*3+x;
}
const int off[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int S[25][25],T[25][25];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			S[i][j]=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			T[i][j]=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)	
			if(S[i][j] && T[i][j])S[i][j]=T[i][j]=0;
			else if(S[i][j])++cnt1;
			else if(T[i][j])++cnt2;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			int c=read();
			int lv=c/2,uv=(c+1)/2;
			if(S[i][j])addEdge(get(i,j,1),get(i,j,0),lv,0),addEdge(get(i,j,0),get(i,j,2),uv,0),addEdge(SS,get(i,j,0),1,0);
			else if(T[i][j])addEdge(get(i,j,1),get(i,j,0),uv,0),addEdge(get(i,j,0),get(i,j,2),lv,0),addEdge(get(i,j,0),ST,1,0);
			else addEdge(get(i,j,1),get(i,j,0),lv,0),addEdge(get(i,j,0),get(i,j,2),lv,0);
			for(int k=0;k<8;++k){
				int x=i+off[k][0],y=j+off[k][1];
				if(1<=x && x<=n && 1<=y && y<=m)
					addEdge(get(i,j,2),get(x,y,1),1<<30,1);
			}
		}
	if(cnt1!=cnt2)puts("-1");
	else printf("%d\n",MCMF(cnt1));
	return 0;
}

