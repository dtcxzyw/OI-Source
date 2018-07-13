#include <cstdio>
#include <map>
#include <vector>
std::map<int,std::vector<int> > hash;
char buf[21];
int BKDR(){
	char* p=buf;
	int res=0;
	while(*p){
		res=res*131+*p;
		++p;
	}
	return res;
}
int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int k;
		scanf("%d",&k);
		for(int j=0;j<k;++j){
			scanf("%s",buf);
			std::vector<int>& c=hash[BKDR()];
			if(c.empty() || c.back()!=i)
				c.push_back(i);
		}
	}
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		scanf("%s",buf);
		std::vector<int>& c=hash[BKDR()];
		for(int j=0;j<c.size();++j)
			printf("%d ",c[j]+1);
		puts("");
	}
	return 0;
}

