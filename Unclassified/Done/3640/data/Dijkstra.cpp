#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
std::string to_string(int x){
	std::stringstream ss;
	ss<<x;
	return ss.str();
}
std::vector<std::pair<int,int> > link[301];
void addEdge(int u,int v,int w){
	link[u].push_back(std::make_pair(v,w));
}
int main(){
	int id,k;
	scanf("%d%d",&id,&k);
	std::string path=to_string(id)+".txt";
	freopen(path.c_str(),"w",stdout);
	int v=1,x=100000;
	for(int i=0;i<k;++i){
		int s=v-1,a=v,b=v+1;
		addEdge(s,a,-1);
		addEdge(s,b,-2);
		addEdge(a,b,-x);
		v+=2,x/=2;
	}
	printf("%d\n",v);
	for(int i=0;i<v;++i){
		printf("%d ",static_cast<int>(link[i].size()));
		for(int j=0;j<link[i].size();++j)
			printf("%d %d ",link[i][j].first,link[i][j].second);
		puts("");
	}
	int q=6;
	printf("%d\n",q);
	for(int i=1;i<=q;++i)
		printf("%d %d\n",0,v-1);
	return 0;
}

