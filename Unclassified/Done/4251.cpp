#include <cstdio>
#include <algorithm>
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
const int size=600,S=size-1,T=size-2;
struct Edge{
	int to,next,f;
} E[(size+251*251)*2];
int last[size],cnt;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0);
}
int d[size],q[size];
bool BFS(){
	memset(d,0,sizeof(d));
	q[0]=S,d[S]=1;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[T];
}
int now[size];
int DFS(int u,int f){
	if(u==T || f==0)return f;
	int res=0,k;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,std::min(f,E[i].f)))){
			E[i].f-=k,E[i^1].f+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
int A[251][251];
bool check(int n,int m,int end,int x){
	cnt=1;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;++i)addEdge(S,i,1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(A[i][j]<=x)
				addEdge(i,n+j,1);
	for(int i=1;i<=m;++i)
		addEdge(i+n,T,1);
	int res=0;
	while(BFS() && res<end){
		memcpy(now,last,sizeof(now));
		res+=DFS(S,1<<30);
	}
	return res>=end;
}
int main(){
	int n=read();
	int m=read();
	int k=read();
	int minv=1<<30,maxv=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			A[i][j]=read();
			minv=std::min(minv,A[i][j]);
			maxv=std::max(maxv,A[i][j]);
		}
	int l=minv,r=maxv,ans=maxv,end=n-k+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(n,m,end,mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;	
}

