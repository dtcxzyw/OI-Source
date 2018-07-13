#include <cstdio>
const int size=100001<<2|1;
int sum[size]={};
bool lazy[size]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int id){
	sum[id]=sum[id<<1]+sum[id<<1|1];
}
void color(int l,int r,int id){
	sum[id]=r-l+1-sum[id];
	lazy[id]=!lazy[id];
}
void push(int l,int r,int id){
	if(lazy[id]){
		int m=(l+r)>>1;
		color(ls);
		color(rs);
		lazy[id]=false;
	}
}
void modify(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)color(l,r,id);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		update(id);
	}
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1,ans=0;
		if(nl<=m)ans+=query(ls,nl,nr);
		if(m<nr)ans+=query(rs,nl,nr);
		return ans;
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int c,l,r;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&c,&l,&r);
		if(c==0)modify(1,n,1,l,r);
		else printf("%d\n",query(1,n,1,l,r));
	}
	return 0;	
}


