#include <cstdio>
#include <algorithm>
#include <vector>
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
const int size=100005,mod=1000000007;
long long inv(long long x){
	long long res=1;
	int k=mod-2;
	while(k){
		if(k&1)res=res*x%mod;
		k>>=1,x=x*x%mod;
	}
	return res;
}
long long inv6;
long long calcWeight(long long x,long long y){
	if(x>y)std::swap(x,y);
	long long sum1=(x*(x+1)>>1)%mod;
	long long sum2=inv6*x%mod*(x+1)%mod*(x<<1|1)%mod;
	return (x*(x+1)*(y+1)-(x+y+2)*sum1+sum2)%mod;
}
struct Block{
	int sum[size<<2],bx,ex,by,ey;
	typedef std::pair<int,int> Arg;
	Block(){
		memset(sum,0,sizeof(sum));
	}
	#define ls l,m,id<<1
	#define rs m+1,r,id<<1|1
	void color(int l,int r,int id,Arg arg){
		sum[id]=(sum[id]+(calcWeight(arg.first,r)-(l-1?calcWeight(arg.first,l-1):0))*arg.second)%mod;
		if(l!=r){
			int m=(l+r)>>1;
			color(ls,arg);
			color(rs,arg);
		}
	}
	int query(int l,int r,int id,int nl,int nr){
		if(nl<=l && r<=nr)return sum[id];
		else{
			int m=(l+r)>>1;
			int res=0;
			if(nl<=m)res+=query(ls,nl,nr);
			if(m<nr)res+=query(rs,nl,nr);
			return res%mod;
		}
	}
	void doModify(int l,int r,int val){
		color(1,ey-by+1,1,Arg(r,val));
		if(l!=1)color(1,ey-by+1,1,Arg(l-1,-val));
	}
	int doQuery(int l,int r){
		return query(1,ey-by+1,1,l,r);
	}
} T[2][2];
void doModify(int n,int l,int r,int val){
	for(int i=0;i<2;++i){
		for(int j=0;j<2;++j){
			int ibx=std::max(l,T[i][j].bx);
			int iex=std::min(r,T[i][j].ex);
			if(ibx<=iex)
				T[i][j].doModify(i?n-iex+1:ibx,i?n-ibx+1:iex,val);
		}
	}
}
int doQuery(int n,int l,int r){
	int res=0;
	for(int i=0;i<2;++i){
		for(int j=0;j<2;++j){
			int iby=std::max(l,T[i][j].by);
			int iey=std::min(r,T[i][j].ey);
			if(iby<=iey)
				res=(res+T[i][j].doQuery(j?n-iey+1:iby,j?n-iby+1:iey))%mod;
		}
	}
	return (res+mod)%mod;
}
int main(){
	freopen("test.in","r",stdin);
	inv6=inv(6);
	int n=read();
	int mid=(n+1)>>1;
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j){
			T[i][j].bx=(i?mid+1:1);
			T[i][j].ex=(i?n:mid);
			T[i][j].by=(j?mid+1:1);
			T[i][j].ey=(j?n:mid);
		}
	int m=read();
	for(int i=1;i<=n;++i)
		doModify(n,i,i,read());
	for(int i=0;i<m;++i){
		int op=read();
		int l=read();
		int r=read();
		if(op==1){
			if(l>r)std::swap(l,r);
			int d=read();
			doModify(n,l,r,d);
		}
		else printf("%d\n",doQuery(n,l,r));	
	}
	return 0;
}

