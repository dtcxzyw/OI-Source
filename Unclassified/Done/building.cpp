#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int size=200001;
int all[size<<3|1]={};
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id,int nl,int nr,int h){
	if(nl<=l && r<=nr)all[id]=max(all[id],h);
	else{
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,h);
		if(m<nr)modify(rs,nl,nr,h);
	}
}
int query(int l,int r,int id,int x){
	if(l==r)return all[id];
	else{
		int m=(l+r)>>1;
		int ans=all[id];
		if(x<=m)ans=max(ans,query(ls,x));
		if(m<x) ans=max(ans,query(rs,x));
		return ans;
	}
}
struct building{
	int h,l,r;
} units[size];
int A[size<<1],h[size<<1];
map<int,int> table;
pair<int,int> points[size<<1];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&units[i].h,&units[i].l,&units[i].r);
		A[i<<1]=units[i].l,A[i<<1|1]=units[i].r;
	}
	sort(A,A+(n<<1));
	int siz=unique(A,A+(n<<1))-A;
	for(int i=0;i<siz;++i)
		table[A[i]]=i+1;
	for(int i=0;i<n;++i){
		int tl=table[units[i].l],tr=table[units[i].r]-1;
		modify(1,siz,1,tl,tr,units[i].h);
	}
	for(int i=0;i<siz;++i)
		h[i]=query(1,siz,1,i+1);
	int last=0,cnt=0;
	for(int i=0;i<siz;++i){
		if(h[i]!=last){
			points[++cnt]=make_pair(A[i],last);
			points[++cnt]=make_pair(A[i],h[i]);
			last=h[i];
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
		printf("%d %d\n",points[i].first,points[i].second);
	return 0;
}

