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
//²î·Ö 
const int size=100005;
long long S[size]={};
void add(int x,int n,long long v){
	while(x<=n){
		S[x]+=v;
		x+=x&-x;
	}
}
long long query(int x){
	long long res=0;
	while(x){
		res+=S[x];
		x-=x&-x;
	}
	return res;
}
int A[size],B[size];
long long maxv[size<<2],lazy[size<<2]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r)maxv[id]=B[l];
	else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		maxv[id]=std::max(A[l-1]+maxv[id<<1],A[m]+maxv[id<<1|1]);
	}
}
int nl,nr,t;
void modify(int l,int r,int id){
	if(nl<=l && r<=nr){
		
	}
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
	}
}
void swap(int l,int r,int id,int a,int b){
	
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)A[i]=read();
	for(int i=1;i<=n;++i){
		B[i]=A[i]-A[i-1];
		add(i,n,B[i]);
	}
	build(1,n,1);
	
	return 0;
}

