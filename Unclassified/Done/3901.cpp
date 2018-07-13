#include <cstdio>
#include <map>
int last[100001];
int main(){
	int n,q,x;
	scanf("%d%d",&n,&q);
	std::map<int,int> cache;
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		int& id=cache[x];
		last[i]=id;
		id=i;
	}
	for(int i=2;i<=n;++i)
		last[i]=std::max(last[i],last[i-1]);
	int l,r;
	for(int i=0;i<q;++i){
		scanf("%d%d",&l,&r);
		puts(last[r]<l?"Yes":"No");
	}
	return 0;
}

