#include <cstdio>
#include <vector>
#include <cstring>
#include <cctype>
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
char buf[10];
void readOp(){
	int cnt=0,c;
	do c=getchar();
	while(!isgraph(c));
	while(isgraph(c)){
		buf[cnt++]=c;
		c=getchar();
	}
	buf[cnt]='\0';
}
const int size=500005;
struct Node{
	int c[2],p,v,sum,siz,maxs,ls,rs;
	bool cov,rev;
} T[size];
int root=0,icnt=0;
std::vector<int> pool;
int newNode(){
	int id;
	if(pool.empty())id=++icnt;
	else{
		id=pool.back();
		pool.pop_back();
	}
	memset(T+id,0,sizeof(Node));
	return id;
}
void freeNode(int u){
	if(u){
		freeNode(T[u].c[0]);
		freeNode(T[u].c[1]);
		pool.push_back(u);
	}
}
int son(int p,int s){
	return T[p].c[1]==s;
}
void update(int u){
	if(u==0)return;
	int l=T[u].c[0],r=T[u].c[1];
	T[u].sum=T[l].sum+T[r].sum+T[u].v;
	T[u].siz=T[l].siz+T[r].siz+1;
	T[u].maxs=std::max(T[l].rs+T[r].ls+T[u].v,
		std::max(T[l].maxs,T[r].maxs));
	T[u].ls=std::max(T[l].ls,T[l].sum+T[u].v+T[r].ls);
	T[u].rs=std::max(T[r].rs,T[r].sum+T[u].v+T[l].rs);
}
void color(int u,int val){
	if(u==0)return;
	T[u].v=val;
	T[u].cov=true;
	T[u].sum=T[u].v*T[u].siz;
	if(val>=0)T[u].ls=T[u].rs=T[u].maxs=T[u].sum;
	else T[u].ls=T[u].rs=0,T[u].maxs=val;
}
void rev(int u){
	if(u==0)return;
	T[u].rev^=1;
	std::swap(T[u].c[0],T[u].c[1]);
	std::swap(T[u].ls,T[u].rs);
}
void push(int u){
	int l=T[u].c[0],r=T[u].c[1];
	if(T[u].cov){
		color(l,T[u].v);
		color(r,T[u].v);
		T[u].cov=T[u].rev=false;
	}
	if(T[u].rev){
		rev(l),rev(r);
		T[u].rev=false;
	}
}
void link(int p,int s,int id){
	if(p==0)root=s;
	else T[p].c[id]=s;
	T[s].p=p;
}
void rotate(int u){
	int p=T[u].p;
	int g=T[p].p;
	int a=son(p,u),b=!a;
	link(p,T[u].c[b],a);
	link(g,u,son(g,p));
	link(u,p,b);
	update(p);
	update(u);
}
void splay(int u,int f){
	while(T[u].p!=f){
		int p=T[u].p;
		int g=T[p].p;
		if(g!=f){
			if(son(p,u)^son(g,p))rotate(p);
			else rotate(u);
		}
		rotate(u);
	}
}
int find(int u,int k){
	push(u);
	int l=T[u].c[0],r=T[u].c[1],lsiz=T[l].siz;
	if(lsiz+1==k)return u;
	if(lsiz>=k)return find(l,k);
	return find(r,k-lsiz-1);
}
int split(int pos,int tot){
	int pre=find(root,pos),nxt=find(root,pos+tot+1);
	splay(pre,0);
	splay(nxt,pre);
	return T[nxt].c[0];
}
int querySum(int pos,int tot){
	return T[split(pos,tot)].sum;
}
void modify(int pos,int tot,int val){
	int u=split(pos,tot);
	color(u,val);
	int p=T[u].p;
	update(p);
	update(T[p].p);
}
void doRev(int pos,int tot){
	int u=split(pos,tot);
	if(!T[u].cov){
		rev(u);
		int p=T[u].p;
		update(p);
		update(T[p].p);
	}
}
void erase(int pos,int tot){
	int u=split(pos,tot);
	int p=T[u].p;
	freeNode(u);
	T[p].c[0]=0;
	update(p);
	update(T[p].p);
}
int A[4000010];
int build(int l,int r){
	if(l>r)return 0;
	int id=newNode();
	if(l==r){
		T[id].siz=1;
		color(id,A[l]);
	}
	else{
		int m=(l+r)>>1;
		int lp=T[id].c[0]=build(l,m-1);
		int rp=T[id].c[1]=build(m+1,r);
		if(lp)T[lp].p=id;
		if(rp)T[rp].p=id;
		T[id].v=A[m];
		update(id);
	}
	return id;
}
void insert(int pos,int tot){
	for(int i=1;i<=tot;++i)A[i]=read();
	int rt=build(1,tot);
	int x=find(root,pos+1),y=find(root,pos+2);
	splay(x,0);
	splay(y,x);
	T[rt].p=y;
	T[y].c[0]=rt;
	update(y);
	update(x);
}
const int nil=-(1<<20);
int main(){
	int n=read();
	int m=read();
	T[0].maxs=A[0]=A[n+1]=nil;
	for(int i=1;i<=n;++i)A[i]=read();
	root=build(0,n+1);
	for(int i=0;i<m;++i){
		readOp();
		int pos,tot;
		if(buf[0]!='M' || buf[2]!='X'){
			pos=read();
			tot=read();
		}
		
		if(buf[0]=='I')insert(pos,tot);
		else if(buf[0]=='D')erase(pos,tot);
		else if(buf[0]=='M'){
			if(buf[2]=='X')printf("%d\n",T[root].maxs);
			else modify(pos,tot,read());
		}
		else if(buf[0]=='R')doRev(pos,tot);
		else printf("%d\n",querySum(pos,tot));
	}
	return 0;
}

