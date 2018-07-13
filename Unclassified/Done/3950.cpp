#include <cstdio>
#include <cstring>
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
int getOp(){
	int c;
	do c=getchar();
	while(c!='Q' && c!='C' && c!='U');
	return c;
}
const int size=300001;
struct Edge{
	int to,next;
} E[size*2];
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
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!d[v]){
			p[v]=u;
			DFS(v);
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
}
int top[size],id[size],pcnt=0;
void buildChain(int u){
	id[u]=++pcnt;
	if(son[u]){
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
bool val[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int x,bool v){
	if(l==r)val[id]=v;
	else{
		int m=(l+r)>>1;
		if(x<=m)modify(ls,x,v);
		else modify(rs,x,v);
		val[id]=val[id<<1]&val[id<<1|1];
	}
}
bool query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return val[id];
	else{
		int m=(l+r)>>1;
		bool res=true;
		if(nl<=m)res&=query(ls,nl,nr);
		if(res && m<nr)res&=query(rs,nl,nr);
		return res;
	}
}
bool query(int u,int v,int n){
	bool res=true;
	while(res){
		if(top[u]==top[v]){
			if(d[u]>d[v])std::swap(u,v);
			if(u!=v)res&=query(1,n,1,id[son[u]],id[v]);
			return res;
		}
		else{
			if(d[top[u]]<d[top[v]])std::swap(u,v);
			res&=query(1,n,1,id[top[u]],id[u]);
			u=p[top[u]];
		}
	}
	return res;
}
int history[size],hcnt=0;
int main(){
	int n=read();
	int m=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	top[1]=1;
	buildChain(1);
	memset(val,0xff,sizeof(val));
	int op,x;
	for(int i=0;i<m;++i){
		op=getOp();
		if(op=='U')modify(1,n,1,history[read()],true);
		else{
			u=read();
			v=read();
			if(op=='Q')puts(query(u,v,n)?"Yes":"No");
			else{
				if(d[u]>d[v])std::swap(u,v);
				history[++hcnt]=id[v];
				modify(1,n,1,id[v],false);
			}
		}
	}
	return 0;
}

