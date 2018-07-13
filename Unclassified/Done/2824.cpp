#include <cstdio>
#include <cstring>
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
const int size=100100;
int A[size],sum[size<<2],lazy[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int nl,nr,arg;
void build(int l,int r,int id){
	lazy[id]=-1;
	if(l==r)sum[id]=(A[l]>=arg);
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
void color(int l,int r,int id,int val){
	lazy[id]=val;
	sum[id]=(val?r-l+1:0);
}
void push(int l,int r,int id){
	if(lazy[id]!=-1){
		int m=(l+r)>>1;
		color(ls,lazy[id]);
		color(rs,lazy[id]);
		lazy[id]=-1;
	}
}
void modify(int l,int r,int id){
	if((arg?r-l+1:0)==sum[id])return;
	if(nl<=l && r<=nr)color(l,r,id,arg);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
int query(int l,int r,int id){
	if(nl<=l && r<=nr)return sum[id];
	else{
		if(sum[id]==0)return 0;
		push(l,r,id);
		int m=(l+r)>>1,res=0;
		if(nl<=m)res+=query(ls);
		if(m<nr)res+=query(rs);
		return res;
	}
}
void modify(int n,int l,int r,int x){
	if(l<=r){
		nl=l,nr=r,arg=x;
		modify(1,n,1);
	}
}
struct Op{
	int op,l,r;
} Q[size];
bool check(int n,int m,int x,int q){
	arg=x;
	build(1,n,1);
	for(int i=0;i<m;++i){
		nl=Q[i].l,nr=Q[i].r;
		int num=query(1,n,1);
		if(Q[i].op){
			modify(n,Q[i].l,Q[i].l+num-1,1);
			modify(n,Q[i].l+num,Q[i].r,0);
		}
		else{
			modify(n,Q[i].l,Q[i].r-num,0);
			modify(n,Q[i].r-num+1,Q[i].r,1);
		}
	}
	nl=q,nr=q;
	return query(1,n,1);
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)A[i]=read();
	for(int i=0;i<m;++i){
		Q[i].op=read();
		Q[i].l=read();
		Q[i].r=read();
	}
	int q=read();
	int l=1,r=n,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(n,m,mid,q))l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

