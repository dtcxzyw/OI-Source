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
typedef long long Int64;
const int size=600100;
struct Node{
	int l,r,dis;
	long long val;
} T[size];
int merge(int x,int y){
	if(x&&y){
		if(T[x].val<T[y].val)std::swap(x,y);
		T[x].r=merge(T[x].r,y);
		if(T[T[x].l].dis<T[T[x].r].dis)std::swap(T[x].l,T[x].r);
		T[x].dis=T[T[x].r].dis+1;
		return x;
	}
	return x|y;
}
int root[size]={};
void pop(int u){
	root[u]=merge(T[root[u]].l,T[root[u]].r);
}
int p[size],c[size],d[size]={};
int main(){
	int n=read();
	int m=read();
	int siz=n+m;
	long long sum=0;
	for(int i=2;i<=siz;++i){
		p[i]=read();
		++d[p[i]];
		c[i]=read();
		sum+=c[i];
	}
	int cnt=0;
	for(int i=siz;i>1;--i){
		long long l=0,r=0;
		if(i<=n){
			while(--d[i])pop(i);
			l=T[root[i]].val;
			pop(i);
			r=T[root[i]].val;
			pop(i);
		}
		T[++cnt].val=l+c[i];
		T[++cnt].val=r+c[i];
		root[p[i]]=merge(root[p[i]],merge(root[i],merge(cnt,cnt-1)));
	}
	while(d[1]--)pop(1);
	while(root[1]){
		sum-=T[root[1]].val;
		pop(1);
	}
	printf("%lld\n",sum);
	return 0;
}

