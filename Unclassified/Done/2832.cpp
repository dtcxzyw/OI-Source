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
struct Edge{
	int to,next,w;
} E[200001];
const int size=10001,moff=101,qsize=size*moff;
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int dis[size][moff];
struct State{
	short u,off;
	State():u(0),off(0){}
	State(short to,short offset):u(to),off(offset){}
} q[qsize],pre[size][moff];
bool flag[size][moff];
void SPFA(){
	memset(dis,0x3f,sizeof(dis));
	int b=0,e=1;
	dis[1][0]=0,flag[1][0]=true,q[0]=State(1,0);
	while(b!=e){
		State src=q[b];
		flag[src.u][src.off]=false;
		b=(b+1)%qsize;
		for(int i=last[src.u];i;i=E[i].next){
			int nd=dis[src.u][src.off]+src.off+E[i].w;
			State dst(E[i].to,src.off+1);
			if(nd<dis[dst.u][dst.off]){
				dis[dst.u][dst.off]=nd;
				pre[dst.u][dst.off]=src;
				if(!flag[dst.u][dst.off]){
					flag[dst.u][dst.off]=true;
					q[e]=dst;
					e=(e+1)%qsize;
				}
			}
		}
	}
}
int st[size];
int main(){
	int n=read();
	int m=read();
	int u,v,w;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
	}
	SPFA();
	int minv=1<<30,mo;
	for(int i=0;i<moff;++i)
		if(dis[n][i]<minv)
			minv=dis[n][i],mo=i;
	printf("%d\n",minv);
	State c(n,mo);
	int scnt=0;
	while(c.u){
		st[++scnt]=c.u;
		c=pre[c.u][c.off];
	}
	for(int i=scnt;i>=1;--i)
		printf("%d ",st[i]);
	return 0;
}

