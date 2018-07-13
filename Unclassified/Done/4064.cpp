#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
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
const int size=200100;
int n,c[size];
void modify(int i){
	i=n-i+1;
	while(i<=n){
		++c[i];
		i+=i&-i;
	}
}
int query(int i){
	i=n-i+1;
	int res=0;
	while(i){
		res+=c[i];
		i-=i&-i;
	}
	return res;
}
std::vector<int> range[size];
int A[size];
struct Info{
	int r,l,p;
	Info(){}
	Info(int rp,int lp,int lpp):r(rp),l(lp),p(lpp){}
	bool operator<(const Info& rhs) const{
		return r<rhs.r;
	}
};
bool check(int x,int m,int k,int a){
	memset(c,0,sizeof(c));
	std::priority_queue<Info> heap;
	for(int i=1;i<=n;++i){
		if(range[i].size())
			heap.push(Info(range[i].back(),i,range[i].size()-1));
		if(A[i]<x){
			int add=(x-A[i]-1)/a+1-query(i);
			if(add<=0)continue;
			while(k&&add&&heap.size()&&heap.top().r>=i){
				Info val=heap.top();
				heap.pop();
				modify(val.r);
				if(val.p && range[val.l][val.p-1]>=i)heap.push(Info(range[val.l][val.p-1],val.l,val.p-1));
				--k;
				--add;
			}
			if(add)return false;
		}
	}
	return true;
}
void foo(){
	n=read();
	int m=read();
	int k=read();
	int a=read();
	int l=1<<30,r=0;
	for(int i=1;i<=n;++i){
		A[i]=read();
		l=std::min(l,A[i]);
		r=std::max(r,A[i]);
	}
	for(int i=1;i<=n;++i)range[i].clear();
	for(int i=0;i<m;++i){
		int l=read();
		int r=read();
		range[l].push_back(r);
	}
	for(int i=1;i<=n;++i)
		std::sort(range[i].begin(),range[i].end());
	r+=k*a;
	int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,m,k,a))l=mid+1,ans=mid;
		else r=mid-1;
	}	
	printf("%d\n",ans);
}
int main(){
	int t=read();
	while(t--)foo();
	return 0;
}

