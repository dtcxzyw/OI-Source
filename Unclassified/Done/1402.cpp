#include <cstdio>
#include <cstring>
struct Edge{
	int to,next;
	bool f;
} E[60000];
const int size=500,S=490,T=491;
int last[size],cnt=1;
void addEdge(int u,int v,bool f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void add2Edge(int u,int v){
	addEdge(u,v,true);
	addEdge(v,u,false);
}
int pre[size],eid[size],q[size];
bool flag[size];
bool BFS(){
	memset(flag,0,sizeof(flag));
	int b=0,e=1;
	q[0]=S,flag[S]=true;
	while(b!=e){
		int u=q[b++];
		if(u==T){
			int p=T;
			while(p){
				E[eid[p]].f=false,E[eid[p]^1].f=true;
				p=pre[p];
			}
			return true;
		}
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(!flag[v] && E[i].f){
				flag[v]=true;
				pre[v]=u,eid[v]=i;
				q[e++]=v;
			}
		}
	}
	return false;
}
int main(){
	int n,p,q;
	scanf("%d%d%d",&n,&p,&q);
	int on1=p,on2=p+n,oq=p+n+n;
	for(int i=1;i<=p;++i)add2Edge(S,i);
	for(int i=1;i<=n;++i)add2Edge(i+on1,i+on2);
	for(int i=1;i<=q;++i)add2Edge(i+oq,T);
	int x;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=p;++j){
			scanf("%d",&x);
			if(x)add2Edge(j,i+on1);
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=q;++j){
			scanf("%d",&x);
			if(x)add2Edge(i+on2,j+oq);
		}
	
	int ans=0;
	while(BFS())++ans;
	printf("%d\n",ans);
	return 0;
}

