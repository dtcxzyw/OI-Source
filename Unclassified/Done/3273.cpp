#include <cstdio>
#include <set>
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
int getOp(){
	int c;
	do c=getchar();
	while(c<'A'||c>'Z');
	return c;
}
const int size=300100;
struct Node{
	int key,l,r,dis,lazy;
} T[size];
void color(int u,int k){
	T[u].key+=k;
	T[u].lazy+=k;
}
void push(int u){
	if(T[u].lazy){
		color(T[u].l,T[u].lazy);
		color(T[u].r,T[u].lazy);
		T[u].lazy=0;
	}
}
int fa[size];
int mergeNode(int u,int v){
	if(!u || !v)return u|v;
	if(T[u].key<T[v].key)std::swap(u,v);
	push(u);
	T[u].r=mergeNode(T[u].r,v);
	fa[T[u].r]=u;
	if(T[T[u].l].dis<T[T[u].r].dis)std::swap(T[u].l,T[u].r);
	T[u].dis=T[T[u].r].dis+1;
	return u;
}
int find(int x){
	while(fa[x]!=x)x=fa[x];
	return x;
}
int eraseNode(int u){
	int nc=mergeNode(T[u].l,T[u].r);
	fa[nc]=(fa[u]==u?nc:fa[u]);
	if(T[fa[u]].l==u)T[fa[u]].l=nc;
	else T[fa[u]].r=nc;
	T[u].dis=T[u].lazy=T[u].l=T[u].r=0;
	fa[u]=u;
	return find(nc);
}
int q[size];
void update(int x){
	int top=0;
	while(fa[x]!=x){
		q[++top]=x;
		x=fa[x];
	}
	q[++top]=x;
	while(top)push(q[top--]);
}
std::multiset<int> cur;
void erase(int x){
	cur.erase(cur.find(x));
}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u!=v){
		if(mergeNode(u,v)==v)erase(T[u].key);
		else erase(T[v].key);
	}
}
int main(){
	int n=read(),off=0;
	for(int i=1;i<=n;++i){
		T[i].key=read();
		T[i].l=T[i].r=T[i].dis=T[i].lazy=0;
		fa[i]=i;
		cur.insert(T[i].key);
	}
	int m=read();
	for(int i=0;i<m;++i){
		int op=getOp();
		if(op=='U')merge(read(),read());
		else if(op=='A'){
			int type=read();
			if(type==1){
				int u=read();
				update(u);
				int id=find(u);
				erase(T[id].key);
				int old=eraseNode(u);
				T[u].key+=read();
				int p=mergeNode(old,u);
				cur.insert(T[p].key);
			}
			else if(type==2){
				int u=read();
				int id=find(u);
				erase(T[id].key);
				color(id,read());
				cur.insert(T[id].key);
			}
			else off+=read();
		}
		else{
			int type=read(),ans;
			if(type==1){
				int u=read();
				update(u);
				ans=T[u].key;
			}
			else if(type==2)ans=T[find(read())].key;
			else ans=*cur.rbegin();
			printf("%d\n",ans+off);
		}
	}
	return 0;
}

