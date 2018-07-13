#include <cstdio>
int read(){
	int res=0,c;
	bool flag=false;
	do{
		c=getchar();
		flag|=c=='-';
	}while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return flag?-res:res;
}
void printImpl(long long x){
	if(x>=10)printImpl(x/10);
	putchar('0'+x%10);
}
void print(long long x){
	if(x<0)putchar('-'),x=-x;
	printImpl(x);
	putchar('\n');
}
const int size=100010;
struct Edge{
	int to,next;
} E[size*2];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
int l[size],r[size],ID[size<<1],pcnt=0;
bool flag[size<<1];
void DFS(int u){
	l[u]=++pcnt;
	flag[pcnt]=true,ID[pcnt]=u;
	for(int i=last[u];i;i=E[i].next){
		int v=E[i].to;
		if(!l[v])
			DFS(v);
	}
	r[u]=++pcnt;
	flag[pcnt]=false,ID[pcnt]=u;
}
long long sum[size<<3],off[size<<3]={},A[size],fac[size<<3];
void color(int id,long long x){
	off[id]+=x;
	sum[id]+=fac[id]*x;
}
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void build(int l,int r,int id){
	if(l==r){
		fac[id]=(flag[l]?1:-1);
		sum[id]=fac[id]*A[ID[l]];
	}else{
		int m=(l+r)>>1;
		build(ls);
		build(rs);
		sum[id]=sum[id<<1]+sum[id<<1|1];
		fac[id]=fac[id<<1]+fac[id<<1|1];
	}
}
void push(int l,int r,int id){
	if(off[id]!=0){
		int m=(l+r)>>1;
		color(id<<1,off[id]);
		color(id<<1|1,off[id]);
		off[id]=0;
	}
}
void modify(int l,int r,int id,int nl,int nr,int x){
	if(nl<=l && r<=nr)color(id,x);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,x);
		if(m<nr)modify(rs,nl,nr,x);
		sum[id]=sum[id<<1]+sum[id<<1|1];
	}
}
long long query(int l,int r,int id,int nl,int nr){
	if(nl<=l && r<=nr)return sum[id];
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		long long res=0;
		if(nl<=m)res+=query(ls,nl,nr);
		if(m<nr)res+=query(rs,nl,nr);
		return res;
	}
}
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)
		A[i]=read();
	int u,v;
	for(int i=1;i<n;++i){
		u=read();
		v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	DFS(1);
	int op,x,a;
	n<<=1;
	build(1,n,1);
	for(int i=0;i<m;++i){
		op=read();
		x=read();
		if(op==3)print(query(1,n,1,l[1],l[x]));
		else{
			a=read();
			if(op==1){
				modify(1,n,1,l[x],l[x],a);
				modify(1,n,1,r[x],r[x],a);
			}
			else modify(1,n,1,l[x],r[x],a);
		}
	}
	return 0;
}

