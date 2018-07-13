#include <cstdio>
#include <queue>
#include <algorithm>
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
const int size=100005;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int d[size]={},p[size],siz[size]={},son[size]={};
void buildTree(int u){
	siz[u]=1;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			d[v]=d[u]+1;
			p[v]=u;
			buildTree(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
}
int top[size]={},icnt=0,id[size];
void buildChain(int u){
	id[u]=++icnt;
	if(son[u]){
		top[son[u]]=top[u];
		buildChain(son[u]);
	}
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!top[v]){
			top[v]=v;
			buildChain(v);
		}
	}
}
struct Seg{
	std::priority_queue<int> heap[2];
	int top(){
		while(heap[1].size() && heap[0].top()==heap[1].top())heap[0].pop(),heap[1].pop();
		return heap[0].empty()?-1:heap[0].top();
	}
} T[size<<2]; 
int nl,nr,val,op;
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modifyImpl(int l,int r,int id){
	if(nl<=l && r<=nr)T[id].heap[op].push(val);
	else{
		int m=(l+r)>>1;
		if(nl<=m)modifyImpl(ls);
		if(m<nr)modifyImpl(rs);
	}
}
void modify(int l,int r,int n){
	if(l<=r){
		nl=l,nr=r;
		modifyImpl(1,n,1);
	}
}
std::pair<int,int> range[size];
void modifyPath(int u,int v,int n){
	int rcnt=0;
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])std::swap(u,v);
		range[rcnt]=std::make_pair(id[top[u]],id[u]);
		++rcnt;
		u=p[top[u]];
	}
	if(d[u]>d[v])std::swap(u,v);
	range[rcnt]=std::make_pair(id[u],id[v]);
	++rcnt;
	std::sort(range,range+rcnt);
	int last=1;
	for(int i=0;i<rcnt;++i){
		modify(last,range[i].first-1,n);
		last=range[i].second+1;
	}
	modify(last,n,n);
}
int query(int l,int r,int id){
	int res=T[id].top();
	if(l!=r){
		int m=(l+r)>>1;
		if(val<=m)res=std::max(res,query(ls));
		else res=std::max(res,query(rs));
	}
	return res;
}
int A[size*2][3];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<n;++i){
		int u=read();
		int v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	d[1]=1;
	buildTree(1);
	top[1]=1;
	buildChain(1);
	for(int i=1;i<=m;++i)
		switch(read()){
			case 0:{
				A[i][0]=read();
				A[i][1]=read();
				A[i][2]=read();
				op=0;
				val=A[i][2];
				modifyPath(A[i][0],A[i][1],n);
			}break;
			case 1:{
				int t=read();
				op=1;
				val=A[t][2];
				modifyPath(A[t][0],A[t][1],n);
			}break;
			case 2:{
				val=id[read()];
				printf("%d\n",query(1,n,1));
			}break;
		}
	return 0;
}

