#include <cstdio>
#include <cstring>
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
const int size=10005,S=size-1,T=size-2,inf=1<<30;
struct Edge{
	int to,next,f;
} E[size*4];
int last[size]={},cnt=1;
void addEdgeImpl(int u,int v,int f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,int f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0);
}
int q[size],d[size];
bool BFS(){
	memset(d,0,sizeof(d));
	q[0]=S,d[S]=1;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f>0 && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[T];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int DFS(int u,int f){
	if(u==T || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].f)))>0){
			E[i].f-=k,E[i^1].f+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(res==0)d[u]=0;
	return res;
}
int dinic(){
	int res=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		res+=DFS(S,inf);
	}
	return res;
}
int id[111][111],x[111];
int main(){
	int n=read();
	int m=read();
	int icnt=0;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			id[i][j]=icnt++;
	for(int i=1;i<=n;++i)x[i]=read();
	if(m)
		for(int i=1;i<=1000;++i)
			addEdge(icnt+i,T,i*i);
	int sum=0;
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j){
			int dv=read();
			if(i==j){
				dv-=x[i];
				if(m)addEdge(id[i][j],icnt+x[i],inf);
			}
			else{
				addEdge(id[i][j],id[i+1][j],inf);
				addEdge(id[i][j],id[i][j-1],inf);
			}
			if(dv>0){
				sum+=dv;
				addEdge(S,id[i][j],dv);
			}
			else if(dv<0)
				addEdge(id[i][j],T,-dv);
		}
	printf("%d\n",sum-dinic());
	return 0;
}

