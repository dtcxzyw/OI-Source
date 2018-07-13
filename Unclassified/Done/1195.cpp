#include <cstdio>
#include <algorithm>
struct Node{
	Node* p;
	int r;
	Node():p(this),r(0){}
} set[1001];

struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[10000];

Node* find(Node* x){
	return x->p==x?x:x->p=find(x->p);
}

void merge(Node* a,Node* b){
	if(a->r>b->r)
		b->p=a;
	else{
		a->p=b;
		if(a->r==b->r)
			++b->r;
	}
}

int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;++i)
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	
	std::sort(E,E+m);
	
	int res=0;
	for(int i=0;i<m;++i){
		Node *a=find(set+E[i].u),*b=find(set+E[i].v);
		if(a!=b){
			res+=E[i].w;
			merge(a,b);
			--n;
			if(n==k)break;
		}
	}
	
	if(n!=k) puts("No Answer");
	else printf("%d\n",res);
	return 0;	
}

