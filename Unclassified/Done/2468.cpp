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
int siz[201][201][1001],sum[201][201][1001];
void foo1(int R,int C,int m){
	for(int i=1;i<=R;++i)
		for(int j=1;j<=C;++j){
			int v=read();
			for(int k=1;k<=1000;++k){
				siz[i][j][k]=siz[i-1][j][k]+siz[i][j-1][k]-siz[i-1][j-1][k];
				sum[i][j][k]=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k];
			}
			for(int k=1;k<=v;++k)
				++siz[i][j][k],sum[i][j][k]+=v;
		}
	for(int i=0;i<m;++i){
		int bx=read()-1;
		int by=read()-1;
		int ex=read();
		int ey=read();
		int h=read();
		int l=1,r=1000,ans=-1;
		while(l<=r){
			int m=(l+r)>>1;
			if(sum[ex][ey][m]-sum[bx][ey][m]-sum[ex][by][m]+sum[bx][by][m]>=h)l=m+1,ans=m;
			else r=m-1; 
		}
		if(ans==-1)puts("Poor QLW");
		else{
			int delta=sum[ex][ey][ans]-sum[bx][ey][ans]-sum[ex][by][ans]+sum[bx][by][ans]-h;
			int cnt=siz[ex][ey][ans]-siz[bx][ey][ans]-siz[ex][by][ans]+siz[bx][by][ans];
			printf("%d\n",cnt-delta/ans);
		}
	}
}
const int size=500005;
struct Node{
	int l,r,siz,sum;
} T[size*12];
int tcnt=0;
int build(int l,int r,int s,int k){
	int id=++tcnt;
	T[id]=T[s];
	++T[id].siz;
	T[id].sum+=k;
	if(l!=r){
		int m=(l+r)>>1;
		if(k<=m)T[id].l=build(l,m,T[s].l,k);
		else T[id].r=build(m+1,r,T[s].r,k);
	}
	return id;
}
int getSiz(int id){
	return T[T[id].r].siz;
}
int getSum(int id){
	return T[T[id].r].sum;
}
int query(int l,int r,int a,int b,int k){
	if(l==r)return l*k;
	else{
		int m=(l+r)>>1;
		int rsiz=getSiz(a)-getSiz(b);
		if(rsiz>=k)return query(m+1,r,T[a].r,T[b].r,k);
		return getSum(a)-getSum(b)+query(l,m,T[a].l,T[b].l,k-rsiz); 
	}
}
int root[size]={};
void foo2(int n,int m){
	for(int i=1;i<=n;++i)
		root[i]=build(1,1000,root[i-1],read());
	for(int i=0;i<m;++i){
		int bx=read()-1;
		int by=read()-1;
		int ex=read();
		int ey=read();
		int h=read();
		int l=1,r=ey-by,ans=-1;
		while(l<=r){
			int m=(l+r)>>1;
			if(query(1,1000,root[ey],root[by],m)>=h)r=m-1,ans=m;
			else l=m+1;
		}
		if(ans==-1)puts("Poor QLW");
		else printf("%d\n",ans);
	}
}
int main(){
	int r=read();
	int c=read();
	int m=read();
	if(r>1)foo1(r,c,m);
	else foo2(c,m);
	return 0;
}

