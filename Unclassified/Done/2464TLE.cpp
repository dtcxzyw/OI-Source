#include <cstdio>
#include <set>
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
	int c;
	do c=getchar();
	while(c!='C'&&c!='Q');
	return c;
}
const int size=100100;
std::multiset<int> seg[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int A[size];
void build(int l,int r,int id){
	seg[id].insert(A+l,A+r+1);
	if(l!=r){
		int m=(l+r)>>1;
		build(ls);
		build(rs);
	}
}
int p,k,old;
void modify(int l,int r,int id){
	seg[id].insert(k);
	seg[id].erase(seg[id].find(old));
	if(l!=r){
		int m=(l+r)>>1;
		if(p<=m)modify(ls);
		else modify(rs);
	}
}
int nl,nr,ans;
void query(int l,int r,int id){
	int cnt=seg[id].count(k);
	if(nl<=l && r<=nr)ans+=cnt;
	else if(cnt){
		int m=(l+r)>>1;
		if(nl<=m)query(ls);
		if(m<nr)query(rs);
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)
		A[i]=read();
	build(1,n,1);
	for(int i=0;i<m;++i)
		if(getOp()=='C'){
			p=read();
			k=read();
			old=A[p];
			if(k!=old){
				A[p]=k;
				modify(1,n,1);
			}
		}
		else{
			nl=read();
			nr=read();
			k=read();
			ans=0;
			query(1,n,1);
			printf("%d\n",ans);
		}
	return 0;
}

