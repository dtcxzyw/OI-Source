#include <cstdio>
#include <algorithm>
#include <cmath>
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
long long gcd(long long a,long long b){
	return b?gcd(b,a%b):a;
}
const int size=50100;
int c[size],cnt[size]={};
long long now=0;
void update(int u,int op){
	int col=c[u];
	long long a=cnt[col]*(cnt[col]-1);
	cnt[col]+=op;
	long long b=cnt[col]*(cnt[col]-1);
	now+=b-a;
}
int block[size];
struct Query{
	int id,l,r;
	bool operator<(const Query& rhs) const{
		return block[l]==block[rhs.l]?r<rhs.r:l<rhs.l;
	}
} Q[size];
long long res[size][2];
int main(){
	int n=read();
	int m=read();
	int bsiz=sqrt(n)+1;
	for(int i=1;i<=n;++i)block[i]=i/bsiz;
	for(int i=1;i<=n;++i)c[i]=read();
	for(int i=0;i<m;++i){
		Q[i].id=i;
		Q[i].l=read();
		Q[i].r=read();
	}
	std::sort(Q,Q+m);
	int nl=1,nr=0;
	for(int i=0;i<m;++i)
		if(Q[i].l!=Q[i].r){
			while(nr<Q[i].r)update(++nr,1);
			while(nr>Q[i].r)update(nr--,-1);
			while(nl<Q[i].l)update(nl++,-1);
			while(nl>Q[i].l)update(--nl,1);
			long long siz=nr-nl+1;
			long long a=now;
			long long b=siz*(siz-1);
			long long gcdv=gcd(a,b);
			res[Q[i].id][0]=a/gcdv;
			res[Q[i].id][1]=b/gcdv;
		}
		else{
			res[Q[i].id][0]=0;
			res[Q[i].id][1]=1;
		}
	for(int i=0;i<m;++i)
		printf("%lld/%lld\n",res[i][0],res[i][1]);
	return 0;	
}

