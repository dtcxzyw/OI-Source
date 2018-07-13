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
const int size=200001,mod=19260817;
int off[size],c[size],sc[size<<2],lc[size<<2],rc[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int dist(int l,int r){
	return ((off[r]-off[l])%mod+mod)%mod;
}
void build(int l,int r,int id){
	if(l==r){
		sc[id]=c[l];
		lc[id]=rc[id]=0;
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sc[id]=(sc[id<<1]+sc[id<<1|1])%mod;
		lc[id]=(lc[id<<1]+lc[id<<1|1]+1LL*sc[id<<1|1]*dist(l,m+1)%mod)%mod;
		rc[id]=(rc[id<<1]+1LL*sc[id<<1]*dist(m,r)%mod+rc[id<<1|1])%mod;
	}
}
int query(int l,int r,int id,int x,int nl,int nr){
	if(nl<=l && r<=nr){
		if(x<=l) return (lc[id]+1LL*sc[id]*dist(x,l)%mod)%mod;
		else if(x>=r) return (rc[id]+1LL*sc[id]*dist(r,x)%mod)%mod;
		return (query(l,r,id,x,nl,x-1)+query(l,r,id,x,x+1,nr))%mod;
	}
	else{
		int m=(l+r)>>1,res=0;
		if(nl<=m)res+=query(ls,x,nl,nr);
		if(m<nr)res+=query(rs,x,nl,nr);
		return res%mod;
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=2;i<=n;++i)
		off[i]=(off[i-1]+read())%mod;
	for(int i=1;i<=n;++i)
		c[i]=read()%mod;
	build(1,n,1);
	int x,l,r;
	for(int i=0;i<m;++i){
	    x=read();
		l=read();
		r=read();
		printf("%d\n",query(1,n,1,x,l,r));	
	}
	return 0;
}

