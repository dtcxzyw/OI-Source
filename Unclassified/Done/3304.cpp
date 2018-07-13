#include <cstdio>
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
const int size=200010;
struct Edge{
	int src,to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].src=u,E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
long long mv;
int mi,eid[size];
bool flag[size],mark;
void DFS(int u,int p,long long d){
	if(d>mv)mv=d,mi=u;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v && !flag[v]){
			if(mark)eid[v]=i;
			DFS(v,u,d+E[i].w);
		}
	}
}
void find(int s,bool set){
	mv=0,mi=s,mark=set;
	if(mark)eid[s]=0;
	DFS(s,0,0);
}
int main(){
	int n=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	find(1,false);
	int s=mi;
	find(s,true);
	int t=mi;
	long long len=mv;
	printf("%lld\n",len);
	for(int i=t;i;i=E[eid[i]].src)flag[i]=true;
	int l=0,r=0;
	long long sum=0;
	for(int i=t;i;i=E[eid[i]].src){
		++r;
		find(i,false);
		if(mv==sum)l=r;
		if(mv==len-sum)break;
		sum+=E[eid[i]].w;
	}
	printf("%d\n",r-l);
	return 0;
}

