#include <cstdio>
#include <algorithm>
using namespace std;
int h[10001<<2|1]={};
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
	int h,x,y;
	bool operator<(const Info& rhs) const{
		return h<rhs.h;
	}
} input[10000];
int main(){
	int n;
	scanf("%d",&n);
	int ans=0;
	for(int i=0;i<n;++i)
		scanf("%d%d%d",&input[i].h,&input[i].x,&input[i].y);
	sort(input,input+n);
	for(int i=0;i<n;++i){
		ans+=max(0,input[i].h-query(1,10000,1,input[i].x));
		ans+=max(0,input[i].h-query(1,10000,1,input[i].y-1));
		modify(1,10000,1,input[i].x,input[i].y-1,input[i].h);
	}
	printf("%d\n",ans);
	return 0;
}

