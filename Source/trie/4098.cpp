#include <cstdio>
#include <set>
#include <algorithm>
#include <iterator>
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
const int size=50005,maxb=29;
struct Node{
	int cnt,c[2];
} T[size*(maxb+2)];
int cnt=0;
int insert(int src,int val,int d){
	int id=++cnt;
	T[id]=T[src];
	++T[id].cnt;
	if(d>=0){
		int x=(val>>d)&1;
		T[id].c[x]=insert(T[src].c[x],val,d-1);
	}
	return id;
}
int query(int tb,int te,int val,int d){
	if(d<0)return 0;
	int x=((val>>d)&1)^1,ans=0;
	if(T[T[te].c[x]].cnt>T[T[tb].c[x]].cnt)ans=1<<d;
	else x^=1;
	return ans|query(T[tb].c[x],T[te].c[x],val,d-1);
}
int root[size]={},A[size],pos[size];
bool cmp(int a,int b){
	return A[a]>A[b];
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		pos[i]=i;
		root[i]=insert(root[i-1],A[i],maxb);
	}
	std::sort(pos+1,pos+n+1,cmp);
	std::set<int> s;
	s.insert(-1);s.insert(-2),s.insert(pos[1]),s.insert(n+1),s.insert(n+2);     
	int ans=0;
	for(int i=2;i<=n;++i){
		int l=std::max(1,*std::prev(std::prev(s.lower_bound(pos[i])))+1);
		int r=std::min(n,*std::next(s.lower_bound(pos[i]))-1);
		s.insert(pos[i]);
		ans=std::max(ans,query(root[l-1],root[r],A[pos[i]],maxb));
	}
	printf("%d\n",ans);
	return 0;
}

