#include <cstdio>
#include <set>
long long read(){
	long long res=0;
	int c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=300010;
struct Edge{
	int src,to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].src=u,E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
bool flag[size]={},mark;
int mi,eid[size];
long long mv;
void DFS(int u,int p,long long s){
	if(s>mv)mv=s,mi=u;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v && !flag[v]){
			if(mark)eid[v]=i;
			DFS(v,u,s+E[i].w);
		}
	}
}
int find(int s,bool pre=false){
	mv=0,mi=s,mark=pre;
	if(pre)eid[s]=0;
	DFS(s,0,0);
}
long long dis[size];
long long maxv(long long a,long long b){
	return a>b?a:b;
}
int main(){
	int n=read();
	long long lim=read();
	int u,v,w;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	find(1);
	int s=mi;
	find(s,true);
	int t=mi;
	long long len=mv;
	E[0].src=0;
	for(int i=t;i;i=E[eid[i]].src)flag[i]=true;
	for(int i=t;i;i=E[eid[i]].src){
		find(i);
		dis[i]=mv;
	}
	int r=t;
	long long cl=0,pre=0,ans=1LL<<60;
	std::multiset<long long> now;
    E[0].src=0;
    for(int l=t;l;l=E[eid[l]].src){
        while(r!=s && cl+E[eid[r]].w<=lim){
        	if(l!=r)now.insert(dis[r]);
            cl+=E[eid[r]].w;
            r=E[eid[r]].src;
        }
        long long res=now.empty()?0:*now.rbegin();
        long long lp=maxv(pre,dis[l]);
        if(res<lp)res=lp;
        long long rp=maxv(len-cl-pre,dis[r]);
        if(res<rp)res=rp;
        if(res<ans)ans=res;
        cl-=E[eid[l]].w;
        pre+=E[eid[l]].w;
        if(l!=r && E[eid[l]].src!=r)now.erase(now.find(dis[E[eid[l]].src]));
    }
	printf("%lld\n",ans);
	return 0;
}

