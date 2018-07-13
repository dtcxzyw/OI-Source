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
std::vector<int> link[301];
int get(int v){
	return rand()%(v-1)+1;
}
int main(){
	int id,v,e,q;
	scanf("%d%d%d%d",&id,&v,&e,&q);
	int t=1+v+e*2+1+q*2;
	printf("t=%d\n",t);
	std::string path=to_string(id)+".txt";
	freopen(path.c_str(),"w",stdout);
	printf("%d\n",v);
	for(int i=0;i<e;++i)
		link[get(v)].push_back(get(v));
	for(int i=0;i<v;++i){
		printf("%d ",static_cast<int>(link[i].size()));
		for(int j=0;j<link[i].size();++j)
			printf("%d %d ",link[i][j],-1);
		puts("");
	}
	printf("%d\n",q);
	for(int i=1;i<=q;++i)
		printf("%d %d\n",0,0);
	return 0;
}

