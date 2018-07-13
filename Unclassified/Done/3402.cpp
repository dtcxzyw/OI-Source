#include <cstdio>
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
const int size=200005;
struct Seg{
	int l,r;
} T[size*20];
int p,val,ncnt=0;
#define ls l,m,T[id].l
#define rs m+1,r,T[id].r
void build(int l,int r,int& id){
	id=++ncnt;
	if(l==r)T[id].l=l,T[id].r=0;
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs); 
	}
}
void modify(int l,int r,int& id){
	T[ncnt+1]=T[id];
	id=++ncnt;
	if(l==r)T[id].l=val;
	else{
		int m=(l+r)>>1;
		if(p<=m)modify(ls);
		else modify(rs);
	}
}
void add(int l,int r,int id){
	if(l==r)++T[id].r;
	else{
		int m=(l+r)>>1;
		if(p<=m)add(ls);
		else add(rs);
	}
}
int query(int l,int r,int id){
	if(l==r)return id;
	else{
		int m=(l+r)>>1;
		if(p<=m)return query(ls);
		return query(rs);
	}
}
int cur,n;
int find(int u){
	p=u;
	int p=query(1,n,cur);
	return T[p].l==u?p:find(T[p].l);
}
int root[size];
int main(){
	n=read();
	int m=read();
	build(1,n,root[0]);
	for(int i=1;i<=m;++i)
		switch(read()){
			case 1:{
				cur=root[i]=root[i-1];
				int fu=find(read()),fv=find(read());
				if(T[fu].l!=T[fv].l){
					if(T[fu].r>T[fv].r)std::swap(fu,fv);
					p=T[fu].l,val=T[fv].l;
					modify(1,n,root[i]);
					if(T[fu].r==T[fv].r){
						p=T[fv].l;
						add(1,n,root[i]);
					}
				}
				cur=root[i];
			}break;
			case 2:{
				cur=root[i]=root[read()];
			}break;
			case 3:{
				cur=root[i]=root[i-1];
				puts(find(read())==find(read())?"1":"0");
			}break;
		}
	return 0;
}

