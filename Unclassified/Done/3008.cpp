#include <cstdio>
#include <cstring>
const int size=25010;
struct Edge{
	int to,next,w;
} E[50010*3];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int dis[size],q[size];
bool flag[size]={};
void SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,flag[s]=true,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			int d=dis[u]+E[i].w;
			if(dis[v]>d){
				dis[v]=d;
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
int main(){
	int n,r,p,s;
	n=read();
	r=read();
	p=read();
	s=read();
	int u,v,w;
	for(int i=0;i<r;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	for(int i=0;i<p;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
	}
	SPFA(s);
	for(int i=1;i<=n;++i)
		if(dis[i]!=0x3f3f3f3f) printf("%d\n",dis[i]);
		else puts("NO PATH");
	return 0;
}

