#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int size=10010;
struct Star{
	int x,y,w;
} s[size];
struct Info{
	int l,r,h,w;
	bool operator<(const Info& rhs) const{
		return h==rhs.h?w<rhs.w:h<rhs.h;
	}
} info[size<<1];
int lazy[size<<2],maxv[size<<2];
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void update(int id){
	maxv[id]=max(maxv[id<<1],maxv[id<<1|1]);
}
void color(int id,int v){
	lazy[id]+=v,maxv[id]+=v;
}
void push(int l,int r,int id){
	if(lazy[id]!=0){
		color(id<<1,lazy[id]);
		color(id<<1|1,lazy[id]);
		lazy[id]=0;
	}
}
void modify(int l,int r,int id,int nl,int nr,int v){
	if(nl<=l && r<=nr)color(id,v);
	else{
		push(l,r,id);
		int m=(l+r)>>1;
		if(nl<=m)modify(ls,nl,nr,v);
		if(m<nr)modify(rs,nl,nr,v);
		update(id);
	}
}
int dx[size],l[size],r[size];
void foo(){
	memset(lazy,0,sizeof(lazy));
	memset(maxv,0,sizeof(maxv));
	int n,w,h;
	scanf("%d%d%d",&n,&w,&h);
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&s[i].x,&s[i].y,&s[i].w);
		dx[i]=s[i].x;
	}
	sort(dx,dx+n);
	int sx=unique(dx,dx+n)-dx;
	int left=0;
	for(int i=0;i<sx;++i){
		while(dx[i]-dx[left]>=w)++left;
		l[i]=left+1,r[i]=i+1;
	}
	for(int i=0;i<n;++i){
		int id=std::lower_bound(dx,dx+sx,s[i].x)-dx;
		Info& add=info[i<<1];
		add.l=l[id],add.r=r[id],add.w=s[i].w,add.h=s[i].y;
		Info& sub=info[i<<1|1];
		sub.l=l[id],sub.r=r[id],sub.w=-s[i].w,sub.h=s[i].y+h;
	}
	n<<=1;
	sort(info,info+n);
	int ans=0;
	for(int i=0;i<n;++i){
		int h=info[i].h;
		while(i<n && h==info[i].h){
			modify(1,sx,1,info[i].l,info[i].r,info[i].w);
			++i;
		}
		--i;
		ans=max(ans,maxv[1]);
	}
	printf("%d\n",ans);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)foo();
	return 0;
}

