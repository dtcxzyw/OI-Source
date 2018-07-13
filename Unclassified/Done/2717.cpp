#include <cstdio>
#include <cstring>
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
const int size=100011;
long long A[size],B[size],sum[size];
void add(int x,int n){
	while(x<=n){
		++sum[x];
		x+=x&-x;
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=sum[x];
		x-=x&-x;
	}
	return res;
}
int getPos(long long x,int n){
	return std::lower_bound(B,B+n,x)-B+1;
}
int main(){
	int n=read();
	int k=read();
	A[0]=0;
	for(int i=1;i<=n;++i)A[i]=A[i-1]+read()-k;
	memcpy(B,A,sizeof(B));
	std::sort(B,B+n+1);
	int siz=std::unique(B,B+n+1)-B;
	long long res=0;
	add(getPos(A[0],siz),siz);
	for(int i=1;i<=n;++i){
		int p=getPos(A[i],siz);
		res+=query(p);
		add(p,siz);
	}
	printf("%lld\n",res);
	return 0;
}

