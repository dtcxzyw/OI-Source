#include <cstdio>
#include <cstring>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
const int SS=1,ST=2,size=1000;
struct G{
	struct Edge{
		int to,next,c;
	} E[300*size];
	int last[size],cnt;
	void clearAsGraph(){
		memset(last,0,sizeof(last));
		cnt=0;
	}
	void clearAsNet(){
		memset(last,0,sizeof(last));
		cnt=1;
	}
	void addEdgeGraph(int u,int v,int w){
		++cnt;
		E[cnt].to=v,E[cnt].next=last[u],E[cnt].c=w;
		last[u]=cnt;
	}
	void addEdgeNet(int u,int v,int c){
		addEdgeGraph(u,v,c);
		addEdgeGraph(v,u,0);
	}
} g1,g2;
int q[size],d[size];
bool flag[size]={};
void color(int u){
	flag[u]=true;
	for(int i=g1.last[u];i;i=g1.E[i].next){
		int v=g1.E[i].to;
		if(!flag[v])color(v);
	}
}
void findRing(int pcnt){
	int icnt=0;
	for(int i=3;i<=pcnt;++i)
		if(d[i])flag[i]=true;
		else q[++icnt]=i;
	for(int i=1;i<=icnt;++i){
		int u=q[i];
		for(int j=g1.last[u];j;j=g1.E[j].next){
			int v=g1.E[j].to;
			if((--d[v])==0){
				q[++icnt]=v;
				flag[v]=false;
			}
		}
	}
	for(int i=3;i<=pcnt;++i)
		if(flag[i])color(i);
}
bool BFS(int pcnt){
	memset(d,0,sizeof(int)*pcnt);
	int b=0,e=1;
	d[SS]=1,q[b]=SS;
	while(b!=e){
		int u=q[b++];
		for(int i=g2.last[u];i;i=g2.E[i].next){
			int v=g2.E[i].to;
			if(d[v]==0 && g2.E[i].c>0){
				d[v]=d[u]+1;
				q[e++]=v;
			}
		}
	}
	return d[ST];
}
int now[size];
int minv(int a,int b){
	return a<b?a:b;
}
int DFS(int u,int f){
	if(u==ST || f==0)return f;
	int res=0,k;
	for(int& i=now[u];i;i=g2.E[i].next){
		int v=g2.E[i].to;
		if(d[v]==d[u]+1 && (k=DFS(v,minv(f,g2.E[i].c)))>0){
			g2.E[i].c-=k,g2.E[i^1].c+=k;
			res+=k,f-=k;
			if(f==0)break;
		}
	}
	if(!res)now[u]=0;
	return res;
}
int dinic(int pcnt){
	int res=0;
	while(BFS(pcnt)){
		memcpy(now,g2.last,sizeof(int)*pcnt);
		res+=DFS(SS,1<<30);
	}
	return res;
}
int id[50][50],w[size];
int main(){
	int n=read();
	int m=read();
	int cnt=2;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			id[i][j]=++cnt;
	g1.clearAsGraph();
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j){
			w[id[i][j]]=read();
			int siz=read();
			for(int k=0;k<siz;++k){
				int x=read();
				int y=read();
				g1.addEdgeGraph(id[i][j],id[x][y],0),++d[id[x][y]]; 
			}
			if(j)g1.addEdgeGraph(id[i][j],id[i][j-1],0),++d[id[i][j-1]];
		}
	findRing(cnt);
	g2.clearAsNet();
	int ans=0;
	for(int i=3;i<=cnt;++i)
		if(!flag[i]){
			if(w[i]>0)ans+=w[i],g2.addEdgeNet(i,ST,w[i]);
			else g2.addEdgeNet(SS,i,-w[i]);
			for(int j=g1.last[i];j;j=g1.E[j].next){
				int v=g1.E[j].to;
				if(!flag[v])g2.addEdgeNet(i,v,1<<30);
			}
		}
	ans-=dinic(cnt+1);
	printf("%d\n",ans);
	return 0;
}

