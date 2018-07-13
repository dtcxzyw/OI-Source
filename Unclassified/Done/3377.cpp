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
struct Key{
	int key,id;
	bool operator<(Key rhs) const{
		return key!=rhs.key?key>rhs.key:id>rhs.id;
	}
};
struct Node{
	Key key;
	int ls,rs,dis;
} tree[size];
void swap(int& a,int& b){
	int c=a;
	a=b;
	b=c;
}
int merge(int u,int v){
	if(!u)return v;
	if(!v)return u;
	if(tree[u].key<tree[v].key)swap(u,v);
	tree[u].rs=merge(tree[u].rs,v);
	if(tree[tree[u].ls].dis<tree[tree[u].rs].dis)swap(tree[u].ls,tree[u].rs);
	tree[u].dis=tree[tree[u].rs].dis+1;
	return u;
}
int fa[size],root[size];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool flag[size]={};
int main(){
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i){
		tree[i].key.key=read();
		tree[i].key.id=i;
		tree[i].ls=tree[i].rs=tree[i].dis=0;
	}
	for(int i=1;i<=n;++i)root[i]=fa[i]=i;
	for(int i=0;i<m;++i)
		if(read()==1){
			int u=read(),v=read();
			if(flag[u]||flag[v])continue;
			int fu=find(u);
			int fv=find(v);
			if(fu!=fv)fa[fv]=fu,root[fu]=merge(root[fu],root[fv]);
		}
		else{
			int u=read();
			if(flag[u])puts("-1");
			else{
				int fu=find(u);
				Key val=tree[root[fu]].key;
				root[fu]=merge(tree[root[fu]].ls,tree[root[fu]].rs);
				printf("%d\n",val.key);
				flag[val.id]=true;
			}
		}
	return 0;
}

