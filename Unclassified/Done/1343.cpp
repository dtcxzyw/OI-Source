#include <cstdio>
#include <cstring>
const int size=210;
struct Edge{
	int to,next;
	long long c;
} E[4100];
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
int n,d[size],q[size];
bool BFS(){
	memset(d,0,sizeof(d));
	d[1]=1,q[0]=1;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(!d[v] && E[i].c>0){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[n];
}
long long minv(long long a,long long b){
	return a<b?a:b;
}
int now[size];
long long DFS(int u,long long f){
	if(u==n || f<=0)return f;
	int nf=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && E[i].c>0 && (k=DFS(v,minv(f,E[i].c)))>0){
			E[i].c-=k,E[i^1].c+=k;
			nf+=k,f-=k;
			if(f<=0)break;
		}
	}
	return nf;
}
int main(){
	int m,x;
	scanf("%d%d%d",&n,&m,&x);
	int u,v,c;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&u,&v,&c);
		addEdge(u,v,c);
	}
	long long mf=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		mf+=DFS(1,1LL<<60);
	}
	if(mf>0)printf("%lld %lld\n",mf,x/mf+(x%mf>0));
	else puts("Orz Ni Jinan Saint Cow!");
	return 0;
}

