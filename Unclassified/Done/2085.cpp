#include <cstdio>
#include <queue>
#include <vector>
const int size=10000;
int a[size],b[size],c[size],cnt[size];
long long v[size];
struct cmp{
	bool operator()(int lhs,int rhs) const{
		return v[lhs]>v[rhs];
	}
};
std::priority_queue<int,std::vector<int>,cmp> heap;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
		v[i]=a[i]+b[i]+c[i];
		cnt[i]=1;
		heap.push(i); 
	}
	for(int i=0;i<m;++i){
		int x=heap.top();
		heap.pop();
		printf("%lld ",v[x]);
		++cnt[x];
		v[x]=(1LL*a[x]*cnt[x]+b[x])*cnt[x]+c[x];
		heap.push(x); 
	}
	
	return 0;
}

