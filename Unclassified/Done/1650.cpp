#include <cstdio>
#include <algorithm>
#include <deque>
int cmp(int a,int b){
	return a==b?0:(a>b?1:-1);
}
int main(){
	int n;
	scanf("%d",&n);
	std::deque<int> v1(n),v2(n);
	for(int i=0;i<n;++i)
		scanf("%d",&v1[i]);
	std::sort(v1.begin(),v1.end());
	for(int i=0;i<n;++i)
		scanf("%d",&v2[i]);
	std::sort(v2.begin(),v2.end());
	int ans=0;
	while(v1.size()){
		int x=v1.front(),y=v1.back();
		if(v2.front()<x){
			ans+=cmp(x,v2.front());
			v1.pop_front(),v2.pop_front();
		}
		else if(v2.back()<y){
			ans+=cmp(y,v2.front());
			v1.pop_back(),v2.pop_back();
		}
		else{
			ans+=cmp(x,v2.back());
			v1.pop_front(),v2.pop_back();
		}
	}
	printf("%d\n",ans*200);
	return 0;
}

