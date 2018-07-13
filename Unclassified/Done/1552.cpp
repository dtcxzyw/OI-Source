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
const int size=100100;
struct Node{
	int val,dis,ls,rs;
} tree[size];
int root[size]={};
void swap(int& a,int& b){
	int c=a;
	a=b;
	b=c;
}
int merge(int u,int v){
	if(!u)return v;
	if(!v)return u;
	if(tree[u].val<tree[v].val)swap(u,v);
	tree[u].rs=merge(tree[u].rs,v);
	if(tree[tree[u].ls].dis<tree[tree[u].rs].dis)swap(tree[u].ls,tree[u].rs);
	tree[u].dis=tree[tree[u].rs].dis+1;
	return u;
}
int b[size],l[size],cnt[size];
long long sum[size];
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		b[i]=read();
		tree[i].ls=tree[i].rs=tree[i].dis=0;
		sum[i]=tree[i].val=read();
		root[i]=i;
		cnt[i]=1;
		l[i]=read();
	}
	long long ans=0;
	for(int i=n;i>=1;--i){
		while(sum[i]>m){
			sum[i]-=tree[root[i]].val;
			--cnt[i];
			root[i]=merge(tree[root[i]].ls,tree[root[i]].rs);
		}
		long long val=1LL*l[i]*cnt[i];
		if(ans<val)ans=val;
		int p=b[i];
		root[p]=merge(root[p],root[i]);
		cnt[p]+=cnt[i];
		sum[p]+=sum[i];
	}
	printf("%lld\n",ans);
	return 0;
}

