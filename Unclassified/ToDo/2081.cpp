#include <cstdio>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=100005;
struct Edge{
	int to,next,w;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v,int w){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w;
	last[u]=cnt;
}
int stack[size],scnt=0,ring[size],rsiz=0;
bool flag[size]={},mark[size]={}; 
bool findRing(int u,int p){
	if(flag[u]){
		int v;
		do{
			v=stack[scnt--];
			ring[rsiz++]=v;
			mark[v]=true;
		}while(u!=v);
		return true;
	}
	stack[++scnt]=u;
	flag[u]=true;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p && findRing(v,u))
			return true;
	}
	--scnt;
	flag[u]=false;
	return false;
}
int p[size]={},d[size]={};
struct Info{
	double k,b;
} dp[size];
double ans[size];
void DFS(int u){
	double sk=d[u],sb=0.0;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p[u]){
			p[v]=u;
			DFS(v);
			sk-=dp[v].k;
			sb+=dp[v].b;
		}
		sb+=E[i].w;
	}
	dp[u].k=1.0/sk;
	dp[u].b=sb/sk;
}
void solve(int u){
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(v!=p[u] && !mark[v]){
			ans[v]=ans[u]*dp[v].k+dp[v].b;
			solve(v);
		}
	}
}
double ls[size],rs[size],rans[size][2]={},down[size];
double calcRing(){
	for(int i=0;i<rsiz;++i){
		int u=ring[i];
		double sb=0.0,sk=0.0;
		for(int j=last[u];j;j=E[j].next){
			int v=E[j].to;
			if(!mark[v]){
				sk+=dp[v].k;
				sb+=dp[v].b+E[j].w;
			}
			else if(ring[(i+1)%rsiz]==v)rs[i]=E[j].w;
			else ls[i]=E[j].w;
		}
		if(d[u]>2)down[i]=sb/(d[u]-2);
		else down[i]=0.0;
	}
	for(int i=0;i<rsiz;++i){
		double P=1.0,dis=ls[i];
		for(int j=1;j<rsiz;++j){
			int dst=(i-j+rsiz)%rsiz;
			int v=ring[dst];
			double mul=j==rsiz-1?0.0:1.0/(d[v]-1);
			if(d[v]>2 || j==rsiz-1)rans[i][0]+=(down[dst]+dis)*P*(1.0-mul);
			dis+=ls[dst];
			P*=mul;
		}
	}
	for(int i=0;i<rsiz;++i){
		double P=1.0,dis=rs[i];
		for(int j=1;j<rsiz;++j){
			int dst=(i+j)%rsiz;
			int v=ring[dst];
			double mul=j==rsiz-1?0.0:1.0/(d[v]-1);
			if(d[v]>2 || j==rsiz-1)rans[i][1]+=(down[dst]+dis)*P*(1.0-mul);
			dis+=rs[dst];
			P*=mul;
		}
	}
	double res=0.0;
	for(int i=0;i<rsiz;++i){
		int u=ring[i];
		double sum=rans[i][0]+rans[i][1]; 
		res+=(sum+down[i]*(d[u]-2))/d[u];	
		ans[u]=sum/2.0;
		solve(u);
	}
	return res;
}
int main(){
	int n=read();
	int m=read();
	int sum=0;
	for(int i=0;i<m;++i){
		int u=read();
		int v=read();
		int w=read();
		sum+=w;
		addEdge(u,v,w);
		addEdge(v,u,w);
		++d[u],++d[v];
	}
	findRing(1,0);
	double res=0.0;
	if(rsiz==n){
		res=(n-1)*sum;
	}
	else if(rsiz==0){
		DFS(1);
		ans[1]=dp[1].b;
		solve(1);
		for(int i=1;i<=n;++i){
			double s=0.0;
			for(int j=last[i];j;j=E[j].next){
				int v=E[j].to;
				if(d[v]>1)s+=(ans[v]-(ans[i]+E[i].w)/d[v])*d[v]/(d[v]-1)+E[i].w;
				else s+=E[i].w;
			}
			res+=s/d[i];
		}
	}
	else{
		for(int i=0;i<rsiz;++i){
			int u=ring[i];
			for(int j=last[u];j;j=E[j].next){
				int v=E[j].to;
				if(!mark[v]){
					p[v]=u;
					DFS(v);
				}
			}
		}
		res+=calcRing();
		for(int i=1;i<=n;++i){
			if(!mark[i]){
				res+=ans[i];
			}
		}
	}
	printf("%.5lf\n",res/n);
	return 0;
}

