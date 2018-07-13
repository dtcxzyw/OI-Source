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
const int qsiz=300100,size=qsiz*3;
int siz[size<<2],sum[size<<2],lazy[size<<3]={},key[size];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)sum[id]=siz[id]=key[l]-key[l-1];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
		siz[id]=siz[id<<1]+siz[id<<1|1];
	}
}
void color(int id,int k){
	lazy[id]=k;
	sum[id]=(k==1?0:siz[id]);
}
void push(int id){
	if(lazy[id]){
		color(id<<1,lazy[id]);
		color(id<<1|1,lazy[id]);
		lazy[id]=0;
	}
}
int k,nl,nr;
void modify(int l,int r,int id){
	if(sum[id]==siz[id] && k==2)return;
	if(sum[id]==0 && k==1)return;
	if(nl<=l && r<=nr)color(id,k);
	else{
		push(id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
struct Query{
	int k,l,r;
} Q[qsiz];
int main(){
	int n=read();
	int q=read();
	int cnt=0;
	key[cnt++]=1;
	key[cnt++]=n+1;
	for(int i=0;i<q;++i){
		Q[i].l=read();
		key[cnt++]=Q[i].l;
		Q[i].r=read();
		key[cnt++]=Q[i].r+1;
		Q[i].k=read();
	}
	std::sort(key,key+cnt);
	cnt=std::unique(key,key+cnt)-key;
	build(1,cnt-1,1);
	for(int i=0;i<q;++i){
		k=Q[i].k;
		nl=std::lower_bound(key,key+cnt,Q[i].l)-key+1;
		nr=std::upper_bound(key,key+cnt,Q[i].r)-key;
		modify(1,cnt-1,1);
		printf("%d\n",sum[1]);
	}
	return 0;
}

