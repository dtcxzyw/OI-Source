#include <cstdio>
#include <algorithm>
struct Edge{
	int u,v,w;
	bool operator<(const Edge& rhs) const{
		return w<rhs.w;
	}
} E[10001];
struct Node{
	int r;
	Node* p;
	Node():p(this),r(0){}
} set[10001];
Node* find(Node* x){
	if(x->p!=x)
		return x->p=find(x->p);
	return x->p;
}
Node* merge(Node* a,Node* b){
	if(a->r<b->r)
		a->p=b;
	else{
		b->p=a;
		if(a->r==b->r)
			++a->r;
	}
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int sum=0;
	for(int i=0;i<k;++i){
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
		sum+=E[i].w;
	}
	
	std::sort(E,E+k);
	for(int i=0;i<k;++i){
		Node *fa=find(set+E[i].u),*fb=find(set+E[i].v);
		if(fa!=fb){
			sum-=E[i].w;
			merge(fa,fb);
		}
	}
	printf("%d\n",sum);
	return 0;
}

