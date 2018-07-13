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
void printImpl(int x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(int x){
	printImpl(x);
	putchar('\n');
}
const int size=100001<<2;
int sum[size],siz[size][2],lsiz[size][2],rsiz[size][2],flag[size];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int l,int r,int id){
	sum[id]=sum[id<<1]+sum[id<<1|1];
	int m=(l+r)>>1,ln=m-l+1,rn=r-m;
	for(int i=0;i<2;++i){
		lsiz[id][i]=lsiz[id<<1][i];
		if(lsiz[id][i]==ln)lsiz[id][i]+=lsiz[id<<1|1][i];
		rsiz[id][i]=rsiz[id<<1|1][i];
		if(rsiz[id][i]==rn)rsiz[id][i]+=rsiz[id<<1][i];
		siz[id][i]=std::max(std::max(siz[id<<1][i],siz[id<<1|1][i]),rsiz[id<<1][i]+lsiz[id<<1|1][i]);
	}
}
void build(int l,int r,int id){
	flag[id]=-1;
	if(l==r){
		int x=read();
		sum[id]=siz[id][1]=lsiz[id][1]=rsiz[id][1]=x;
		siz[id][0]=lsiz[id][0]=rsiz[id][0]=1-x;
	}
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		update(l,r,id);
	}
}
void push(int l,int r,int id);
void color(int l,int r,int id,int op){
	if(op==2){
		flag[id]=1-flag[id];
		sum[id]=r-l+1-sum[id];
		std::swap(lsiz[id][0],lsiz[id][1]);
		std::swap(rsiz[id][0],rsiz[id][1]);
		std::swap(siz[id][0],siz[id][1]);
	}
	else{
		flag[id]=op;
		sum[id]=siz[id][1]=lsiz[id][1]=rsiz[id][1]=(op?r-l+1:0);
		siz[id][0]=lsiz[id][0]=rsiz[id][0]=(op?0:r-l+1);
	}
}
void push(int l,int r,int id){
	if(flag[id]!=-1){
		int m=(l+r)>>1;
		color(ls,flag[id]);
		color(rs,flag[id]);
		flag[id]=-1;
	}
}
int nl,nr,op;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)color(l,r,id,op);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		update(l,r,id);
	}
}
int query1(int l,int r,int id){
	if(nl<=l && r<=nr)return sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1,ans=0;
		if(nl<=m)ans+=query1(ls);
		if(m<nr)ans+=query1(rs);
		return ans;
	}
}
int query2(int l,int r,int id){
	if(nl<=l && r<=nr)return siz[id][1];
	else{
		push(l,r,id);
		int m=(l+r)>>1,ans=0;
		if(nl<=m)ans=std::max(ans,query2(ls));
		if(m<nr)ans=std::max(ans,query2(rs));
		if(nl<=m && m<nr){
			int ml=m-std::max(nl,l)+1,mr=std::min(nr,r)-m;
			ans=std::max(ans,std::min(rsiz[id<<1][1],ml)+std::min(lsiz[id<<1|1][1],mr));
		}
		return ans;
	}
}
int main(){
	int n=read();
	int m=read();
	build(1,n,1);
	for(int i=0;i<m;++i){
		op=read();
		nl=read()+1;
		nr=read()+1;
		if(op<=2)modify(1,n,1);
		else if(op==3)print(query1(1,n,1));
		else print(query2(1,n,1));
	}
	return 0;
}

