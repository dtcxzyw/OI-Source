#include <cstdio>
#include <set>
#include <algorithm>
std::pair<int,int> cow[20000];
int read(){
	int res=0,c;
	do c=getchar();
	while(c<'0' || c>'9');
	while('0'<=c && c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}
int main(){
	int n,m;
	n=read();
	m=read();
	std::multiset<int> t;
	for(int i=0;i<n;++i)
		t.insert(read());
	for(int i=0;i<m;++i){
		cow[i].second=read();
		cow[i].first=read();
	}
	std::sort(cow,cow+m);
	int cnt=0;
	for(int i=0;i<m;++i){
		std::multiset<int>::iterator it=t.lower_bound(cow[i].second);
		if(it!=t.end() && *it<=cow[i].first)
			++cnt,t.erase(it);
	}
	printf("%d\n",cnt);
	return 0;
}

