#include <cstdio>
const int size=1001;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int num[size<<2|1];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int id){
	num[id]=gcd(num[id<<1],num[id<<1|1]);
}
void build(int l,int r,int id){
	if(l==r)scanf("%d",&num[id]);
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l&&r<=nr)return num[id];
	else{
		int m=(l+r)>>1;
		if(nl<=m && m<nr)return gcd(query(ls,nl,nr),query(rs,nl,nr));
		else if(nl<=m)return query(ls,nl,nr);
		else return query(rs,nl,nr);
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	build(1,n,1);
	int l,r;
	for(int i=0;i<m;++i){
		scanf("%d%d",&l,&r);
		printf("%d\n",query(1,n,1,l,r));
	}
	return 0;
}

