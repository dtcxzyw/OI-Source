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
const int size=500005;
int A[size],r,B[size];
int get(int x,int y){
	if(x&&y)return y*r+x;
	return 0;
}
struct Node{
	int l,r,siz,sum;
} T[size*50];
int tcnt=0;
int build(int l,int r,int a,int b,int c,int k){
	int id=++tcnt;
	T[id].siz=T[a].siz+T[b].siz-T[c].siz;
	T[id].sum=T[a].sum+T[b].sum-T[c].sum;
	if(l<=k && k<=r)++T[id].siz,T[id].sum+=B[k];
	if(l!=r){
		int m=(l+r)>>1;
		T[id].l=build(l,m,T[a].l,T[b].l,T[c].l,k);
		T[id].r=build(m+1,r,T[a].r,T[b].r,T[c].r,k);
	}
	return id;
}
int getSiz(int id){
	return T[T[id].r].siz;
}
int getSum(int id){
	return T[T[id].r].sum;
}
int query(int l,int r,int a,int b,int c,int d,int k){
	if(l==r)return B[l]*k;
	else{
		int m=(l+r)>>1;
		int rsiz=getSiz(a)-getSiz(b)-getSiz(c)+getSiz(d);
		if(rsiz>=k)return query(m+1,r,T[a].r,T[b].r,T[c].r,T[d].r,k);
		return getSum(a)-getSum(b)-getSum(c)+getSum(d)+query(l,m,T[a].l,T[b].l,T[c].l,T[d].l,k-rsiz); 
	}
}
int root[size]={};
int main(){
	r=read();
	int c=read();
	int m=read();
	int siz=0;
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
			B[++siz]=A[get(i,j)]=read();
	std::sort(B+1,B+siz+1);
	siz=std::unique(B+1,B+siz+1)-(B+1);
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j){
			int pos=std::lower_bound(B+1,B+siz+1,A[get(i,j)])-B;
			root[get(i,j)]=build(1,siz,root[get(i-1,j)],root[get(i,j-1)],root[get(i-1,j-1)],pos);
		}
	for(int i=0;i<m;++i){
		int bx=read()-1;
		int by=read()-1;
		int ex=read();
		int ey=read();
		int h=read();
		int a=root[get(ex,ey)],b=root[get(ex,by)],c=root[get(bx,ey)],d=root[get(bx,by)];
		int l=1,r=(ex-bx)*(ey-by),ans=-1;
		while(l<=r){
			int m=(l+r)>>1;
			int maxv=query(1,siz,a,b,c,d,m);
			if(maxv>=h)ans=m,r=m-1;
			else l=m+1;
		}
		if(ans==-1)puts("Poor QLW");
		else printf("%d\n",ans);
	}
	return 0;
}

