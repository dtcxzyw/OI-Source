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
const int size=3005;
struct Edge{
	int to,next;
	double w;
} E[10010];
int last[size]={},cnt=0;
void addEdge(int u,int v,double w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
double dis[size];
bool flag[size];
bool spfa(int u){
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		double nd=dis[u]+E[i].w;
		if(nd<dis[v]){
			if(flag[v])return true;
			else{
				dis[v]=nd;
				if(spfa(v))return true;
			}
		}
	}
	flag[u]=false;
	return false;
}
bool check(int n){
	memset(dis,0,sizeof(double)*(n+1));
	memset(flag,0,sizeof(bool)*(n+1));
	for(int i=1;i<=n;++i){
		if(spfa(i))
			return true;
	}
	return false;
}
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		double w;
		scanf("%lf",&w);
		addEdge(u,v,w);
	}
	double l=-1e7,r=1e7,last=0.0;
	while(r-l>=1e-9){
		double mid=(l+r)*0.5;
		double delta=mid-last;
		for(int i=1;i<=cnt;++i)E[i].w-=delta;
		last=mid;
		if(check(n))r=mid;
		else l=mid;
	}
	printf("%.8lf\n",l);
	return 0;
}

