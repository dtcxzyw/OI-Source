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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	if(x<0)x=-x;
	printImpl(x);
	putchar('\n');
}
int getOp(){
	int c,res;
	do c=getchar();
	while(c!='u' && c!='i');
	res=c;
	do c=getchar();
	while('a'<=c&&c<='z');
	return res;
}
const int size=100001;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int d[size],p[size],siz[size],son[size];
void DFS(int u){
	d[u]=d[p[u]]+1;
	siz[u]=1;
	son[u]=-1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		p[v]=u;
		DFS(v);
		siz[u]+=siz[v];
		if(son[u]==-1 || siz[v]>siz[son[u]])
			son[u]=v;
	}
}
int top[size],id[size],pcnt=0;
void buildChain(int u){
	id[u]=++pcnt;
	if(son[u]!=-1){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!id[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
//1->uninstall 2->install
int sum[size<<2]={},mark[size<<2]={};
void color(int l,int r,int id,int flag){
	mark[id]=flag;
	sum[id]=(flag==1?0:(r-l+1));
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void push(int l,int r,int id){
	if(mark[id]){
		int m=(l+r)>>1;
		color(ls,mark[id]);
		color(rs,mark[id]);
		mark[id]=0;
	}
}
int nl,nr,flag;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,flag);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
int main(){
	int n=read();
	for(int i=1;i<n;++i)
		addEdge(read(),i);
	DFS(0);
	buildChain(0);
	p[0]=-1;
	int m=read(),x,op;
	for(int i=0;i<m;++i){
		op=getOp();
		x=read();
		int old=sum[1];
		if(op=='i'){
			flag=2;
			do{
				nl=id[top[x]],nr=id[x];
				modify(1,n,1);
				x=p[top[x]];
			}while(x!=-1);
		}
		else{
			flag=1;
			nl=id[x],nr=id[x]+siz[x]-1;
			modify(1,n,1);
		}
		print(sum[1]-old);
	}
	return 0;
}

