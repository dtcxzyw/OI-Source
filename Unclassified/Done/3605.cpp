#include <cstdio>
#include <cstring>
#include <algorithm>
const int size=100001;
struct Edge{
	int to,next;
} E[size];
int last[size]={},cnt=0;
void addEdge(int u,int v){
	++cnt;
	E[cnt].to=v,E[cnt].next=last[u];
	last[u]=cnt;
}
struct Node{
	Node *lc,*rc;
	int l,r,m,sum;
	Node(){}
	Node(int L,int R):l(L),r(R),m((L+R)>>1){}
	Node* check(Node*& child,int l,int r){
		if(!child)child=new Node(l,r);
		return child;
	}
	void modify(int x){
		++sum;
		if(l!=r){
			if(x<=m)check(lc,l,m)->modify(x);
			else check(rc,m+1,r)->modify(x);
		}
	}
	int query(int nl,int nr) const{
		if(nl<=l && r<=nr)return sum;
		else{
			int res=0;
			if(nl<=m && lc)res+=lc->query(nl,nr);
			if(m<nr && rc)res+=rc->query(nl,nr);
			return res;
		}
	}
	void choose(Node*& child,Node* rhs){
		if(rhs){
			if(child)child->merge(rhs);
			else child=rhs;
		}
	}
	void merge(Node* rhs){
		if(this==rhs)return;
		sum+=rhs->sum;
		choose(lc,rhs->lc);
		choose(rc,rhs->rc);
	}
} root[size];
int w[size],order[size],siz,num[size];
void DFS(int x){
	for(int i=last[x];i;i=E[i].next){
		DFS(E[i].to);
		root[x].merge(&root[E[i].to]);
	}
	num[x]=root[x].query(w[x]+1,siz);
	root[x].modify(w[x]);   
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&w[i]);
	memcpy(order,w+1,sizeof(int)*n);
	std::sort(order,order+n);
	siz=std::unique(order,order+n)-order;
	for(int i=1;i<=n;++i)
		w[i]=std::lower_bound(order,order+siz,w[i])-order+1;
	int p;
	for(int i=2;i<=n;++i){
		scanf("%d",&p);
		addEdge(p,i);
	}
	for(int i=1;i<=n;++i)
		root[i].l=1,root[i].r=n,root[i].m=(1+n)>>1;
	DFS(1);
	for(int i=1;i<=n;++i)
		printf("%d\n",num[i]);
	return 0;
}

