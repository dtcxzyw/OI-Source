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
int prime[700000],pcnt=0;
bool flag[10000001];
void pre(int n){
	for(int i=2;i<=n;++i){
		if(!flag[i])prime[++pcnt]=i;
		for(int j=1;j<=pcnt && prime[j]*i<=n;++j){
			flag[prime[j]*i]=true;
			if(i%prime[j]==0)break;
		}
	}
}
const int size=700000,SS=size-1,ST=size-2;
struct Edge{
	int to,next,c,f;
} E[size];
int last[size],cnt;
void addEdge(int u,int v,int c){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=c,E[cnt].f=0;
	last[u]=cnt;
}
void addEdge2(int u,int v,int c){
	addEdge(u,v,c);
	addEdge(v,u,0);
}
int q[size],d[size];
bool mark[size];
bool BFS(){
	memset(mark,0,sizeof(mark));
	memset(d,0,sizeof(d));
	q[0]=SS,mark[SS]=true,d[SS]=0;
	int b=0,e=1;
	while(b!=e){
		int u=q[b];
		b=(b+1)%size;
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f<E[i].c && !mark[v]){
				mark[v]=true;
				d[v]=d[u]+1;
				q[e]=v;
				e=(e+1)%size;
			}
		}
	}
	return mark[ST];
}
int minv(int a,int b){
	return a<b?a:b;
}
int now[size];
int DFS(int u,int f){
	if(u==ST || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,E[i].c-E[i].f)))>0){
			E[i].f+=k;
			E[i^1].f-=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	return res;
}
void foo(){
	int n=read();
	int m=read();
	cnt=1;
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;++i){
		int x=read();
		addEdge2(SS,pcnt+i,1);
		for(int j=1;j<=pcnt && x!=1;++j)
			if(x%prime[j]==0){
				do x/=prime[j];
				while(x%prime[j]==0);
				addEdge2(pcnt+i,j,1);
			}
	}
	for(int i=1;i<=m;++i){
		int x=read();
		addEdge2(pcnt+n+i,ST,1);
		for(int j=1;j<=pcnt && x!=1;++j)
			if(x%prime[j]==0){
				do x/=prime[j];
				while(x%prime[j]==0);
				addEdge2(j,pcnt+n+i,1);
			}
	}
	int ans=0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		ans+=DFS(SS,1<<30);
	}
	printf("%d\n",ans);
}
int main(){
	pre(10000000);
	int t=read();
	for(int i=0;i<t;++i)foo();
	return 0;
}

