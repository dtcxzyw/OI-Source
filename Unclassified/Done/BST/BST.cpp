#include <cstdio>
using namespace std;
struct Node final{
	int key,size;
	Node* l,r;
	Node():l(nullptr),r(nullptr),key(0),size(1){}
} tree[100001];
int cnt=0;
inline void insert(int x){
	Node* root=tree;
	while(true){
		++root->size;
		if(root->l && root->key>=x)root=root->l;
		else if(root->r && root->key<=x)root=root->r;
		else break;
	}
	++cnt;
	if(root->key>=x)root->l=tree+cnt;
	else if(root->key<=x)root->r=tree+cnt;
	tree[cnt].key=x;
}
inline int n2p(int x){
	int res=0;
	Node* root=tree;
	while(root->key!=x){
		if(root->l && root->key>=x)root=root->l;
		else if(root->r && root->key<=x){
			res+=root->size-root->r->size;
			root=root->r;
		}
		else break;
	}
	return res-(x>0);
}
inline int p2n(int x){
	Node* root=tree;
	while(x){
		if(root->l && root->l->size>=x){
			x-=root->l->size;
			root=root->r;
		}
		else root=root->l;
	}
	return root.key;
}
inline int prev(int x){
	Node* root=tree;
	while(true){
		if(root->l && root->key>=x)root=root->l;
		else if(root->r && root->key<=x)root=root->r;
		else break;
	}
	
}
inline int next(int x){
	
}

int main(){
	int n,op,x;
	scanf("%d",&n);
	while(n){
		scanf("%d%d",&op,&x);
		switch(op){
			case 1:insert(x);break;
			case 2:erase(x);break;
			case 3:printf("%d\n",n2p(x));break;
			case 4:printf("%d\n",p2n(x))break;
			case 5:printf("%d\n",prev(x));break;
			case 6:printf("%d\n",next(x))break;
		}
		--n;
	}
	return 0;	
}

