#include <iostream>
using namespace std;
struct Node final {
    Node *p,*l;
    Node():p(this),l(this){}
} sets[30001];

inline Node* find(Node* x){
    if(x->p!=x)
        return find(x->p);
    return x->p;
}

inline int getDepth(Node* x){
	int cnt=0;
	while(x->p!=x)
		x=x->p,++cnt;
	return cnt;
}

inline void merge(Node* a,Node* b){
    a=find(a);
	a->p=b->l;
    b->l=a;
}

inline int abs(int x){
	return x>0?x:-x;
}

int main(){
    ios::sync_with_stdio(false);
    int n,i,j;
    cin>>n;
    char code[2];
    for(int k=0;k<n;++k){
        cin>>code>>i>>j;
        switch(code[0]){
            case 'M':merge(sets+i,sets+j);break;
            case 'C':cout<<(find(sets+i)==find(sets+j)?abs(getDepth(sets+i)-getDepth(sets+j))-1:-1)<<endl;break;
        }
    }
    return 0;
}

