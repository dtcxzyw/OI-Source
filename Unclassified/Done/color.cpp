#include <cstdio>
#include <algorithm>
const int size=100001<<2;
int type[size]={},lazy[size]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void color(int id,int x){
	type[id]=lazy[id]=x;
}
void update(int id){
	type[id]=type[id<<1]|type[id<<1|1];
}
void push(int l,int r,int id){
	if(lazy[id]){
		int m=(l+r)>>1;
		color(id<<1,lazy[id]);
		color(id<<1|1,lazy[id]);
		lazy[id]=0;
	}
}
void modify(int l,int r,int id,int nl,int nr,int x){
	if(nl<=l && r<=nr)color(id,x);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,x);
		if(m<nr)modify(rs,nl,nr,x);
		update(id);
	}
}
void build(int l,int r,int id){
	if(l!=r){
		int m=(l+r)>>1;
		build(ls);
		build(rs);
	}
	type[id]=1<<1;
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return type[id];
	else{
		push(l,r,id);
		int ans=0;
		int m=(l+r)>>1;
		if(nl<=m)ans|=query(ls,nl,nr);
		if(m<nr)ans|=query(rs,nl,nr);
		return ans;
	}
}
int bitcount(int x,int t){
	int cnt=0;
	for(int i=1;i<=t;++i)
		cnt+=static_cast<bool>(x&(1<<i));
	return cnt;
}
int main(){
	int n,t,m;
	scanf("%d%d%d",&n,&t,&m);
	build(1,n,1);
	char c[2];
	int l,r,x;
	for(int i=0;i<m;++i){
		scanf("%s%d%d",c,&l,&r);
		if(l>r)std::swap(l,r);
		if(*c=='C'){
			scanf("%d",&x);
			modify(1,n,1,l,r,1<<x);
		}
		else 
			printf("%d\n",bitcount(query(1,n,1,l,r),t));
	}
	return 0;
}

