#include <cstdio>
#include <algorithm>
using namespace std;
const int size=40001;
int h[size<<3|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int nl,int nr,int k){
    if(nl<=l && r<=nr)h[id]=max(h[id],k);
    else{
        int m=(l+r)>>1;
        if(nl<=m)modify(ls,nl,nr,k);
        if(m<nr)modify(rs,nl,nr,k);
    }
}
int query(int l,int r,int id,int x){
    if(l==r)return h[id];
    else{
        int m=(l+r)>>1;
        int ans=h[id];
        if(x<=m)ans=max(ans,query(ls,x));
        if(m<x) ans=max(ans,query(rs,x));
        return ans;
    }
}
struct Info{
	int l,r,h;
} input[size];
int ps[size<<1];
int remap(int x,int siz){
	return lower_bound(ps,ps+siz,x)-ps;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d%d",&input[i].l,&input[i].r,&input[i].h);
	
	for(int i=0;i<n;++i)
		ps[i<<1]=input[i].l,ps[i<<1|1]=input[i].r;
	sort(ps,ps+(n<<1));
	int siz=unique(ps,ps+(n<<1))-ps;
	for(int i=0;i<n;++i)
		input[i].l=remap(input[i].l,siz)+1,input[i].r=remap(input[i].r,siz);
	for(int i=0;i<n;++i)
		modify(1,siz,1,input[i].l,input[i].r,input[i].h);
	long long sum=query(1,siz,1,siz);
	for(int i=0;i<siz-1;++i)
		sum+=1LL*query(1,siz,1,i+1)*(ps[i+1]-ps[i]);
	printf("%lld\n",sum);
	return 0;	
}

