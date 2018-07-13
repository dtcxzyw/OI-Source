#include <cstdio>
#include <algorithm>
const int size=20001<<2;
int siz[size],lsiz[size],rsiz[size];
bool flag[size]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	siz[id]=lsiz[id]=rsiz[id]=1;
	if(l!=r){
		int m=(l+r)>>1;
		build(ls);
		build(rs);
	}
}
void update(int l,int r,int id,int x){
	if(l!=r){
		int m=(l+r)>>1;
		if(x<=m)update(ls,x);
		else update(rs,x);
		lsiz[id]=lsiz[id<<1];
		if(flag[m]^flag[m+1] && lsiz[id]==m-l+1)lsiz[id]+=lsiz[id<<1|1];
		rsiz[id]=rsiz[id<<1|1];
		if(flag[m]^flag[m+1] && rsiz[id]==r-m)rsiz[id]+=rsiz[id<<1];
		siz[id]=std::max(siz[id<<1],siz[id<<1|1]);
		if(flag[m]^flag[m+1])
			siz[id]=std::max(siz[id],rsiz[id<<1]+lsiz[id<<1|1]);
	}
}
int main(){
	int n,m,x;
	scanf("%d%d",&n,&m);
	build(1,n,1);
	for(int i=1;i<=m;++i){
		scanf("%d",&x);
		flag[x]=!flag[x];
		update(1,n,1,x);
		printf("%d\n",siz[1]);
	}
	return 0;
}

