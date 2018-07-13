#include <cstdio>
#include <algorithm>
const int size=50020;
int t[size],w[size],maxv[size<<2|1];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)maxv[id]=w[l];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		maxv[id]=std::max(maxv[id<<1],maxv[id<<1|1]);
	}	
}
int query(int l,int r,int id,int nl,int nr){
	if(nl<=l&&r<=nr)
		return maxv[id];
	else{
		int m=(l+r)>>1,v=0;
		if(nl<=m)v=std::max(v,query(ls,nl,nr));
		if(m<nr)v=std::max(v,query(rs,nl,nr));
		return v;
	}
}
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		t[i]=read();
		w[i]=read();
	}
	build(1,n,1);
	int m=read(),l,r;
	for(int i=0;i<m;++i){
		l=read();
		r=read();
		int lp=std::lower_bound(t+1,t+n+1,l)-t;
		int rp=std::lower_bound(t+1,t+n+1,r)-t;
		if(t[lp]==l && t[rp]==r){
			if(w[lp]>=w[rp]){
				if(lp+1==rp)puts(l+1==r?"true":"maybe");
				else{
					if(query(1,n,1,lp+1,rp-1)<w[rp])puts(rp-lp==r-l?"true":"maybe");
					else puts("false");
				}
			}
			else puts("false");
		}
		else if(t[lp]==l){
			if(lp+1==rp)puts("maybe");
			else{
				int maxv=query(1,n,1,lp+1,rp-1);
				puts(w[lp]>maxv?"maybe":"false");
			}
		}
		else if(t[rp]==r){
			if(lp==rp)puts("maybe");
			else{
				if(query(1,n,1,lp,rp-1)<w[rp])puts("maybe");
				else puts("false");
			}
		}
		else puts("maybe");
	}
	return 0;
}

