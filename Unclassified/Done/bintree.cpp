#include <cstdio>
#include <queue>
struct Node{
	int u,v,siz;
	Node(){};
	Node(int l,int r);
	bool operator<(Node rhs) const{
		if(siz==rhs.siz)return u==rhs.u?v>rhs.v:u>rhs.u;
		return siz>rhs.siz;
	}
};
Node tree[1000001];
Node::Node(int l,int r):u(l),v(r){
	siz=tree[u].siz+tree[v].siz+1;
}
std::priority_queue<Node> heap; 
void put(int u){
	if(tree[u].u){
		putchar('(');
		put(tree[u].u);
		putchar(')');
	}
	putchar('X');
	if(tree[u].v){
		putchar('(');
		put(tree[u].v);
		putchar(')');
	}
}
void update(int x){
	static int now=0;
	if(now>=x)return;
	if(now==0)heap.push(Node(0,0)); 
	for(int i=now+1;i<=x;++i){
		tree[i]=heap.top();
		heap.pop();
		if(tree[i].v+1<=i)heap.push(Node(tree[i].u,tree[i].v+1));
		heap.push(Node(i,0));
	}
	now=x;
}
void foo(int n){
	if(n!=0){
		update(n);
		put(n);
	}
	putchar('\n');
}
int main(){
	freopen("bintree.in","r",stdin);
	freopen("bintree.out","w",stdout);
	int t,n;
	scanf("%d",&t);
	for(int i=0;i<t;++i){
		scanf("%d",&n);
		foo(n);
	}
	return 0;
}

