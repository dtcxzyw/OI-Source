#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int size=200001;
struct Node{
	int l,r,sum;
} nodes[20*size]={};
int tot=0,root[size];
void add(int& p,int base,int v,int l,int r){
	p=++tot;
	nodes[p]=nodes[base];
	++nodes[p].sum;
	if(l==r)return;
	int m=(l+r)>>1;
	if(v<=m) add(nodes[p].l,nodes[base].l,v,l,m);
	else add(nodes[p].r,nodes[base].r,v,m+1,r);
}
int query(int b,int e,int l,int r,int k){
	if(l==r)return l;
	int m=(l+r)>>1;
	int sum=nodes[nodes[e].l].sum-nodes[nodes[b].l].sum;
	if(k<=sum)
	    return query(nodes[b].l,nodes[e].l,l,m,k);
	else
	    return query(nodes[b].r,nodes[e].r,m+1,r,k-sum);
}
int A[size],B[size];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d\n",&A[i]);
	memcpy(B+1,A+1,n*sizeof(int));
	sort(B+1,B+n+1);
	int rn=unique(B+1,B+n+1)-(B+1);
	for(int i=1;i<=n;++i)
		add(root[i],root[i-1],lower_bound(B+1,B+rn+1,A[i])-B,1,rn);
	int l,r,k;
	for(int i=0;i<m;++i){
		scanf("%d%d%d",&l,&r,&k);
		int p=query(root[l-1],root[r],1,rn,k);
		printf("%d\n",B[p]);
	}
	return 0;
}

