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
bool flag[200000<<2|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int nl,int nr){
	if(flag[id])return;
	if(nl<=l && r<=nr)flag[id]=true;
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr);
		if(m<nr)modify(rs,nl,nr);
		flag[id]=flag[id<<1]&flag[id<<1|1];
	}
}
int query(int l,int r,int id){
	if(flag[id])return r-l+1;
	else if(l<r){
		int m=(l+r)>>1;
		return query(ls)+query(rs);
	}
	return flag[id];
}
int main(){
	int n,m;
	n=read();
	m=read();
	int l,r;
	for(int i=0;i<m;++i){
		l=read();
		r=read();
		modify(1,n,1,l,r);
		printf("%d\n",n-query(1,n,1));
	}
	return 0;
}

