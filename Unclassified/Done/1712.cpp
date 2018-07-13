#include <cstdio>
#include <algorithm>
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0'||c>'9');
	while('0'<=c&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
const int size=501000;
struct Edge{
	int to,next;
} E[size];
int cnt[size<<3]={},lazy[size<<3];
int nl,nr,x;
#define ls l,m,id<<1
#define rs m+1,r,id<<1|1
void modify(int l,int r,int id){
	if(nl<=l && r<=nr)cnt[id]+=x,lazy[id]+=x;
	else{
		int m=(l+r)>>1;
		if(lazy[id]){
			cnt[id<<1]+=lazy[id];
			lazy[id<<1]+=lazy[id];
			cnt[id<<1|1]+=lazy[id];
			lazy[id<<1|1]+=lazy[id];
			lazy[id]=0;
		}
		if(nl<=m)modify(ls);
		if(m<nr)modify(rs);
		cnt[id]=std::max(cnt[id<<1],cnt[id<<1|1]);
	}
}
struct Range{
	int l,r,len;
	bool operator<(const Range& rhs) const{
		return len<rhs.len;
	}
} R[size];
int P[size<<1];
int main(){
	int n=read();
	int m=read();
	for(int i=0;i<n;++i){
		R[i].l=read();
		R[i].r=read();
		R[i].len=R[i].r-R[i].l;
		P[i<<1]=R[i].l;
		P[i<<1|1]=R[i].r;
	}
	std::sort(R,R+n);
	std::sort(P,P+2*n);
	int siz=std::unique(P,P+2*n)-P;
	for(int i=0;i<n;++i)
		R[i].l=std::lower_bound(P,P+siz,R[i].l)-P+1,
		R[i].r=std::lower_bound(P,P+siz,R[i].r)-P+1;
	int ans=1<<30,r=0;
	for(int l=0;l<n;++l){
		while(r<n && cnt[1]<m){
			nl=R[r].l,nr=R[r].r,x=1;
			modify(1,siz,1);
			++r;
		}
		if(cnt[1]>=m)ans=std::min(ans,R[r-1].len-R[l].len);
		else if(r>=n)break;
		nl=R[l].l,nr=R[l].r,x=-1;
		modify(1,siz,1);
	}
	if(ans==1<<30)puts("-1");
	else printf("%d\n",ans);
	return 0;
}

