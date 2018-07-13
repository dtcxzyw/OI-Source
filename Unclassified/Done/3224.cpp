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
	while(c!='B'&&c!='Q');
	return c;
}
const int size=100100,tsiz=size*50;
struct Node{
	int cnt,ls,rs;
} seg[tsiz];
#define lc l,m,seg[id].ls
#define rc m+1,r,seg[id].rs
int ncnt=0;
void insert(int l,int r,int& id,int k){
	if(!id)id=++ncnt;
	++seg[id].cnt;
	if(l!=r){
		int m=(l+r)>>1;
		if(k<=m)insert(lc,k);
		else insert(rc,k);
	}
}
int query(int l,int r,int id,int k){
	if(l==r)return l;
	int m=(l+r)>>1,lsiz=seg[seg[id].ls].cnt;
	if(k<=lsiz)return query(lc,k);
	return query(rc,k-lsiz);
}
int merge(int u,int v){
	if(u&&v){
		seg[u].ls=merge(seg[u].ls,seg[v].ls);
		seg[u].rs=merge(seg[u].rs,seg[v].rs);
		seg[u].cnt+=seg[v].cnt;
		return u;
	}
	return u|v;
}
int fa[size],root[size]={};
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int val[size],map[size];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		val[i]=read();
		fa[i]=map[val[i]]=i;
	}
	for(int i=0;i<m;++i){
		int u=find(read()),v=find(read());
		if(u!=v)fa[u]=v;
	}
	for(int i=1;i<=n;++i){
		int u=find(i);
		insert(1,n,root[u],val[i]);
	}
	int q=read();
	for(int i=0;i<q;++i)
		if(getOp()=='B'){
			int u=find(read()),v=find(read());
			if(u!=v){
				root[u]=merge(root[u],root[v]);
				fa[v]=u;
			}
		}
		else{
			int u=find(read());
			int k=read();
			if(seg[root[u]].cnt<k)puts("-1");
			else printf("%d\n",map[query(1,n,root[u],k)]);
		}
	return 0;
}

