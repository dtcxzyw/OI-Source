#include <cstdio>
#include <vector>
#include <map>
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
struct Node{
	Node* fail;
	std::vector<int> cnt;
	std::map<int,Node*> nxt;
	typedef std::map<int,Node*>::iterator IterM;
} pool[1000000],*root;
Node* newNode(){
	static int cnt=0;
	++cnt;
	pool->fail=0;
	return pool+cnt;
}
void insert(int id){
	int siz=read();
	Node* p=root;
	for(int i=1;i<=siz;++i){
		int c=read();
		Node*& node=p->nxt[c];
		if(!node)node=newNode();
		p=node;
	}
	p->cnt.push_back(id); 
}
Node* q[1000000];
void cook(){
	int b=0,e=1;
	q[0]=root;
	while(b!=e){
		Node* u=q[b++];
		for(Node::IterM it=u->nxt.begin();it!=u->nxt.end();++it){
			Node* v=it->second;
			int c=it->first;
			if(u==root)v->fail=root;
			else{
				Node* p=u->fail;
				while(p){
					if(p->nxt.count(c)){
						v->fail=p->nxt[c];
						break;
					}
					p=p->fail;
				}
				if(!p)v->fail=root;
			}
			q[e++]=v;
		}
	}
}
int ans1[50100]={};
bool flag[50100]={};
int A[50100];
int match(int* begin,int* end){
	Node* p=root;
	int cnt=0;
	for(int* it=begin;it!=end;++it){
		int c=*it;
		while(!p->nxt.count(c) && p!=root)p=p->fail;
		if(p->nxt.count(c)){
			p=p->nxt[c];
			Node* pc=p;
			while(pc!=root){
				for(int j=0;j<pc->cnt.size();++j){
					int v=pc->cnt[j];
					if(!flag[v])A[++cnt]=v,flag[v]=true;
				}
				pc=pc->fail;
			}
		}
		else p=root;
	}
	for(int i=1;i<=cnt;++i){
		++ans1[A[i]];
		flag[A[i]]=false;
	}
	return cnt;
}
const int size=20100;
int P[200000],begin[size],end[size];
void build(int id){
	static int cnt=0;
	begin[id]=cnt;
	int siz=read();
	for(int i=1;i<=siz;++i)P[cnt++]=read();
	P[cnt++]=1<<30;
	siz=read();
	for(int i=1;i<=siz;++i)P[cnt++]=read();
	end[id]=cnt;
}
int ans2[size];
int main(){
	root=newNode();
	int n=read();
	int m=read();
	for(int i=1;i<=n;++i)build(i);
	for(int i=1;i<=m;++i)insert(i);
	cook();
	for(int i=1;i<=n;++i)
		ans2[i]=match(P+begin[i],P+end[i]);
	for(int i=1;i<=m;++i)printf("%d\n",ans1[i]);
	printf("%d",ans2[1]);
	for(int i=2;i<=n;++i)printf(" %d",ans2[i]);
	return 0;
}

