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
int getID(int num)
{
    int& x=idMap[num];
    if(x)return x;
    return x=++cnt;
}
struct Question
{
    int i,j;
} eq[100001],neq[100001];
void foo()
{
    cnt=0,idMap.clear();
    int eqc=0,neqc=0,n;
    cin>>n;
    new(sets1) Node[2*n+1];
    new(sets2) Node[2*n+1];
    int c,i,j,e;
    bool flag=false;
    Node *ii,*ij;
    for(c=0;c<n;++c)
    {
        cin>>i>>j>>e;
        if(flag)continue;
        if(e) 
        {
            if(i==j)continue;
            i=getID(i),j=getID(j);
            doUnion(sets1+i,sets1+j),eq[++eqc]={i,j};
        }
        else 
        {
            if(i==j)
            {
                flag=true;
                continue;
            }
            i=getID(i),j=getID(j);
            doUnion(sets2+i,sets2+j),neq[++neqc]={i,j};
        }
    }
    if(flag)goto p;
    for(c=1;c<=neqc;++c)
    {
        ii=find(sets1+neq[c].i);
        ij=find(sets1+neq[c].j);
        if(ii==ij)
        {
            flag=true;
            break;
        }
    }
    if(flag)goto p;
    for(c=1;c<=eqc;++c)
    {
        ii=find(sets2+eq[c].i);
        ij=find(sets2+eq[c].j);
        if(ii==ij)
        {
            flag=true;
            break;
        }
    }
p:
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

