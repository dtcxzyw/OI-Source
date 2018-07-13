#include <cstdio>
#include <algorithm>
const int size=20001;
long long num[size]={},sum[size]={};
int maxx=0;
void add(long long* A,int i,int x){
	while(i<=maxx){
		A[i]+=x;
		i+=i&-i;
	}
}

long long query(long long* A,int i){
	long long ans=0;
	while(i){
		ans+=A[i];
		i-=i&-i;
	}
	return ans;
}
struct Unit{
	int v,x;
	bool operator<(Unit rhs) const{
		return v<rhs.v;
	}
} units[100000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d%d",&units[i].v,&units[i].x);
		maxx=std::max(maxx,units[i].x);
	}
	std::sort(units,units+n);
	long long ans=0;
	for(int i=0;i<n;++i){
		long long nl=query(num,units[i].x-1),sl=query(sum,units[i].x-1),
			nr=query(num,maxx)-query(num,units[i].x),
			sr=query(sum,maxx)-query(sum,units[i].x);
		ans+=units[i].v*((nl-nr)*units[i].x-sl+sr);
		add(num,units[i].x,1);
		add(sum,units[i].x,units[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}

