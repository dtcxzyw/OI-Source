#include <cstdio>
#include <set>
#include <vector>
#include <map>
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
const int size=100005;
typedef std::set<int>::iterator IterS;
typedef std::set<int>::reverse_iterator IterRS;
typedef std::map<int,int>::iterator IterM;
void foo1(){
	int k=read();
	int n=read();
	int m=read();
	std::vector<std::set<int> > net(n+5);
	for(int i=0;i<k;++i)
		for(int j=1;j<=n;++j){
			int val=read();
			if(val!=j){
				net[std::min(val,j)].insert(std::max(val,j));
			}
		}
	int cnt=0;
	for(int i=1;i<=n;++i)
		cnt+=net[i].size();
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i)
		for(IterS it=net[i].begin();it!=net[i].end();++it)
			printf("%d %d 1\n",i,*it);
}
void foo2(){
	int k=read();
	int n=read();
	int m=read();
	std::vector<std::map<int,int> > link(n+5);
	for(int i=0;i<k;++i)
		for(int j=1;j<=n;++j){
			int val=read();
			if(val!=j){
				++link[j][val];
			}
		}
	std::vector<std::set<int> > pair(n+5);
	for(int i=1;i<=n;++i){
		std::vector<std::pair<int,int> > ref;
		for(IterM j=link[i].begin();j!=link[i].end();++j)
			ref.push_back(std::make_pair(j->second,j->first));
		std::sort(ref.rbegin(),ref.rend());
		for(int j=0;j<2 && j<ref.size();++j)
			pair[std::min(i,ref[j].second)].insert(std::max(i,ref[j].second));
	}
	std::vector<std::map<int,int> > net(n+5);
	for(int i=1;i<=m;++i){
		std::set<int> cur;
		for(int j=1;j<=n;++j){
			std::vector<int> toErase;
			for(IterS it=pair[j].begin();it!=pair[j].end();++it){
				int k=*it;
				if(!cur.count(j) && !cur.count(k)){
					cur.insert(j);
					cur.insert(k);
					net[j][k]=i;
					toErase.push_back(k);
				}
			}
			for(int k=0;k<toErase.size();++k)
				pair[j].erase(toErase[k]);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		cnt+=net[i].size();
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i)
		for(IterM it=net[i].begin();it!=net[i].end();++it)
			printf("%d %d %d\n",i,it->first,it->second);
}
void foo(){
	throw;
}
int main(){
	int id=read();
	int t=read();
	typedef void (*Func)();
	const Func func[9]={foo,foo1,foo2,foo,foo,foo,foo,foo,foo};
	while(t--)func[id]();
	return 0;
}

