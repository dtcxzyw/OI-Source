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
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
int sum[size<<2]={};
void add(int l,int r,int id,int pos,int val){
	sum[id]+=val;
	if(l!=r){
		int m=(l+r)>>1;
		if(pos<=m)add(ls,pos,val);
		else add(rs,pos,val);
	}
}
int query(int l,int r,int id,int k){
	if(l==r)return l;
	int rsiz=sum[id<<1|1],m=(l+r)>>1;
	if(rsiz<k)return query(ls,k-rsiz);
	return query(rs,k);
}
int A[size],ans[size],siz[size];
int main(){
	int n;
	double k;
	scanf("%d %lf",&n,&k);
	for(int i=1;i<=n;++i)
		A[i]=read();
	std::sort(A+1,A+n+1);
	for(int i=1;i<=n;++i)siz[i]=1;
	for(int i=n;i>=1;--i){
		int p=i/k;
		addEdge(p,i);
		siz[p]+=siz[i];
	}
	for(int i=last[0];i;i=E[i].next)add(1,n,1,E[i].to,siz[E[i].to]);
	int end=1;
	for(int i=1;i<=n;i=end){
		while(end<=n && A[end]==A[i])++end;
		for(int j=end-i;j;--j){
			int u=query(1,n,1,j);
			ans[u]=A[i];
			add(1,n,1,u,-siz[u]);
			for(int e=last[u];e;e=E[e].next)
				add(1,n,1,E[e].to,siz[E[e].to]);
		}
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}

