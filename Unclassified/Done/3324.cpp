#include <cstdio>
#include <cmath>
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
const double eps=1e-8;
bool equal(double a,double b){
	return fabs(b-a)<=eps;
}
const int size=103,S=size-1,T=size-2;
const double inf=1e20;
struct Edge{
	int to,next;
	double f;
} E[size*size*2];
int last[size],cnt;
void addEdgeImpl(int u,int v,double f){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].f=f;
	last[u]=cnt;
}
void addEdge(int u,int v,double f){
	addEdgeImpl(u,v,f);
	addEdgeImpl(v,u,0.0);
}
int d[size],q[size];
bool BFS(){
	memset(d,0,sizeof(d));
	d[S]=1,q[0]=S;
	int b=0,e=1;
	while(b!=e){
		int u=q[b++];
		for(int i=last[u];i;i=E[i].next){
			int v=E[i].to;
			if(E[i].f>eps && !d[v]){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[T];
}
int now[size];
double DFS(int u,double f){
	if(u==T || equal(f,0.0))return f;
	double res=0.0,k;
	for(int& i=now[u];i;i=E[i].next){
		int v=E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,fmin(f,E[i].f)))>eps){
			E[i].f-=k,E[i^1].f+=k;
			res+=k,f-=k;
			if(equal(f,0.0))break;
		}
	}
	if(equal(res,0.0))d[u]=0;
	return res;
}
int A[size],B[size];
bool map[size][size];
double calc(double t,int n,int m){
	memset(last,0,sizeof(last));
	cnt=1;	
	for(int i=1;i<=m;++i)addEdge(S,i,B[i]*t);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			if(map[i][j])
				addEdge(i,j+m,inf);
	for(int i=1;i<=n;++i)
		addEdge(i+m,T,A[i]);
	double res=0.0;
	while(BFS()){
		memcpy(now,last,sizeof(now));
		res+=DFS(S,inf);
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	double sum=0.0;
	for(int i=1;i<=n;++i){
		A[i]=read();
		sum+=A[i];
	}
	for(int i=1;i<=m;++i)B[i]=read();
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			map[i][j]=read();
	double l=0.0,r=1e6;
	while(r-l>=1e-4){
		double mid=(l+r)*0.5;
		if(equal(sum,calc(mid,n,m)))r=mid;
		else l=mid;
	}
	printf("%.4lf\n",l);
	return 0;
}

