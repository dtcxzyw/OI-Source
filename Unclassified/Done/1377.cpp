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
struct Node{
	int l,r,v;
	Node():l(0),r(0),v(0){}
	void insert(int id);
	void print();
} tree[100001];
void Node::insert(int id){
	if(tree[id].v<v){
		if(l)tree[l].insert(id);
		else l=id;
	}
	else{
		if(r)tree[r].insert(id);
		else r=id;
	}
}
void Node::print(){
	printf("%d ",v);
	if(l)tree[l].print();
	if(r)tree[r].print();
}
int main(){
	int n=read();
	tree[1].v=read();
	for(int i=2;i<=n;++i){
		tree[i].v=read();
		tree[1].insert(i); 
	}
	tree[1].print();
	return 0;
}

