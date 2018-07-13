#include <cstdio>
#include <cmath>
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
const int size=500001;
struct Edge{
	int to,next;
	double p;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,double p){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].p=p;
	last[u]=cnt;
}
double P[size]={},Pt[size]={};
void DFS(int u,int p){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			DFS(v,u);
			double w=Pt[v]*E[i].p;
			Pt[u]=Pt[u]+w-Pt[u]*w;
		}
	}
}
void solve(int u,int p){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p!=v){
			double w=Pt[v]*E[i].p;
			if(fabs(1.0-w)>1e-8){
				double pv=(P[u]-w)/(1.0-w)*E[i].p;
				P[v]=Pt[v]+pv-Pt[v]*pv;
			}
			else P[v]=1.0;
			solve(v,u);
		}
	}
}
int main(){
	int n=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		double p=read()*0.01;
		addEdge(u,v,p);
		addEdge(v,u,p);
	}
	for(int i=1;i<=n;++i)
		Pt[i]=read()*0.01;
	DFS(1,0);
	P[1]=Pt[1];
	solve(1,0);
	double res=0.0;
	for(int i=1;i<=n;++i)res+=P[i];
	printf("%.6lf\n",res);
	return 0;
}

