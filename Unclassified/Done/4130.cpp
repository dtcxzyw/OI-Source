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
	int c,res=0;
	do c=getchar();
	while(c<'A'||c>'Z');
	while('A'<=c&&c<='Z'){
		res=res^c;
		c=getchar();
	}
	return res;
}
const int size=500005;
struct Info{
	int lc,rc,cnt;
	Info(){}
	Info(int lc,int rc,int cnt):lc(lc),rc(rc),cnt(cnt){}
	int size() const{
		return cnt?cnt+2:1+(lc!=rc);
	}
} A[size<<2];
int lazy[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
Info merge(const Info& lhs,const Info& rhs){
	if(lhs.size()!=1){
		if(rhs.size()!=1)return Info(lhs.lc,rhs.rc,lhs.cnt+rhs.cnt+1+(lhs.rc!=rhs.lc));
		else return Info(lhs.lc,rhs.rc,lhs.cnt+(lhs.rc!=rhs.lc));
	}
	else{
		if(rhs.size()!=1)return Info(lhs.lc,rhs.rc,rhs.cnt+(lhs.rc!=rhs.lc));
		else return Info(lhs.rc,rhs.lc,0);
	}
}
void build(int l,int r,int id){
	if(l==r){
		A[id].lc=A[id].rc=read();
		A[id].cnt=0;
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		A[id]=merge(A[id<<1],A[id<<1|1]);
	}
}
void color(int id,int c){
	A[id].lc=A[id].rc=c;
	A[id].cnt=0;
	lazy[id]=c;
}
void push(int id){
	if(lazy[id]){
		color(id<<1,lazy[id]);
		color(id<<1|1,lazy[id]);
		lazy[id]=0;
	}
}
void modify(int l,int r,int id,int nl,int nr,int c){
	if(nl<=l && r<=nr)color(id,c);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,c);
		if(m<nr)modify(rs,nl,nr,c);
		A[id]=merge(A[id<<1],A[id<<1|1]);
	}
}
Info query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return A[id];
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m){
			if(m<nr)return merge(query(ls,nl,nr),query(rs,nl,nr));
			return query(ls,nl,nr);
		}
		return query(rs,nl,nr);
	}
}
int map(int x,int first,int r,int n){
	return ((first+r*(x-1)-1)%n+n)%n+1;
}
int main(){
	int n=read();
	read();
	build(1,n,1);
	int q=read();
	int r=1,first=1;
	while(q--){
		switch(getOp()){
			case 'R':{
				int k=read();
				first=map(1-k,first,r,n);
				break;
			}
			case 'F':{
				r=-r;
				break;
			}
			case 'S':{
				int i=map(read(),first,r,n);
				int j=map(read(),first,r,n);
				int ic=query(1,n,1,i,i).lc;
				int jc=query(1,n,1,j,j).lc;
				modify(1,n,1,i,i,jc);
				modify(1,n,1,j,j,ic);
				break;
			}
			case 'P':{
				int i=map(read(),first,r,n);
				int j=map(read(),first,r,n);
				int c=read();
				if(r==1){
					if(i<=j)modify(1,n,1,i,j,c);
					else{
						modify(1,n,1,i,n,c);
						modify(1,n,1,1,j,c);
					}
				}
				else{
					if(j<=i)modify(1,n,1,j,i,c);
					else{
						modify(1,n,1,1,i,c);
						modify(1,n,1,j,n,c);
					}
				}
				break;
			}
			case 'C':{
				Info res=query(1,n,1,1,n);
				printf("%d\n",res.cnt+1+(res.lc!=res.rc));
				break;
			}
			case 'C'^'S':{
				int i=map(read(),first,r,n);
				int j=map(read(),first,r,n);
				Info res;
				if(r==1){
					if(i<=j)res=query(1,n,1,i,j);
					else res=merge(query(1,n,1,i,n),query(1,n,1,1,j));
				}
				else{
					if(j<=i)res=query(1,n,1,j,i);
					else res=merge(query(1,n,1,j,n),query(1,n,1,1,i));
				}
				printf("%d\n",res.size());
				break;
			}
		}
	}
	return 0;
}

