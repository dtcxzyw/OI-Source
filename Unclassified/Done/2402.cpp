#include <cstdio>
#include <cstring>
typedef long long Int64;
const Int64 size=410,SS=size-1,ST=size-2;
struct Edge{
	Int64 to,next,c,f,w;
} E[size*size];
Int64 last[size],cnt=1;
void addEdge(Int64 u,Int64 v,Int64 c,Int64 w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c,E[cnt].w=w,E[cnt].f=0;
	last[u]=cnt;
}
void addEdge2(Int64 u,Int64 v,Int64 c,Int64 w){
	addEdge(u,v,c,w);
	addEdge(v,u,0,w);
}
bool mark[size];
Int64 d[size],q[size];
bool BFS(Int64 mid){
	memset(mark,0,sizeof(mark));
	memset(d,0,sizeof(d));
	Int64 b=0,e=1;
	q[0]=SS,mark[SS]=true,d[SS]=0;
	while(b!=e){
		Int64 u=q[b];
		b=(b+1)%size;
		for(Int64 i=last[u];i;i=E[i].next){
			Int64 v=E[i].to;
			if(E[i].w<=mid && !mark[v] && E[i].f<E[i].c){
				d[v]=d[u]+1;
				mark[v]=true;
				q[e]=v;
				e=(e+1)%size;
			}
		}
	}
	return mark[ST];
}
Int64 minv(Int64 a,Int64 b){
	return a<b?a:b;
}
Int64 now[size],mid;
Int64 DFS(Int64 u,Int64 f){
	if(u==ST || f==0)return f;
	Int64 res=0,k;
	for(Int64& i=now[u];i;i=E[i].next){
		Int64 v=E[i].to;
		if(E[i].w<=mid && d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].c-E[i].f)))>0){
			E[i].f+=k;
			E[i^1].f-=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	return res;
}
Int64 check(){
	for(Int64 i=0;i<=cnt;++i)E[i].f=0;
	Int64 res=0;
	while(BFS(mid)){
		memcpy(now,last,sizeof(last));
		res+=DFS(SS,1<<30);
	}
	return res;
}
Int64 link[size][size];
int main(){
	Int64 n,m;
	scanf("%lld%lld",&n,&m);
	Int64 sum=0;
	for(Int64 i=1;i<=n;++i){
		Int64 s,p;
		scanf("%lld%lld",&s,&p);
		sum+=s;
		addEdge2(SS,i,s,0);
		addEdge2(n+i,ST,p,0);
	}
	memset(link,0x3f,sizeof(link));
	for(Int64 i=1;i<=n;++i)link[i][i]=0;
	Int64 u,v,w;
	for(Int64 i=0;i<m;++i){
		scanf("%lld%lld%lld",&u,&v,&w);
		link[u][v]=link[v][u]=minv(link[u][v],w);
	}
	for(Int64 k=1;k<=n;++k)
		for(Int64 i=1;i<=n;++i)
			for(Int64 j=1;j<=n;++j)
				link[i][j]=minv(link[i][j],link[i][k]+link[k][j]);
	Int64 maxl=0;
	for(Int64 i=1;i<=n;++i)
		for(Int64 j=1;j<=n;++j)
			if(link[i][j]!=0x3f3f3f3f3f3f3f3f){
				addEdge2(i,n+j,1<<30,link[i][j]);
				if(link[i][j]>maxl)maxl=link[i][j];
			}
	Int64 ans=-1,l=0,r=maxl;
	while(l<=r){
		mid=(l+r)>>1;
		if(check()==sum)ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}

