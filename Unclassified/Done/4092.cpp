#include <cstdio>
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
int getOp(){
	int c;
	do c=getchar();
	while(c!='C'&&c!='Q');
	return c;
}
int maxv(int a,int b){
	return a>b?a:b;
}
const int size=100100;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int p[size][18],d[size],siz[size],id[size],icnt=0;
void DFS(int u){
	id[u]=++icnt;
	siz[u]=1;
	for(int i=1;i<18;++i)
		p[u][i]=p[p[u][i-1]][i-1];
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(p[u][0]!=v){
			p[v][0]=u;
			d[v]=d[u]+1;
			DFS(v);
			siz[u]+=siz[v];
		}
	}
}
int maxd[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int val,nl,nr;
void modify(int l,int r,int id){
	if(maxd[id]>=val)return;
	if(nl<=l && r<=nr)maxd[id]=val;
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
	}
}
int k;
void query(int l,int r,int id){
	val=maxv(val,maxd[id]);
	if(l!=r){
		int m=(l+r)>>1;
		if(k<=m)query(ls);
		else query(rs);
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	siz[0]=0;
	DFS(1);
	for(int i=1;i<=n;++i){
		int op=getOp();
		int x=read();
		if(op=='C'){
			nl=id[x];
			nr=id[x]+siz[x]-1;
			val=d[x];
			modify(1,n,1);
		}
		else{
			k=id[x],val=0;
			query(1,n,1);
			int delta=d[x]-val;
			for(int i=0;i<18;++i)
				if(delta&(1<<i))
					x=p[x][i];
			printf("%d\n",x);
		}
	}
	return 0;
}

