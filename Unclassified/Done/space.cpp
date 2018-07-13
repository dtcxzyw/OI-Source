#include <cstdio>
#include <map>
#include <functional>
using namespace std;
map<int,map<int,map<int,int,greater<int>>,greater<int>>,greater<int>> space;
const int size=100000;
int x[size],y[size],z[size],ans[size]={};
inline int sum(int x){
	return x;
}
template<typename T1,typename T2,typename T3,typename First,typename... Args>
int sum(const map<T1,T2,T3>& m,First x,Args... args){
	auto i=m.lower_bound(x);
	int res=0;
	for(;i!=m.cend();++i)
	    res+=sum(i->second,args...);
	return res;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
		++space[x[i]][y[i]][z[i]];
	}
	
	for(int i=0;i<n;++i)
		++ans[sum(space,x[i],y[i],z[i])];
	
	for(int i=1;i<=n;++i)
	    printf("%d\n",ans[i]);
	
	return 0;
}

