#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
std::string to_string(int x){
	std::stringstream ss;
	ss<<x;
	return ss.str();
}
int main(){
	int id,v,e;
	scanf("%d%d%d",&id,&v,&e);
	int t=2+e*2;
	printf("t=%d\n",t);
	std::string path=to_string(id)+".txt";
	freopen(path.c_str(),"w",stdout);
	printf("%d %d\n",v,e);
	for(int i=0;i<v;++i)
		for(int j=i+1;j<v;++j){
			printf("%d %d\n",i,j);
			--e;
			if(e==0)return 0;
		}
	throw;
	return 0;
}

