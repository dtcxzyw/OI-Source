#include <iostream>
#include <map>
#include <new>
using namespace std;
struct Node
{
	Node* p;
	int r;
	Node():p(this),r(0){}
}sets1[200001],sets2[200001];
Node* find(Node* node)
{
	if(node!=node->p)
		return node->p=find(node->p);
	return node->p;
}
void doUnion(Node* a,Node* b)
{
	a=find(a),b=find(b);
	if(a->r>b->r)
		b->p=a;
	else
	{
		a->p=b;
		if(a->r==b->r)++b->r;
	}
}
map<int,int> idMap;
int cnt;
Node* getID(int id,Node* base)
{
	int& x=idMap[id];
	if(x)return base+x;
	return base+(x=++cnt);
}
void foo()
{
	cnt=0,idMap.clear();
	int n;
	cin>>n;
	new(sets1) Node[2*n+1];
	new(sets2) Node[2*n+1];
	int c,i,j,e;
	bool flag=false;
	Node *ii,*ij;
	for(c=0;c<n;++c)
	{
		cin>>i>>j>>e;
		if(e) 
		{
			doUnion(getID(i,sets1),getID(j,sets1));
			ii=find(getID(i,sets2));
			ij=find(getID(j,sets2));
			if(ii==ij)
			{
				flag=true;
				break;
			}
		}
		else 
		{
			doUnion(getID(i,sets2),getID(j,sets2));
			ii=find(getID(i,sets1));
			ij=find(getID(j,sets1));
			if(ii==ij)
			{
				flag=true;
				break;
			}
		}
	}
	cout<<(flag?"NO":"YES")<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t)
		foo(),--t;
	return 0;
}

