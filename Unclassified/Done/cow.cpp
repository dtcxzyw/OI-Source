#include <cstdio>
#include <algorithm>
struct Request{
	int l,r;
	bool operator<(Request rhs) const{
		return r<rhs.r;
	}
} orders[100000];
const int size=100001<<2|1;
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int minv[size],offset[size]={};
void update(int id){
	minv[id]=std::min(minv[id<<1],minv[id<<1|1])-offset[id];
}
void modify(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)++offset[id],--minv[id];
	else{
		int m=(l+r)>>1;
		if(m>=nl)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		update(id);
	}	
}

void build(int l,int r,int id){
	if(l==r)
	    scanf("%d",&minv[id]);
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(id);
	}
}

int query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return minv[id];
	else{
		int m=(l+r)>>1,ans=1000000000;
		if(m>=nl)ans=query(ls,nl,nr)-offset[id];
		if(m<nr && ans>0)ans=std::min(ans,query(rs,nl,nr)-offset[id]);
		return ans;
	}	
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	build(1,n,1);
	for(int i=0;i<m;++i)
	    scanf("%d%d",&orders[i].l,&orders[i].r);
	std::sort(orders,orders+m);
	int ans=0;
	for(int i=0;i<m;++i)
		if(query(1,n,1,orders[i].l,orders[i].r)>0)
			modify(1,n,1,orders[i].l,orders[i].r),++ans;
			
	printf("%d\n",ans);
	return 0;
}

