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
bool getCode(){
	int c;
	do c=getchar();
	while(c!='A' && c!='L');
	return c=='A';
}
const int size=500001;
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int lsiz[size<<2],rsiz[size<<2],siz[size<<2],flag[size<<2];
void build(int l,int r,int id){
	lsiz[id]=rsiz[id]=siz[id]=r-l+1;
	flag[id]=-1;
	if(l!=r){
		int m=(l+r)>>1;
		build(ls);
		build(rs);
	}
}
void color(int l,int r,int id,int f){
	flag[id]=f;
	lsiz[id]=rsiz[id]=siz[id]=(f?0:r-l+1);
}
void update(int l,int r,int id){
	lsiz[id]=lsiz[id<<1];
	rsiz[id]=rsiz[id<<1|1];
	int m=(l+r)>>1,ll=m-l+1,rl=r-m;
	if(lsiz[id]==ll)lsiz[id]+=lsiz[id<<1|1];
	if(rsiz[id]==rl)rsiz[id]+=rsiz[id<<1];
	siz[id]=std::max(std::max(siz[id<<1],siz[id<<1|1]),rsiz[id<<1]+lsiz[id<<1|1]);
}
void push(int l,int r,int id){
	if(flag[id]!=-1){
		int m=(l+r)>>1;
		color(ls,flag[id]);
		color(rs,flag[id]);
		flag[id]=-1;
	}	
}
void modify(int l,int r,int id,int nl,int nr,int f){
	if(nl<=l&&r<=nr)color(l,r,id,f);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,f);
		if(nr>m)modify(rs,nl,nr,f);
		update(l,r,id);
	}
}
int query(int l,int r,int id,int len){
	if(l==r)return l;
	push(l,r,id);
	int m=(l+r)>>1;
	if(siz[id<<1]>=len)return query(ls,len);
	if(rsiz[id<<1]+lsiz[id<<1|1]>=len)return m-rsiz[id<<1]+1;
	return query(rs,len);
}
int main(){
	int n=read();
	int m=read();
	int x,y,ans=0;
	build(1,n,1);
	for(int i=0;i<m;++i)
		if(getCode()){
			x=read();
			if(siz[1]>=x){
				int l=query(1,n,1,x);
				modify(1,n,1,l,l+x-1,1);
			}
			else ++ans;
		}
		else{
			x=read();
			y=read();
			modify(1,n,1,x,y,0);
		}
	printf("%d\n",ans);
	return 0;
}

