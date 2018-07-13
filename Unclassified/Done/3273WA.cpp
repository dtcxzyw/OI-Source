#include <cstdio>
#include <vector>
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
int maxv(int a,int b){
	return a>b?a:b;
}
const int size=300100;
struct Seg{
	int val,l,r,lazy;
	std::vector<int> p;
} t[size<<3];
int newNode(){
	static int cnt=0;
	return ++cnt;
}
void color(int id,int x){
	t[id].val+=x;
	t[id].lazy+=x;
}
void push(int id){
	if(t[id].lazy){
		color(t[id].l,t[id].lazy);
		color(t[id].r,t[id].lazy);
		t[id].lazy=0;
	}
}
void modifyAll(int id,int v){
	color(id,v);
}
void pushDown(int id){
	for(int i=0;i<t[id].p.size();++i)pushDown(t[id].p[i]);
	push(id);
}
void pushUp(int id){
	for(int i=0;i<t[id].p.size();++i){
		int p=t[id].p[i];
		int val=maxv(t[t[p].l].val,t[t[p].r].val);
		if(t[p].val==val)continue;
		t[p].val=val;
		pushUp(p);
	}
}
void modifySingle(int id,int v){
	pushDown(id);
	t[id].val+=v;
	pushUp(id);
}
int mergeSeg(int u,int v){
	int id=newNode();
	t[id].l=u,t[id].r=v,t[id].val=maxv(t[u].val,t[v].val),t[id].lazy=0;
	t[u].p.push_back(id);
	t[v].p.push_back(id);  
	return id;
}
int root[size],all,fa[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int u,int v){
	u=find(u),v=find(v);
	if(u!=v){
		fa[u]=v;
		root[v]=mergeSeg(root[v],root[u]);
	}
}
int A[size];
int main(){
	int n=read();
	all=newNode();
	for(int i=1;i<=n;++i){
		int id=newNode();
		root[i]=A[i]=id;
		t[id].l=t[id].r=0,t[id].lazy=0,t[id].val=read();
		fa[i]=i;
		all=mergeSeg(all,id);
	}
	int m=read();
	for(int i=0;i<m;++i){
		int op=getOp();
		if(op=='U')merge(read(),read());
		else if(op=='A'){
			int type=read();
			if(type==1){
				int u=read();
				modifySingle(A[u],read());
			}
			else if(type==2){
				int u=read();
				modifyAll(root[find(u)],read());
			}
			else modifyAll(all,read());
		}
		else{
			int type=read(),ans;
			if(type==1){
				int u=read();
				pushDown(A[u]);
				ans=t[A[u]].val;
			}
			else if(type==2)ans=t[root[find(read())]].val;
			else ans=t[all].val;
			printf("%d\n",ans);
		}
	}
	return 0;
}

