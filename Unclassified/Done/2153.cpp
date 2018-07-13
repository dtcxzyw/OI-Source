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
const int vcnt=210,size=vcnt*2;
struct Edge{
	int to,next,f,c;
} E[2*(20100+vcnt)];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f,int c){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f,E[cnt].c=c;
	last[u]=cnt;
}
void addEdge(int u,int v,int f,int c){
	addEdgeImpl(u,v,f,c);
	addEdgeImpl(v,u,0,-c);
}
int q[size],dis[size],edge[size],f[size];
bool flag[size]={};
int minv(int a,int b){
	return a<b?a:b;
}
bool SPFA(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0,f[s]=1<<30,q[0]=s;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next)
			if(E[i].f){
				int v=E[i].to;
				int nd=dis[u]+E[i].c;
				if(nd<dis[v]){
					dis[v]=nd;
					edge[v]=i;
					f[v]=minv(f[u],E[i].f);
					if(!flag[v]){
						flag[v]=true;
						q[e]=v;
						e=(e+1)%size;		
					}
				}
			}
	}
	return dis[t]!=0x3f3f3f3f;
}
void MCMF(int s,int t){
	int mf=0,mc=0;
	while(SPFA(s,t)){
		mf+=f[t];
		mc+=f[t]*dis[t];
		int p=t;
		while(p!=s){
			int e=edge[p];
			E[e].f-=f[t];
			E[e^1].f+=f[t];
			p=E[e^1].to;
		}
	}
	printf("%d %d\n",mf,mc);
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int c=read();
		addEdge(u,v+n,1,c);
	}
	for(int i=1;i<=n;++i)
		addEdge(i+n,i,1,0);
	MCMF(1,n+n);
	return 0;
}

