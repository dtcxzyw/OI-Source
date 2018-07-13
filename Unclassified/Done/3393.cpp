#include <cstdio>
#include <cstring>
const int size=100001;
struct Edge{
	int to,next;
} E[400001];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int len[size]={};
void DFS(int u,int p){
	if(len[u]<p){
		len[u]=p;
		for(int i=last[u];i;i=E[i].next)
			DFS(E[i].to,p-1);
	}
}
long long dis[size];
int q[size*5];
bool flag[size]={};
void SPFA(int P,int Q,int s){
	memset(dis,0x3f,sizeof(dis));
	int b=0,e=1;
	q[0]=1,flag[1]=true,dis[1]=0;
	while(b!=e){
		int u=q[b++];
		flag[u]=false;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(len[v]==s)continue;
			long long nd=dis[u]+(len[v]?Q:P);
			if(dis[v]>nd){
				dis[v]=nd;
				if(!flag[v]){
					flag[v]=true;
					q[e++]=v;
				}
			}
		}
	}
}
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
int c[size];
int main(){
	int n,m,k,s,P,Q;
	n=read();m=read();k=read();s=read();P=read();Q=read();
	for(int i=0;i<k;++i)c[i]=read();
	int u,v;
	for(int i=0;i<m;++i){
		u=read(),v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	++s;
	for(int i=0;i<k;++i)
		DFS(c[i],s);
	len[1]=len[n]=0;
	SPFA(P,Q,s);
	printf("%lld\n",dis[n]-P);
	return 0;
}

