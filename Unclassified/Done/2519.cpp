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
const int size=101000;
struct Info{
	int l,r;
	bool operator<(Info rhs) const{
		return l==rhs.l?r<rhs.r:l<rhs.l;
	}
} A[size];
struct Seg{
	int l,r,w;
	bool operator<(Seg rhs) const{
		return r==rhs.r?l<rhs.l:r<rhs.r;
	}
} seg[size];
int find(int x,int siz){
	int l=1,r=siz,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(seg[mid].r<x)res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
int dp[size]={};
int main(){
	int n=read(),icnt=0;
	for(int i=0;i<n;++i){
		int a=read();
		int b=read();
		int l=a+1,r=n-b;
		if(l<=r){
			A[icnt].l=l;
			A[icnt].r=r;
			++icnt;
		}
	}
	std::sort(A,A+icnt);
	int scnt=0;
	for(int i=0;i<icnt;++i){
		if(seg[scnt].l==A[i].l && seg[scnt].r==A[i].r)++seg[scnt].w;
		else{
			++scnt;
			seg[scnt].l=A[i].l;
			seg[scnt].r=A[i].r;
			seg[scnt].w=1;
		}
		seg[scnt].w=std::min(seg[scnt].w,seg[scnt].r-seg[scnt].l+1);
	}
	std::sort(seg+1,seg+scnt+1);
	for(int i=1;i<=scnt;++i){
		int j=find(seg[i].l,i-1);
		dp[i]=std::max(dp[i-1],dp[j]+seg[i].w);
	}
	printf("%d\n",n-dp[scnt]);
	return 0;
}

