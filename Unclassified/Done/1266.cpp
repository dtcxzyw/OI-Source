#include <cstdio>
#include <queue>
#include <stack>
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
struct Edge{
	int to,next,w,s;
} E[151*151];
int last[151]={},cnt=0;
void addEdge(int u,int v,int w,int s){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u],E[cnt].w=w,E[cnt].s=s;
	last[u]=cnt;
}
double dis[151][501];
int pre[151][501];
bool flag[151*512]={};
int enc(int a,int b){
	return a<<9|b;
}
void dec(int c,int& a,int& b){
	a=c>>9;
	b=c&511;
}
void SPFA(int n,int maxv){
	for(int i=0;i<n;++i)
		for(int j=1;j<=maxv;++j)
			dis[i][j]=1e10;
	dis[0][70]=0.0;
	std::queue<int> q;
	q.push(enc(0,70));
	int u,lv;
	while(q.size()){
		int src=q.front();q.pop();
		flag[src]=false;
		dec(src,u,lv);
		for(int i=last[u];i;i=E[i].next){
			int cv=(E[i].s?E[i].s:lv),v=E[i].to;
			double d=dis[u][lv]+static_cast<double>(E[i].w)/cv;
			if(d<dis[v][cv]){
				dis[v][cv]=d;
				pre[v][cv]=src;
				int id=enc(v,cv);
				if(!flag[id]){
					flag[id]=true;
					q.push(id); 
				}
			}
		}
	} 
}
int main(){
	int n=read();
	int m=read();
	int d=read();
	int u,v,w,s,maxv=70;
	for(int i=0;i<m;++i){
		u=read();
		v=read();
		s=read();
		w=read();
		addEdge(u,v,w,s);
		if(s>maxv)maxv=s;
	}
	
	SPFA(n,maxv);
	double mind=1e10;
	for(int i=1;i<=maxv;++i)
		if(dis[d][i]<mind)
			mind=dis[d][i],v=i;
	std::stack<int> st;
	st.push(d); 
	while(d){
		dec(pre[d][v],d,v);
		st.push(d);
	}
	while(st.size()){
		printf("%d ",st.top());
		st.pop();
	}
	return 0;	
}

